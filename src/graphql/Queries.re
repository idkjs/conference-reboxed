// GraphQL query for getting my todos
module GetTalkQuery = [%graphql
  {|
    query GetTalk($id: ID!) {
  getTalk(id: $id) {
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

module ListTalks = [%graphql
  {|
    query ListTalks {
  listTalks(limit: 500) {
    items {
      id
      name
      speakerName
      speakerBio
      time
      speakerAvatar
      location
      summary
      timeStamp
      date
      twitter
      github
    }
    nextToken
  }
}
  |}
];

// // GraphQL mutation for inserting a todo
module GetCommentQuery = [%graphql
  {|
query GetComment($id: ID!) {
  getComment(id: $id) {
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

module ListCommentsQuery = [%graphql
  {|
query GetComment($id: ID!) {
  getComment(id: $id) {
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

module ListCommentsByTalkIdQuery = [%graphql
  {|
query listCommentsByTalkId($talkId: ID!) {
  listCommentsByTalkId(talkId: $talkId) {
    items {
      message
      createdAt
      createdBy
    }
  }
}
  |}
];

module ListReportsQuery = [%graphql
  {|
query ListReports(
  $filter: ModelReportFilterInput
  $limit: Int
  $nextToken: String
) {
  listReports(filter: $filter, limit: $limit, nextToken: $nextToken) {
    items {
      id
      commentId
      comment
      talkTitle
      deviceId
    }
    nextToken
  }
}
  |}
];


