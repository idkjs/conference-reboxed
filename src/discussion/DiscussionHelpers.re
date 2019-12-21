let newComment = (~talkId, ~message, ~deviceId): APITypes.comment => {
  createdAt: Js.Date.now()->Js.Float.toString,
  id: None,
  talkId: Some(talkId),
  message,
  createdBy: UserSession.getName(),
  deviceId: Some(deviceId),
};
  let extractMessageFrom = event => {
    /* use Obj.magic to change time, otherwise code in Wonka.subscribe breaks. */
    let event = event->Obj.magic;
    /* get the message value on event and post to ui */
    let newItem = event##value##data;
    Js.log2("extractMessageFrom_newItem: ", newItem);
    newItem;
  };
    let scroller = () => {
      let scrollViewRef = React.useRef(Js.Nullable.null);
      let cancelTimer = (timerId, ()) => Js.Global.clearTimeout(timerId);
      let setTimeout = Js.Global.setTimeout;
      let timeoutId = scrollView =>
        setTimeout(() => scrollView |> ReactNative.ScrollView.scrollToEnd, 50);
      switch (scrollViewRef->React.Ref.current->Js.Nullable.toOption) {
      | Some(scrollView) => cancelTimer(timeoutId(scrollView)) |> ignore
      | _ => ()
      };
    };
    let handleSetComments = (~newItem,~comments,~setComments )=> {
      open APITypes;
      let newCommentsArray = Array.append([|newItem|], comments);
      let sortedComments =
        newCommentsArray
        ->Belt.SortArray.stableSortBy((a1, a2) =>
            compare(a1.createdAt, a2.createdAt)
          )
        ->Belt.Array.reverse;
      Js.log2("newCommentsArray[0]: ", newCommentsArray[0]);
      Js.log2("newCommentsArray: ", newCommentsArray);
      Js.log2("sortedComments[0]: ", sortedComments[0]);
      Js.log2("sortedComments: ", sortedComments);
      setComments(_ => sortedComments);
      /* call scroller to get list to scroll to bottom. Not working */
      scroller();
    };
open ReactNative;
let useSubscribed = () => {
  // let (appState, setAppState) = React.useState(_ => AppState.currentState);
  let (subscribed, setSubscribed) = React.useState(_ => false);
  let appState = AppState.currentState;
  let isConnected =
    switch (ReactNativeNetInfo.useNetInfo()##details->Js.Null.toOption) {
    | None => false
    | Some(_x) => true
    };
  React.useEffect2(
    () => {
      switch (appState, isConnected) {
      | (_active, true) => setSubscribed(_ => true)
      | (_, _) => setSubscribed(_ => false)
      };
      None;
    },
    (appState, isConnected),
  );
  subscribed;
};