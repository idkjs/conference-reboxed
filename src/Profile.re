open ReactNative;
open ReactNavigation;
open ProfileStyle;

type state = {
  username: string,
  email: string,
  twitter: string,
  github: string,
  isEditing: bool,
};

type action =
  | ToggleForm
  | OnChange(string, string)
  | SetUsername(string)
  | SetEmail(string);

[@react.component]
let make = (~navigation: Navigation.t) => {
  // Js.log2("client", client);
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ToggleForm => {...state, isEditing: !state.isEditing}
        | SetUsername(string) => {...state, username: string}
        | SetEmail(string) => {...state, email: string}
        | OnChange(key, value) =>
          switch (key) {
          | "twitter" => {...state, twitter: value}
          | "email" => {...state, email: value}
          | _ => state
          }
        },
      {
        username: "",
        email: "",
        twitter: "_idkjs",
        github: "idkjs",
        isEditing: false,
      },
    );
  let handleOnChange = (key, value) => {
    dispatch(OnChange(key, value));
  };
  let signOutAsync = (~navigation) => {
    Auth.signOut();
    Utils.UserSession.clearToken() |> ignore;
    navigation->Navigation.navigate("AuthLoading");
  };

  React.useEffect0(() => {
    dispatch(SetEmail(Session.getEmail()));
    dispatch(SetUsername(Session.getUser()));
    None;
  });
  // Js.log2("user", Session.getUser());
  let buttonText = state.isEditing ? "Save" : "Edit Profile";
  <View style=styles##container>
    <BaseHeader />
    <View style=styles##profileContainer>
      <Text style=styles##username> {state.username |> React.string} </Text>
      <Text style=styles##email> {state.email |> React.string} </Text>
      {!state.isEditing
         ? <Social twitter={state.twitter} github={state.github} />
         : <Form
             onChange=handleOnChange
             twitter={state.twitter}
             github={state.github}
           />}
      <View style=styles##buttonContainer>
        <TouchableHighlight
          onPress={_ => dispatch(ToggleForm)} underlayColor="transparent">
          <View style=styles##button>
            <Text style=styles##buttonText>
              {buttonText |> React.string}
            </Text>
          </View>
        </TouchableHighlight>
        <TouchableHighlight
          onPress={_ => signOutAsync(~navigation)}
          underlayColor="transparent">
          <View style=styles##button>
            <Text style=styles##buttonText>
              {"Sign out" |> React.string}
            </Text>
          </View>
        </TouchableHighlight>
      </View>
    </View>
  </View>;
};
module MapIcon = {
  [@react.component]
  let make = () => {
    <FontAwesome
      // <Icon color=Colors.highlight name="logo-twitter" size=20 />;
      name=`user
      size=20
      color=Colors.highlight
    />;
  };
};
// module ProfileIcon = {
//   open ReasonExpoVectorIcons;
//   [@react.component]
//   let make = () => {
//     <Ionicons name=`iosSearch size=20 color="green" />
//   };
// };
let tabBarIcon = NavigationOptions.TabBarIcon.element(<MapIcon />);
make->NavigationOptions.setNavigationOptions(
  NavigationOptions.t(
    ~title="Profile",
    // ~tabBarIcon=NavigationOptions.TabBarIcon.element(<MapIcon />),
    ~tabBarIcon=Helpers.tabBarIcon(~name=`user),
    (),
  ),
) /* )*/ /*   NavigationOptions.t(~title="Profile", ())*/;
// make->NavigationOptions.setNavigationOptions(