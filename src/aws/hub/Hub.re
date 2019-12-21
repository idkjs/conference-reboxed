// module Logger = {
//   [@bs.send] external log: (t, string, string) => unit = "log";
//   // [@bs.send] external logO: (t, string, Js.t({..})) => unit = "log";
//   [@bs.send] external logO: (t, string, APITypes.payloadJs) => unit = "log";
//   let logger = createLogger(~name="UserProvider", ~level=Info, ());
//   let log = (level, message) => log(logger, levelToString(level), message);
//   let logO = (level, message) => logO(logger, levelToString(level), message);
// }
type t = string;

[@bs.inline]
let active = "active";
// type event = [ | `signIn | `signUp | `signOut | `signIn_failure | `configured];
[@bs.inline]
let signIn = "signIn";

[@bs.inline]
let signUp = "signUp";

[@bs.inline]
let signOut = "signOut";

[@bs.inline]
let signIn_failure = "signIn_failure";

[@bs.inline]
let configured = "configured";

// type payload('a) = {
//   string,
//   data: option('a),
//   message: option(string),
// };

// type cb = payload(Js.t({.})) => unit;
// [@bs.scope "Hub"] [@bs.module "aws-amplify"]
// external listen: ([@bs.string] [ | `change(t => cb)]) => unit = "listen";

// [@bs.scope "Hub"] [@bs.module "aws-amplify"]
// external remove: ([@bs.string] [ | `change(t => cb)]) => unit = "remove";
type channel = [
  | `core
  | `auth
  | `api
  | `analytics
  | `interactions
  | `pubsub
  | `storage
  | `xr
];

type cb = APITypes.payloadJs => unit;
[@bs.module "@aws-amplify/core"] external hub: t = "Hub";
[@bs.send] external listen: (t, channel, cb) => unit = "listen";
[@bs.send] external remove: (t, channel, cb) => unit = "remove";

let listen = (string, callback) => listen(hub, string, callback);
let remove = (string, callback) => remove(hub, string, callback);