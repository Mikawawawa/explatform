'use strict';


/**
 * 根据教师号获取教师课表
 * 查看教师课表
 *
 * teacher_id String teacher
 * returns CourseInfo
 **/
exports.get_teacher_timetableById = function(teacher_id) {
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
 * 根据实验id获取所有学生的该实验信息
 *
 * class_id String 班级id
 * returns Expinfo_t
 **/
exports.teacherGet_expGET = function(class_id) {
  return new Promise(function(resolve, reject) {
    var examples = {};
    examples['application/json'] = {
  "status" : 0,
  "info" : [ {
    "student_id" : {
      "type" : "string",
      "description" : "学生id号"
    },
    "article" : {
      "type" : "string",
      "description" : "报告编号"
    },
    "grade" : {
      "type" : "object",
      "maxitem" : 3,
      "example" : [ {
        "preview" : 4
      }, {
        "action" : 5
      }, {
        "report" : 4
      } ]
    }
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
 * 获取实验报告
 * 根据报告id获取markdown报告的原始内容
 *
 * report_id String 报告编号
 * returns Reportinfo_t
 **/
exports.teacherGet_reportGET = function(report_id) {
  return new Promise(function(resolve, reject) {
    var examples = {};
    examples['application/json'] = {
  "status" : 0,
  "info" : "# hello world"
};
    if (Object.keys(examples).length > 0) {
      resolve(examples[Object.keys(examples)[0]]);
    } else {
      resolve();
    }
  });
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
exports.teacherSet_gradePOST = function(student_id,exp_id,preview,action,report) {
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
 * 开始实验
 * 教师开始实验
 *
 * classroom_id String  (optional)
 * class_id String  (optional)
 * process String  (optional)
 * returns ActionState
 **/
exports.teacherStart_expPOST = function(classroom_id,class_id,process) {
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

