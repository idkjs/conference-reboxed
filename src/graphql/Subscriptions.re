
module OnCreateTalk = [%graphql
  {|
    subscription OnCreateTalk {
  onCreateTalk {
    id
    name
    speakerName
    speakerBio
    time
    location
    summary
    twitter
    github
    comments {
      items {
        id
        talkId
        message
        createdAt
        deviceId
      }
      nextToken
    }
  }
}
|}
];

module OnUpdateTalk = [%graphql
  {|
    subscription OnUpdateTalk {
  onUpdateTalk {
    id
    name
    speakerName
    speakerBio
    time
    location
    summary
    twitter
    github
    comments {
      items {
        id
        talkId
        message
        createdAt
        deviceId
      }
      nextToken
    }
  }
}
|}
];

module OnDeleteTalk = [%graphql
  {|
    subscription OnDeleteTalk {
  onDeleteTalk {
    id
    name
    speakerName
    speakerBio
    time
    location
    summary
    twitter
    github
    comments {
      items {
        id
        talkId
        message
        createdAt
        deviceId
      }
      nextToken
    }
  }
}
|}
];

module OnCreateComment = [%graphql
  {|
 subscription onCreateCommentWithId($talkId: ID!) {
  onCreateCommentWithId(talkId: $talkId) {
    id
    talkId
    talk {
      id
      name
      speakerName
      speakerBio
      time
      location
      summary
      twitter
      github
      comments {
        nextToken
      }
    }
    message
    createdAt
    createdBy
    deviceId
  }
}
|}
];

module OnUpdateComment = [%graphql
  {|
    subscription OnUpdateComment {
  onUpdateComment {
    id
    talkId
    talk {
      id
      name
      speakerName
      speakerBio
      time
      location
      summary
      twitter
      github
      comments {
        nextToken
      }
    }
    message
    createdAt
    deviceId
  }
}
|}
];

module OnDeleteComment = [%graphql
  {|
    subscription OnDeleteComment {
  onDeleteComment {
    id
    talkId
    talk {
      id
      name
      speakerName
      speakerBio
      time
      location
      summary
      twitter
      github
      comments {
        nextToken
      }
    }
    message
    createdAt
    deviceId
  }
}
|}
];

module OnCreateReport = [%graphql
  {|
    subscription OnCreateReport {
  onCreateReport {
    id
    commentId
    comment
    talkTitle
    deviceId
  }
}
|}
];

module OnUpdateReport = [%graphql
  {|
    subscription OnUpdateReport {
  onUpdateReport {
    id
    commentId
    comment
    talkTitle
    deviceId
  }
}
|}
];

module OnDeleteReport = [%graphql
  {|
    subscription OnDeleteReport {
  onDeleteReport {
    id
    commentId
    comment
    talkTitle
    deviceId
  }
}
|}
];