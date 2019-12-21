open ReactNative;
open ReactNavigation;
open ScheduleStyle;
// open Types;
module Schedule = {
  type talk = TalkType.t;
  type state = {
    talks: TalkType.talks,
    currentDate: string,
    loading: bool,
  };
  let day1 = "November 10";
  let day2 = "November 11";

  [@react.component]
  let make = (~navigation: Navigation.t) => {
    let (currentDate, setCurrentDate) = React.useState(() => day1);
    let (talkData, setTalkData) = React.useState(() => [||]);
    // let (loading, setLoading) = React.useState(() => false);
    let toggleDate = date => {
      setCurrentDate(date);
    };
    let filteredTalks =
      talkData->Belt.Array.keep(talk => {
        let talkData = Belt.Option.getWithDefault(talk##date, "");
        talkData === currentDate;
      });

    let handleTalkData = response => {
      let response = response->Obj.magic;
      /* get the message value on response and post to ui */
      let talkData = response##data##listTalks##items;
      talkData;
    };
    React.useEffect(() => {
      let listTalks = Queries.ListTalks.make();
      let graphqlOperation: APITypes.graphqlOperation = {
        query: listTalks##query,
        variables: Some(listTalks##variables),
      };
      API.mutate(graphqlOperation)
      |> Js.Promise.then_(response => {
           let newTalkData = handleTalkData(response);
          //  let mergedData = Belt.Array.concat(newTalkData,talkData)
          //  Js.log2("data", talkData);
          //  setLoading(_ => false);
           setTalkData(_ => newTalkData)
           //  Js.log2("reason_broadcaster_mutation", response)
           |> Js.Promise.resolve;
         })
      |> ignore;
      // let talkData =
      //     Belt.Option.map(response##data##listTalks => listTalks##items
      //     ->Belt.Option.getWithDefault([||])
      //     ->Belt.Array.keepMap(item => item);
      // setTalkData(_=>Some(talkData));
      None;
    });

    <View style=styles##container>
      // {loading
      //    ? <View style=styles##loading>
      //        <ActivityIndicator
      //          size=ActivityIndicator.Size.large
      //          color="white"
      //        />
      //      </View>
      //    :
         <ScrollView>
             <View style=styles##listContainer>
               <FlatList
                 data=filteredTalks
                 keyExtractor={(talk, _) => talk##id}
                 renderItem={props => {
                   <ScheduleItem
                     // let talk = props##item;
                     onPress={_ =>
                       navigation->Navigation.navigateWithParams(
                         "Talk",
                         {"talk": props##item},
                       )
                     }
                     talk=props##item
                   />
                 }}
               />
             </View>
           </ScrollView>
      <View style=styles##tabBottomContainer>
        <TouchableHighlight
          underlayColor=Colors.primaryDark
          onPress={_ => toggleDate(_ => day1)}>
          <View style=styles##bottomButton>
            <Text style=styles##bottomButtonText>
              {day1 |> React.string}
            </Text>
          </View>
        </TouchableHighlight>
        <TouchableHighlight
          underlayColor=Colors.primaryDark
          onPress={_ => toggleDate(_ => day2)}>
          <View style=styles##bottomButton>
            <Text style=styles##bottomButtonText>
              {day2 |> React.string}
            </Text>
          </View>
        </TouchableHighlight>
      </View>
    </View>;
  };
  make->NavigationOptions.(
          setNavigationOptions(
            t(
              ~headerLeft=
                <Image
                  source=Theme.logo
                  resizeMode=`contain
                  style=styles##logo
                />,
              (),
            ),
          )
        );
};
let defaultNavigationOptions = {
  "headerStyle":
    Style.(
      style(
        ~backgroundColor=Colors.primary,
        ~borderBottomColor=Colors.primaryLight,
        ~borderBottomWidth=1.,
        (),
      )
    ),
};
let configOptions = StackUtils.config(~defaultNavigationOptions, ());

let make =
  StackNavigator.(
    makeWithConfig(
      {
        "Schedule": {
          screen: Schedule.make,
        },
        "Talk": {
          screen: Pager.make,
        },
      },
      configOptions,
    )
  );

make->NavigationOptions.setNavigationOptions(
  NavigationOptions.t(
    ~title="Schedule",
    ~tabBarIcon=Helpers.tabBarIcon(~name=`calendar),
    (),
  ),
);