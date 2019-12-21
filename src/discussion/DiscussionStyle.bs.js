// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Theme from "../Theme.bs.js";
import * as ReactNative from "react-native";

var styles = ReactNative.StyleSheet.create({
      buttonContainer: {
        flexDirection: "row"
      },
      input: {
        fontFamily: Theme.Typography.primary,
        fontSize: 16,
        backgroundColor: "#fff",
        height: 50,
        paddingHorizontal: 8,
        width: Theme.dimensions.width
      },
      container: {
        backgroundColor: Theme.Colors.primary,
        flex: 1
      },
      scrollViewContainer: {
        flex: 1,
        paddingBottom: 50
      },
      time: {
        color: "rgba(0, 0, 0, .5)"
      },
      message: {
        color: Theme.Colors.primaryText,
        fontFamily: Theme.Typography.primary,
        fontSize: 16
      },
      createdBy: {
        color: Theme.Colors.highlight,
        fontFamily: Theme.Typography.primary,
        marginTop: 4
      },
      comment: {
        backgroundColor: Theme.Colors.primaryDark,
        borderBottomColor: "#25223e",
        borderBottomWidth: 1,
        borderRadius: 5,
        paddingHorizontal: 10,
        paddingVertical: 15
      }
    });

var logo = Theme.logo;

var dimensions = Theme.dimensions;

var primaryText = Theme.primaryText;

var Colors = Theme.Colors;

var Typography = Theme.Typography;

export {
  logo ,
  dimensions ,
  primaryText ,
  Colors ,
  Typography ,
  styles ,
  
}
/* styles Not a pure module */