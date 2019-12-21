// type t = {
//   id: string,
//   createdBy: option(CoursesStudents__Coach.t),
//   note: string,
//   createdAt: Js.Date.t,
// };
type t = {
  id: option(string),
  talkId: option(string),
  message: string,
  createdAt: Js.Date.t,
  createdBy: string,
  deviceId: option(string),
};

let make = (~id=?, ~message, ~createdAt, ~createdBy,~talkId=?,~deviceId=?,()) => {
  id,
  talkId,
  message,
  createdAt,
  createdBy,
  deviceId
};

let id = t => t.id;

let message = t => t.message;

let createdAt = t => t.createdAt;

let createdBy = t => t.createdBy;
let createdAtPretty = t => t.createdAt |> DateFns.format("MMMM D, YYYY");
let sort = comments =>
  comments
  |> ArrayUtils.copyAndSort((x, y) =>
       DateFns.differenceInSeconds(y.createdAt, x.createdAt) |> int_of_float
     );

let makeFromJs = comment => {
  make(
    ~id=comment##id,
    ~message=comment##message,
    ~createdAt=comment##createdAt |> DateFns.parseString,
    ~createdBy=
      comment##createdBy,
    ~deviceId=
      comment##deviceId,
  );
};