open ReactNative;
open Expo;

module Authenticator = {
  open Main;
  open WithAuthenticator;
  let makeProps = TabNavWithProps.makeProps;
  let make =
    withAuthenticator(TabNavWithProps.make, ~theme=AmplifyTheme.theme, ());
};
let styles =
  StyleSheet.create(
    Style.{
      "container":
        style(~flex=1., ~backgroundColor=Theme.Colors.primaryLight, ()),
    },
  );
YellowBox.ignoreWarnings([|
  "Possible Unhandled Promise Rejection",
  "Remote debugger",
  "UIManager['getConstants']",
|]);

Amplify.configure(AwsExports.config);
API.configure(AwsExports.config);
let loadResourcesAsync = () => {
  Js.Promise.resolve(
    Font.loadAsync([
      (
        "Gotham Rounded",
        Packager.require("./assets/fonts/GothamRnd-Light.otf"),
      ),
      (
        "GothamRnd Medium",
        Packager.require("./assets/fonts/GothamRnd-Medium.otf"),
      ),
      ("Gotham Bold", Packager.require("./assets/fonts/GothamRnd-Bold.otf")),
    ]),
  )
  |> ignore;
};

let handleLoadingError = error => {
  // In this case, you might want to report the error to your error reporting
  // service, for example Sentry
  error->Js.Console.warn;
};

[@react.component]
let app = () => {
  let (isLoadingComplete, setLoadingComplete) = React.useState(() => false);

  !isLoadingComplete
    ? <AppLoading
        startAsync={_ => loadResourcesAsync() |> Js.Promise.resolve}
        onError=handleLoadingError
        onFinish={_ => setLoadingComplete(_ => true)}
      />
    : <View style=styles##container>
        <StatusBar barStyle=`darkContent />
        <Authenticator />
      </View>;
};
// let default = app;