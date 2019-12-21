open ReactNative;
open ReactNavigation;

module TabNavigator = {
  let tabBarStyle = Style.(style(~backgroundColor=Theme.Colors.primary, ()));
  let tabBarOptions: TabNavigator.tabBarOptions =
    TabNavigator.tabBarOptions(
      ~activeTintColor=Theme.Colors.highlight,
      ~style=tabBarStyle,
      ~inactiveTintColor="#fafafa",
      (),
    );

  let routes = {
    "Schedule": {
      screen: Schedule.make,
    },
    "Profile": {
      screen: Profile.make,
    },
    "Map": {
      screen: Map.make,
    },
  };
  let config = TabNavigator.config(~tabBarOptions, ());
  let navigator = TabNavigator.Bottom.(makeWithConfig(routes, config));

  navigator->NavigationOptions.setDynamicNavigationOptions(params => {
    let headerTintColor =
      params##navigationOptions->NavOptionsUtils.headerTintColor;
    let routeName =
      params##navigation->Navigation.state->Helpers.getActiveRoute##routeName;
    Js.log2("routeName", routeName);

    let tabBarIcon = () =>
      switch (routeName) {
      | "Schedule" => Helpers.tabBarIcon(~name=`calendar)
      | "Map" => Helpers.tabBarIcon(~name=`map)
      | _ => Helpers.tabBarIcon(~name=`user)
      };
    Js.log2("tabBarIcon", tabBarIcon);
    NavigationOptions.t(~tabBarIcon=tabBarIcon(), ~headerTintColor, ());
  });
};

module TabNavWithPropsContainer =
  AppContainer.Make({
    type screenProps = {. "token": string};
    let navigator = TabNavigator.navigator;
  });

module TabNavWithProps = {
  [@react.component]
  let make = () => {
    let (token, setToken) = React.useState(() => None);
    React.useEffect(() => {
      setToken(_ => Some(Session.getToken()));
      None;
    });

    switch (token) {
    | Some(token) =>
      let screenProps = {"token": token};

      <TabNavWithPropsContainer screenProps />;
    | None => <LoadingScreen />
    };
  };
};

[@react.component]
let make = () => {
  let (signedIn, setSignedIn) = React.useState(() => true);
  module Logr = HubLogger;
  let listener: Hub.cb =
    payload => {
      Js.log2("listener_payload", payload);
      Logr.log(Info, "listening for auth events...");
      Logr.logO(Info, payload);

      switch (payload.hubEvent) {
      | `signIn =>
        Logr.log(Info, "signIn event...");
        Logr.logO(Info, payload);

      | `signOut =>
        Logr.log(Info, "signOut event...");
        Logr.logO(Info, payload);
      | _ => Js.log2("logger", payload) |> ignore
      };
    };
  React.useEffect0(() => {
    Auth.getCurrentAuthUser()
    |> Js.Promise.then_(result => {
         //  Js.log2("Auth.getCurrentAuthUser", result);
         switch (result) {
         | Belt.Result.Ok(_user) =>
           //  Js.log2("Auth.getCurrentAuthUser:result", user);
           setSignedIn(_ => true)
         | Belt.Result.Error(err) => Js.log2("user not signed in", err)
         };
         Js.Promise.resolve(result);
       })
    |> ignore;
    let remove = Hub.listen(`auth, listener);
    // Hub.listen(`auth, listener);
    Some(() => remove);
    // None;
  });
  let renderLogo = !signedIn ? <Logo /> : React.null;
  <View style=Style.(style(~flex=1., ()))>
    renderLogo
    <LoadingScreen />
  </View>;
} /* let default = AppWithAuth.make*/;