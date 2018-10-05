'use strict';


/**
 * Gets some experiments information
 * Returns a list containing all expriments.
 *
 * returns List
 **/
exports.exprimentsGET = function() {
  return new Promise(function(resolve, reject) {
    var examples = {};
    examples['application/json'] = [ {
  "experimentReport" : "experimentReport",
  "experimentScore" : "experimentScore",
  "experimentID" : "experimentID",
  "experimentName" : "experimentName"
}, {
  "experimentReport" : "experimentReport",
  "experimentScore" : "experimentScore",
  "experimentID" : "experimentID",
  "experimentName" : "experimentName"
} ];
    if (Object.keys(examples).length > 0) {
      resolve(examples[Object.keys(examples)[0]]);
    } else {
      resolve();
    }
  });
}


/**
 * Add some experiment reports
 * Adds a new report to the report list.
 *
 * report Report The report to create. (optional)
 * no response value expected for this operation
 **/
exports.exprimentsPOST = function(report) {
  return new Promise(function(resolve, reject) {
    resolve();
  });
}


/**
 * Add some users
 * Adds a new user to the users list.
 *
 * user User The user to create. (optional)
 * no response value expected for this operation
 **/
exports.usersPOST = function(user) {
  return new Promise(function(resolve, reject) {
    resolve();
  });
}

