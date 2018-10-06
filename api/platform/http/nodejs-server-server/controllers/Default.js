'use strict';

var utils = require('../utils/writer.js');
var Default = require('../service/DefaultService');

module.exports.get_gradeStudentIDGET = function get_gradeStudentIDGET (req, res, next) {
  var studentID = req.swagger.params['studentID'].value;
  Default.get_gradeStudentIDGET(studentID)
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};

module.exports.get_reportGET = function get_reportGET (req, res, next) {
  Default.get_reportGET()
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};

module.exports.landingPOST = function landingPOST (req, res, next) {
  var tags = req.swagger.params['tags'].value;
  Default.landingPOST(tags)
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};
