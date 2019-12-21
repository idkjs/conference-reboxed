open ReactNative;
open DiscussionStyle;

[@react.component]
let make = (~comments) => {
  <>
    <View style=styles##scrollViewContainer>
      {comments->Array.length > 1
         ? <ScrollView>
             {!(Array.length(comments) > 0)
                ? <View style=styles##comment>
                    <Text style=styles##message>
                      {"No comments yet!" |> React.string}
                    </Text>
                  </View>
                : React.null}
             {comments->Belt.Array.mapWithIndex((idx, c: APITypes.comment) =>
                <View key={string_of_int(idx)} style=styles##comment>
                  <Text style=styles##message>
                    {"message: " ++ c.message |> React.string}
                  </Text>
                  <Text style=styles##createdBy>
                    {"createdBy: " ++ c.createdBy |> React.string}
                  </Text>
                  <Text style=styles##createdBy>
                    {"createdAt: " ++ c.createdAt |> React.string}
                  </Text>
                </View>
              )
              |> React.array}
           </ScrollView>
         : <View style=styles##comment>
             <Text style=styles##message>
               {"No comments yet!" |> React.string}
             </Text>
           </View>}
    </View>
    // <Button title="Send" onPress={event=>onButtonPress(event)} />
  </>;
};