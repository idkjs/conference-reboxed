// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Belt_Option from "bs-platform/lib/es6/belt_Option.js";
import * as Json_decode from "@glennsl/bs-json/src/Json_decode.bs.js";

function decode(json) {
  return {
          id: Json_decode.field("id", Json_decode.string, json),
          name: Json_decode.field("name", Json_decode.string, json),
          speakerName: Json_decode.field("speakerName", Json_decode.string, json),
          speakerBio: Json_decode.field("speakerBio", Json_decode.string, json),
          speakerAvatar: Json_decode.optional((function (param) {
                  return Json_decode.field("speakerAvatar", Json_decode.string, param);
                }), json),
          time: Json_decode.optional((function (param) {
                  return Json_decode.field("time", Json_decode.string, param);
                }), json),
          location: Json_decode.optional((function (param) {
                  return Json_decode.field("location", Json_decode.string, param);
                }), json),
          summary: Json_decode.field("summary", Json_decode.string, json),
          timeStamp: Json_decode.optional((function (param) {
                  return Json_decode.field("timeStamp", Json_decode.string, param);
                }), json),
          date: Json_decode.optional((function (param) {
                  return Json_decode.field("date", Json_decode.string, param);
                }), json),
          twitter: Json_decode.optional((function (param) {
                  return Json_decode.field("twitter", Json_decode.string, param);
                }), json),
          github: Json_decode.optional((function (param) {
                  return Json_decode.field("github", Json_decode.string, param);
                }), json)
        };
}

var decodeTalk = decode;

function talkJson(item) {
  return decode(JSON.parse(Belt_Option.getExn(JSON.stringify(item))));
}

export {
  decode ,
  decodeTalk ,
  talkJson ,
  
}
/* No side effect */
