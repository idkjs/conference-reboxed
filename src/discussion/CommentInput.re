open ReactNative;
open DiscussionStyle;
[@react.component]
let make = (~message,~handleChangeText,~createComment) => {
        <View>
          <TextInput
            value=message
            onChangeText={value => handleChangeText(_ => value)}
            onSubmitEditing={_ => createComment |> ignore}
            style = styles##input
            autoCapitalize=`none
            placeholder="Discuss this talk."
            autoCorrect=false
          />
        </View>;
};