'use strict';


/**
 * 登录
 * 用户登录.
 *
 * id String 登录ID号
 * pwd String 学生学号
 * returns ActionState
 **/
exports.landingPost = function(id,pwd) {
  return new Promise(function(resolve, reject) {
    var examples = {};
    examples['application/json'] = {
  "status" : 0,
  "info" : "发送操作请求成功"
};
    if (Object.keys(examples).length > 0) {
      resolve(examples[Object.keys(examples)[0]]);
    } else {
      resolve();
    }
  });
}


/**
 * 获取用户权限
 * 根据输入的用户名返回用户权限
 *
 * id String 用户id
 * returns inline_response_200
 **/
exports.userGet_powerGET = function(id) {
  return new Promise(function(resolve, reject) {
    var examples = {};
    examples['application/json'] = {
  "userType" : "userType",
  "status" : "status"
};
    if (Object.keys(examples).length > 0) {
      resolve(examples[Object.keys(examples)[0]]);
    } else {
      resolve();
    }
  });
}

