// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as AwsAmplify from "aws-amplify";

function getCurrentAuthUser(param) {
  return AwsAmplify.Auth.currentAuthenticatedUser();
}

var currentAuthUser = AwsAmplify.Auth.currentAuthenticatedUser().then((function (res) {
        return Promise.resolve(res);
      }));

export {
  getCurrentAuthUser ,
  currentAuthUser ,
  
}
/* currentAuthUser Not a pure module */
