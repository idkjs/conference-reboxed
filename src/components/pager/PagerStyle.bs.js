// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Theme from "../../Theme.bs.js";
import * as ReactNative from "react-native";

var styles = ReactNative.StyleSheet.create({
      container: {
        backgroundColor: Theme.Colors.primaryDark,
        flex: 1
      },
      button: {
        borderBottomWidth: 2,
        alignItems: "center",
        height: 45,
        justifyContent: "center",
        width: Theme.dimensions.width / 2
      },
      buttonContainer: {
        flex: 1
      },
      buttonText: {
        color: Theme.Colors.primaryText,
        fontFamily: Theme.Typography.primary,
        textAlign: "center"
      },
      tabContainer: {
        flexDirection: "row"
      },
      indexSelected: {
        backgroundColor: Theme.Colors.primary2,
        borderBottomColor: Theme.Colors.highlight
      },
      indexNotSelected: {
        backgroundColor: Theme.Colors.primary,
        borderBottomColor: Theme.Colors.primary
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