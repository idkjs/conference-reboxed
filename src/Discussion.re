open ReactNative;
open ReactNavigation;
open DiscussionStyle;

let deviceId = Expo.Constants.deviceId;
let width = dimensions##width;
[@react.component]
let make = (~navigation: Navigation.t) => {
  let (message, setMessage) = React.useState(() => "");
  let (comments, setComments) = React.useState(() => [||]);
  let subscribed = DiscussionHelpers.useSubscribed();

  let talkId = Utils.unsafeCast2(navigation)##state##params##talk##id;
  React.useEffect1(() => {
    let subRequest = Subscriptions.OnCreateComment.make(~talkId, ());
    let graphqlOperation: APITypes.graphqlOperation = {
      query: subRequest##query,
      variables: Some(subRequest##variables),
    };
    let source = API.subscribe(graphqlOperation);

    let subscription =
      source
      |> Wonka.fromObservable
      |> Wonka.subscribe((. event) => {
           Js.log2("subscription_event", event);
           Js.log2("subscribed", subscribed);
           subscribed
             ? DiscussionHelpers.(
                 extractMessageFrom(event)
                 |> handleSetComments(~newItem=_, ~comments, ~setComments)
               )
             : ();
         });
    Some(() => subscription.unsubscribe());
  },[|subscribed|]);

  React.useEffect(() => {
    let sortComments = (comments: array(APITypes.comment)) =>
      comments->Belt.SortArray.stableSortBy((a1, a2) =>
        compare(a1.createdAt, a2.createdAt)
      );
    let commentsRequest = Queries.ListCommentsByTalkIdQuery.make(~talkId, ());
    let graphqlOperation: APITypes.graphqlOperation = {
      query: commentsRequest##query,
      variables: Some(commentsRequest##variables),
    };
    API.query(graphqlOperation)
    |> Js.Promise.then_(response => {
         let commentsResponse =
           response##data##listCommentsByTalkId##items
           ->Belt.Array.map(APITypes.commentToRecord);
         let comments = sortComments(commentsResponse);
         setComments(_ => comments) |> Js.Promise.resolve;
       })
    |> ignore;
    None;
  });

  let handleResponse = response => {
    /* use Obj.magic to change time, otherwise code in Wonka.subscribe breaks. */
    let response = response->Obj.magic;
    Js.log2("createMessageHandleResponse: ", response);
    /* get the message value on event and post to ui */
    let onCreateCommentWithId = response##data##createComment;
    Js.log2("extractMessageFrom_newItem: ", onCreateCommentWithId);
    let onCreateCommentWithIdDeviceId = response##data##createComment##deviceId;
    Js.log2("onCreateCommentWithIdDeviceId: ", onCreateCommentWithIdDeviceId);
    Js.log2("onCreateCommentWithIdDeviceId === deviceId: ", (onCreateCommentWithIdDeviceId === deviceId));
    Js.log2("deviceId: ", deviceId);
let sameDeviceIds = onCreateCommentWithIdDeviceId === deviceId;
    sameDeviceIds
      ? DiscussionHelpers.(
          handleSetComments(~newItem=onCreateCommentWithId, ~comments, ~setComments)
        )
      : ();
  };

  let createMessage: ReactNative.TextInput.editingEvent => unit =
    event => {
      let timestamp = event##nativeEvent##text;
      Js.log2("timestamp", timestamp);
      let newComment: APITypes.comment = {
        createdAt: Js.Date.now()->Js.Float.toString,
        id: None,
        talkId: Some(talkId),
        message,
        createdBy: UserSession.getName(),
        deviceId: Some(Expo.Constants.deviceId),
      };
      Js.log2("newComment", newComment);
      let comments = Array.append(comments, [|newComment|]);
      setComments(_ => comments);

      let input = newComment->Utils.convertRecordJsObj;
      let mutationRequest = Mutations.CreateComment.make(~input, ());
      let graphqlOperation: APITypes.graphqlOperation = {
        query: mutationRequest##query,
        variables: Some(mutationRequest##variables),
      };

      API.mutate(graphqlOperation)
      |> Js.Promise.then_(response => {
           /* checks that deviceId on incoming matches this deviceId the calls handleSetComments if true, then calls scroller to get list to scroll to bottom. Scroller not working... */
           handleResponse(response);

           Js.Promise.resolve();
         })
      |> Js.Promise.catch(err => Js.Promise.resolve(Js.log2("ERROR", err)))
      |> ignore;
      setMessage(_ => "");
      ();
    };

  let onChangeText = message => setMessage(message);

  <KeyboardAvoidingView
    accessibilityViewIsModal=true
    keyboardVerticalOffset=130.
    behavior=`padding
    style=styles##container>
    <DiscussionHistory comments />
    <View>
      <TextInput
        value=message
        onChangeText={value => onChangeText(_ => value)}
        onSubmitEditing=createMessage
        autoCapitalize=`none
        style=styles##input
        placeholder="Discuss this talk."
        autoCorrect=false
      />
    </View>
  </KeyboardAvoidingView>;
  // <Button title="Send" onPress={event=>onButtonPress(event)} />
};

make->NavigationOptions.(setNavigationOptions(t(~title="Discussion", ())));
