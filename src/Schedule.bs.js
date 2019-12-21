// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as API from "./aws/API.bs.js";
import * as Curry from "bs-platform/lib/es6/curry.js";
import * as Pager from "./Pager.bs.js";
import * as Theme from "./Theme.bs.js";
import * as React from "react";
import * as Helpers from "./utils/Helpers.bs.js";
import * as Queries from "./graphql/Queries.bs.js";
import * as Belt_Array from "bs-platform/lib/es6/belt_Array.js";
import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as ScheduleItem from "./components/ScheduleItem.bs.js";
import * as ReactNative from "react-native";
import * as ScheduleStyle from "./components/ScheduleStyle.bs.js";
import * as ReactNavigation from "react-navigation";

var day1 = "November 10";

var day2 = "November 11";

function Schedule$Schedule(Props) {
  var navigation = Props.navigation;
  var match = React.useState((function () {
          return day1;
        }));
  var setCurrentDate = match[1];
  var currentDate = match[0];
  var match$1 = React.useState((function () {
          return /* array */[];
        }));
  var setTalkData = match$1[1];
  var filteredTalks = Belt_Array.keep(match$1[0], (function (talk) {
          var talkData = Belt_Option.getWithDefault(talk.date, "");
          return talkData === currentDate;
        }));
  var handleTalkData = function (response) {
    return response.data.listTalks.items;
  };
  React.useEffect((function () {
          var listTalks = Queries.ListTalks.make(/* () */0);
          var graphqlOperation_query = listTalks.query;
          var graphqlOperation_variables = Caml_option.some(listTalks.variables);
          var graphqlOperation = {
            query: graphqlOperation_query,
            variables: graphqlOperation_variables
          };
          API.mutate(graphqlOperation).then((function (response) {
                  var newTalkData = handleTalkData(response);
                  return Promise.resolve(Curry._1(setTalkData, (function (param) {
                                    return newTalkData;
                                  })));
                }));
          return ;
        }));
  return React.createElement(ReactNative.View, {
              style: ScheduleStyle.styles.container,
              children: null
            }, React.createElement(ReactNative.ScrollView, {
                  children: React.createElement(ReactNative.View, {
                        style: ScheduleStyle.styles.listContainer,
                        children: React.createElement(ReactNative.FlatList, {
                              data: filteredTalks,
                              keyExtractor: (function (talk, param) {
                                  return talk.id;
                                }),
                              renderItem: (function (props) {
                                  return React.createElement(ScheduleItem.make, {
                                              talk: props.item,
                                              onPress: (function (param) {
                                                  navigation.navigate("Talk", {
                                                        talk: props.item
                                                      });
                                                  return /* () */0;
                                                })
                                            });
                                })
                            })
                      })
                }), React.createElement(ReactNative.View, {
                  style: ScheduleStyle.styles.tabBottomContainer,
                  children: null
                }, React.createElement(ReactNative.TouchableHighlight, {
                      underlayColor: Theme.Colors.primaryDark,
                      onPress: (function (param) {
                          return Curry._1(setCurrentDate, (function (param) {
                                        return day1;
                                      }));
                        }),
                      children: React.createElement(ReactNative.View, {
                            style: ScheduleStyle.styles.bottomButton,
                            children: React.createElement(ReactNative.Text, {
                                  style: ScheduleStyle.styles.bottomButtonText,
                                  children: day1
                                })
                          })
                    }), React.createElement(ReactNative.TouchableHighlight, {
                      underlayColor: Theme.Colors.primaryDark,
                      onPress: (function (param) {
                          return Curry._1(setCurrentDate, (function (param) {
                                        return day2;
                                      }));
                        }),
                      children: React.createElement(ReactNative.View, {
                            style: ScheduleStyle.styles.bottomButton,
                            children: React.createElement(ReactNative.Text, {
                                  style: ScheduleStyle.styles.bottomButtonText,
                                  children: day2
                                })
                          })
                    })));
}

Schedule$Schedule.navigationOptions = {
  headerLeft: React.createElement(ReactNative.Image, {
        resizeMode: "contain",
        source: Theme.logo,
        style: ScheduleStyle.styles.logo
      })
};

var Schedule = {
  day1: day1,
  day2: day2,
  make: Schedule$Schedule
};

var defaultNavigationOptions = {
  headerStyle: {
    backgroundColor: Theme.Colors.primary,
    borderBottomColor: Theme.Colors.primaryLight,
    borderBottomWidth: 1
  }
};

var configOptions = {
  defaultNavigationOptions: defaultNavigationOptions
};

var make = ReactNavigation.createStackNavigator({
      Schedule: {
        screen: Schedule$Schedule
      },
      Talk: {
        screen: Pager.make
      }
    }, configOptions);

make.navigationOptions = {
  title: "Schedule",
  tabBarIcon: Helpers.tabBarIcon(/* calendar */-14065986)
};

export {
  Schedule ,
  defaultNavigationOptions ,
  configOptions ,
  make ,
  
}
/*  Not a pure module */
