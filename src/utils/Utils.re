external unsafeCast : ReactNavigation.NavigationOptions.t => Js.t('a) = "%identity";
external unsafeCast2 : ReactNavigation.Navigation.t => Js.t('a) = "%identity";
let nullableToOption = stringOrNull =>
  Js.Promise.resolve(stringOrNull->Js.Null.toOption);
// open ReactNavigation;
// let header = Navigation.header(`Null(Js.null));
let namespace = "conf-in-box-";

module UserSession = {
  open ReactNative;
  let userNameToken = namespace ++ "username";
  let getToken = AsyncStorage.getItem(namespace);
  let getUser = AsyncStorage.getItem(userNameToken);
  let setToken = token => AsyncStorage.setItem(namespace, token);
  let clearToken = () => AsyncStorage.removeItem(namespace);
};

external toString: 'a => string = "%identity";

let sortCreatedBy = arr =>
  arr
  ->Belt.SortArray.stableSortBy((a1, a2) =>
      compare(a1##createdAt, a2##createdAt)
    )
  ->Belt.Array.reverse;
let getUsernameFromStorage = () =>
  ReactNative.AsyncStorage.getItem(namespace ++ "username")
  |> Js.Promise.then_(user => {
       Js.log2("AsyncStorage.getItem: ", user);
       let usr = Js.nullToOption(user)->toString;
       Js.log2("AsyncStorage._USR: ", usr);
       //  handleUsername(_ => usr);
       //  setUsername(_ => usr);
       //  Js.log2("AsyncStorage.getItem:CHECKING_USERNAME_FROMSTATE ", username);
       //  createTestMessage();
       Js.Promise.resolve(usr);
     });
open ReactNative;
let loadFonts =
  Js.Promise.resolve(
    Expo.Font.loadAsync([
      (
        "Gotham Rounded",
        Packager.require("../assets/fonts/GothamRnd-Light.otf"),
      ),
      (
        "GothamRnd Medium",
        Packager.require("../assets/fonts/GothamRnd-Medium.otf"),
      ),
      (
        "Gotham Bold",
        Packager.require("../assets/fonts/GothamRnd-Bold.otf"),
      ),
    ]),
  );

[@bs.val]
external jsonStringify: ('a, Js.Nullable.t(unit), int) => string =
  "JSON.stringify";

let getInputValue = (e): string => ReactEvent.Form.target(e)##value;
let getSyntheticInputValue = (e): string => ReactEvent.Synthetic.target(e)##value;

let extractMessageFrom = event => {
  let event = event->Obj.magic;
  /* get the message value on event and post to ui */
  let message = event##value##data##onCreateMessage##message;
  message;
};

external convertRecordJsObj: 'a => Js.t({..}) = "%identity";
external convertToJsObj: Js.Json.t => Js.t({..}) = "%identity";
external convertStrToJsObj: Js.Json.t => Js.t({..}) = "%identity";

external convertToString: string => Js.t({..}) = "%identity";

let parseJsonConvertJsObj = str => str |> Js.Json.parseExn |> convertToJsObj;
let parseStrConvertJsObj = str => str |> Js.Json.parseExn |> convertStrToJsObj;