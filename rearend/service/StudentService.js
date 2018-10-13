'use strict';


/**
 * 学生获取课程
 * 根据学生的账号返回学生课表
 *
 * student_id String The studentID
 * returns CourseInfo
 **/
exports.studentGet_courseGET = function(student_id) {
  return new Promise(function(resolve, reject) {
    var examples = {};
    examples['application/json'] = {
  "status" : 0,
  "info" : [ {
    "course_id" : null,
    "type" : "string",
    "description" : "课程id号"
  }, {
    "course_name" : null,
    "type" : "string",
    "desciption" : "课程名"
  } ]
};
    if (Object.keys(examples).length > 0) {
      resolve(examples[Object.keys(examples)[0]]);
    } else {
      resolve();
    }
  });
}


/**
 * 获取实验详情
 * 根据课程号获取实验的详情
 *
 * course_id String 课程编号
 * returns Expinfo_s
 **/
exports.studentGet_expGET = function(course_id) {
  return new Promise(function(resolve, reject) {
    var examples = {};
    examples['application/json'] = {
  "score" : 0,
  "name" : "name",
  "student_id" : "student_id",
  "id" : "id"
};
    if (Object.keys(examples).length > 0) {
      resolve(examples[Object.keys(examples)[0]]);
    } else {
      resolve();
    }
  });
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

