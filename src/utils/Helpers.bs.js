// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Theme from "../Theme.bs.js";
import * as React from "react";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as ReactNative from "react-native";
import * as FontAwesome from "@expo/vector-icons";

function headerIcon($staropt$star, source) {
  var additionalStyle = $staropt$star !== undefined ? Caml_option.valFromOption($staropt$star) : { };
  return React.createElement(ReactNative.Image, {
              source: source,
              style: /* array */[
                {
                  height: 24,
                  margin: 11,
                  width: 24
                },
                additionalStyle
              ]
            });
}

function tabBarIcon(name) {
  return (function (props) {
      var match = props.focused;
      return React.createElement(FontAwesome.FontAwesome, {
                  name: (function () {
                        switch (name) {
                          case -14065986 :
                              return "calendar";
                          case 5442204 :
                              return "map";
                          case -844262837 :
                              return "user";
                          
                        }
                      })(),
                  size: 20,
                  color: match ? Theme.Colors.highlight : "#fafafa"
                });
    });
}

function getActiveRoute(_route) {
  while(true) {
    var route = _route;
    var match = route.routes;
    if (match !== undefined) {
      var routes = match;
      var routeCount = routes.length;
      if (routeCount === 0 || route.index >= routeCount) {
        return route;
      } else {
        _route = routes[route.index];
        continue ;
      }
    } else {
      return route;
    }
  };
}

export {
  headerIcon ,
  tabBarIcon ,
  getActiveRoute ,
  
}
/* Theme Not a pure module */
