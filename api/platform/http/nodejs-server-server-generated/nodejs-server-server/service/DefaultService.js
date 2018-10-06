'use strict';


/**
 * Gets experiment grade
 * Returns grade
 *
 * returns List
 **/
exports.get_gradeGET = function() {
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
 * student Student The student to create. (optional)
 * no response value expected for this operation
 **/
exports.landingPOST = function(student) {
  return new Promise(function(resolve, reject) {
    resolve();
  });
}

