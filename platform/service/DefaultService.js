'use strict';

const modules = require("../models/modules")
const mqtt=require("../models/mqtt")

/**
 * 获取实验进度：发MAC地址
 *
 * data Classes 实验信息
 * returns Emessage
 **/
exports.get_progressPOST = async function(id) {
  return await modules.get_progress(id)
}

/**
 * 验证管理员身份
 *
 * data Admin 验证管理员身份
 * returns init
 **/
exports.check_adminPOST = async function(password,id) {
  return await modules.check_admin(password,id)
}

/**
 * 老师验证
 *
 * data Teacher 老师验证
 * returns Result
 **/
exports.check_teacherPOST = async function(password,id) {
  return await modules.check_teacher(password,id)
}

/**
 * 上传成绩
 *
 * data Student 上传成绩
 * returns grade
 **/
exports.put_gradePOST = async function(mark,id,experiment_id) {
  return await modules.put_grade(mark,id,experiment_id)
}


/**
 * 上传日志信息
 *
 * data Log 上传日志信息
 * returns info
 **/
exports.put_logPOST = async function(id,log) {
  return await modules.put_log(id,log)
}


/**
 * 读取日志信息
 *
 * data Info 读取日志信息
 * returns log
 **/
exports.read_logPOST = async function(id) {
  return await modules.read_log(id)
}


/**
 * 时间
 *
 * data Emessage 时间
 * returns info
 **/
exports.read_timePOST = async function(data) {
  return await modules.read_time(data)
}


/**
 * 学生签到
 *
 * data Student 学生签到
 * returns info
 **/
exports.student_signinPOST = async function(id,mac,exp) {
  mqtt.noticePower('000',1)
  return await modules.student_signin(id,mac,exp)
}

