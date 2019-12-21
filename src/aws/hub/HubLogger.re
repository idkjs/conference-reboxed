type level =
  | Error
  | Warn
  | Info
  | Verbose
  | Debug
  | Silly;
let levelToString =
  fun
  | Error => "ERROR"
  | Warn => "WARN"
  | Info => "INFO"
  | Verbose => "VERBOSE"
  | Debug => "DEBUG"
  | Silly => "SILLY";

type t;
type options;
[@bs.obj]
external options: (~name: string=?, ~level: string=?, unit) => options = "";
/*
 [@bs.module "winston"] external createLogger: options => t = "";
 let createLogger = (~level=?, ~format=?, ~defaultMeta=?, ~transports=?, ()) =>
   options(
     ~level=?Belt.Option.map(level, levelToString),
     ~format?,
     ~defaultMeta?,
     ~transports?,
     (),
   )
   |> createLogger; */

[@bs.module "@aws-amplify/core"] [@bs.new]
external createLogger: options => t = "Logger";
let createLogger = (~name=?, ~level=?, ()) =>
  options(~name?, ~level=?Belt.Option.map(level, levelToString), ())
  |> createLogger;

[@bs.send] external error: (t, string) => unit = "error";
[@bs.send] external errorO: (t, Js.t({..})) => unit = "error";
[@bs.send] external warn: (t, string) => unit = "warn";
[@bs.send] external warnO: (t, Js.t({..})) => unit = "warn";
[@bs.send] external info: (t, string) => unit = "info";
[@bs.send] external infoO: (t, Js.t({..})) => unit = "info";
[@bs.send] external verbose: (t, string) => unit = "verbose";
[@bs.send] external verboseO: (t, Js.t({..})) => unit = "verbose";
[@bs.send] external debug: (t, string) => unit = "debug";
[@bs.send] external debugO: (t, Js.t({..})) => unit = "debug";

[@bs.send] external log: (t, string, string) => unit = "log";
// [@bs.send] external logO: (t, string, Js.t({..})) => unit = "log";
[@bs.send] external logO: (t, string, APITypes.payloadJs) => unit = "log";
let logger = createLogger(~name="UserProvider", ~level=Info, ());
let log = (level, message) => log(logger, levelToString(level), message);
let logO = (level, message) => logO(logger, levelToString(level), message);
// let info = (level, message) => info(logger, levelToString(level), message);