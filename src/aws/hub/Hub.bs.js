// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Core from "@aws-amplify/core";

function listen(string, callback) {
  Core.Hub.listen(string, callback);
  return /* () */0;
}

function remove(string, callback) {
  Core.Hub.remove(string, callback);
  return /* () */0;
}

export {
  listen ,
  remove ,
  
}
/* @aws-amplify/core Not a pure module */