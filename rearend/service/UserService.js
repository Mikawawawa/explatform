'use strict';
const User=require("../models/user")

/**
 * 登录
 * 用户登录.
 *
 * id String 登录ID号
 * pwd String 学生学号
 * returns ActionState
 **/
exports.landingPost = function(id,password) {
  return await User.login(id,password)
}
    


/**
 * 获取用户权限
 * 根据输入的用户名返回用户权限
 *
 * id String 用户id
 * returns inline_response_200
 **/
exports.userGet_powerGET = function(id) {
  return await User.getPower(id)
}

