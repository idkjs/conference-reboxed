import Amplify,{ Auth, Hub } from 'aws-amplify';
import { FontAwesome } from '@expo/vector-icons';
import { withAuthenticator } from 'aws-amplify-react-native';
import AmplifyTheme from 'aws-amplify-react-native/src/AmplifyTheme';
import React from 'react';
import { Image, StyleSheet, View } from 'react-native';
import { createAppContainer, createBottomTabNavigator } from 'react-navigation';
import Map from './Map';
import Profile from './Profile';
import Schedule from './Schedule';
import { colors, logo } from './theme';
import config from '../../aws-exports';

Amplify.configure(config);
const TabNavigator = createBottomTabNavigator(
	{
		Schedule: {
			screen: Schedule
		},
		Profile: {
			screen: Profile
		},
		Map: {
			screen: Map
		}
	},
	{
		tabBarOptions: {
			activeTintColor: colors.highlight,
			inactiveTintColor: '#fafafa',
			style: {
				backgroundColor: colors.primary
			}
		},
		defaultNavigationOptions: ({ navigation }) => ({
			tabBarIcon: ({ tintColor }) => {
				const { routeName } = navigation.state;
				if (routeName === 'Schedule') {
					return <FontAwesome color={tintColor} size={20} name="calendar" />;
				}
				if (routeName === 'Map') {
					return <FontAwesome color={tintColor} size={20} name="map" />;
				}
				return <FontAwesome color={tintColor} size={20} name="user" />;
			}
		})
	}
);

class TabNavWithProps extends React.Component {
	static router = TabNavigator.router;
	render() {
		return <TabNavigator screenProps={{ ...this.props }} {...this.props} />;
	}
}

const App = createAppContainer(TabNavWithProps);

const theme = {
	...AmplifyTheme,
	button: {
		...AmplifyTheme.button,
		backgroundColor: colors.primaryLight
	},
	sectionFooterLink: {
		...AmplifyTheme.sectionFooterLink,
		color: colors.primaryLight
	},
	buttonDisabled: {
		...AmplifyTheme.buttonDisabled,
		backgroundColor: colors.primaryOpaque(0.6)
	}
};

class AppWithAuth extends React.Component {
	state = {
		signedIn: true
	};
	async componentDidMount() {
		try {
			await Auth.currentAuthenticatedUser();
			this.setState({ signedIn: true });
		} catch (err) {
			console.log('user not signed in');
		}
		Hub.listen('auth', (data) => {
			const { payload: { event } } = data;
			if (event === 'signIn') {
				this.setState({ signedIn: true });
			}
			if (event === 'signOut' && this.state.signedIn) {
				this.setState({ signedIn: false });
			}
		});
	}
	render() {
		const AppComponent = withAuthenticator(App, null, null, null, theme);
		return (
			<View style={styles.appContainer}>
				{!this.state.signedIn && <Logo />}
				<AppComponent {...this.props} />
			</View>
		);
	}
}

const Logo = () => (
	<View style={styles.logoContainer}>
		<Image style={styles.logo} resizeMode="contain" source={logo} />
	</View>
);

const styles = StyleSheet.create({
	appContainer: {
		flex: 1
	},
	logoContainer: {
		marginTop: 70,
		justifyContent: 'center',
		alignItems: 'center'
	},
	logo: {
		height: 50,
		width: 200
	}
});

export default AppWithAuth;
