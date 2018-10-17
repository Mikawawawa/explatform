'use strict';

const Teacher=require("../models/teacher")
const Mqtt=require("../models/mqtt")

/**
 * 根据教师号获取教师课表
 * 查看教师课表
 *
 * teacher_id String teacher
 * returns CourseInfo
 **/
exports.get_teacher_timetableById = async function(teacher_id) {
  return await Teacher.getCourse(teacher_id)
}


/**
 * 获取实验详情
 * 根据实验id获取所有学生的该实验信息
 *
 * class_id String 班级id
 * returns Expinfo_t
 **/
exports.get_exp = async function(class_id) {
  return await Teacher.get_exp(class_id)
}


/**
 * 获取实验报告
 * 根据报告id获取markdown报告的原始内容
 *
 * report_id String 报告编号
 * returns Reportinfo_t
 **/
exports.teacherGet_reportGET = async function(report_id) {
  return await Teacher.getReport(report_id)
}


/**
 * 设置某个学生某个实验的成绩
 * 传入学生id、实验id和完整的成绩，设置学生信息
 *
 * student_id String 学生学号
 * exp_id String 实验编号
 * preview Integer 预习分 (optional)
 * action Integer 操作分 (optional)
 * report Integer 报告分 (optional)
 * returns ActionState
 **/
exports.set_grade = async function(student_id,exp_id,grade,preview,action,report) {
  return await Teacher.set_grade(student_id,exp_id,grade)
}


/**
 * 开始实验
 * 教师开始实验
 *
 * classroom_id String  (optional)
 * class_id String  (optional)
 * process String  (optional)
 * returns ActionState
 **/
exports.teacherStart_expPOST = async function(classroom_id,class_id,process) {
  console.log(process)
  Mqtt.beginExperiment("000", process)
  // await Mqtt.noticePower(class_id, process)
  return await Teacher.startExp(classroom_id,class_id,process)
}
