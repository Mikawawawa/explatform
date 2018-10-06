'use strict';


/**
 * Gets experiment grade
 * Returns grade
 *
 * studentID String ID of pet to return
 * returns List
 **/
exports.get_gradeStudentIDGET = function(studentID) {
  return new Promise(function(resolve, reject) {
    var examples = {};
    examples['application/json'] = [ {
  "experimentScore" : "experimentScore"
}, {
  "experimentScore" : "experimentScore"
} ];
    if (Object.keys(examples).length > 0) {
      resolve(examples[Object.keys(examples)[0]]);
    } else {
      resolve();
    }
  });
}


/**
 * Gets experiment report
 * Returns report
 *
 * no response value expected for this operation
 **/
exports.get_reportGET = function() {
  return new Promise(function(resolve, reject) {
    resolve();
  });
}


/**
 * login
 * 学生登录.
 *
 * tags Tags The student to create. (optional)
 * no response value expected for this operation
 **/
exports.landingPOST = function(tags) {
  return new Promise(function(resolve, reject) {
    resolve();
  });
}

