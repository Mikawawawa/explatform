'use strict';


/**
 * 学生获取课程
 * 根据学生的账号返回学生课表
 *
 * student_id String The studentID
 * returns CourseInfo
 **/
exports.studentGet_courseGET = function(student_id) {
  return await test.getCourse(student_id)
}


/**
 * 获取实验详情
 * 根据课程号获取实验的详情
 *
 * student_id String 学号
 * course_id String 课程编号
 * returns Expinfo_s
 **/
exports.studentGet_expGET = function(student_id,course_id) {
  return await test.getExp(student_id,course_id)
}


/**
 * 提交报告
 * 提交报告
 *
 * student_id String 学生的ID
 * exp_id String 实验的ID
 * article String 实验报告的数据
 * returns ActionState
 **/
exports.studentSet_reportPOST = function(student_id,exp_id,article) {
  return await test.setReport(student_id,exp_id,article)

}


