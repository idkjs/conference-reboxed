// type amp;
// [@bs.module "@aws-amplify/auth/lib"] external amplify: amp = "default";

// type config;
// [@bs.module "./aws-exports.js"] external awsConfig: config = "default";

// type configure;
// [@bs.send] external configure: (amp, config) => configure = "configure";

// /* let amplify = amplify; */
// let configure = configure(amplify, awsConfig);
type t;
[@bs.module "@aws-amplify/core"] external amplify: t = "default";
[@bs.send] external configure: (t, AwsExports.t) => unit = "configure";
let configure = config => configure(amplify, config);