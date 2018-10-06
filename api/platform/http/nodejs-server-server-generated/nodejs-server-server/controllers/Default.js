'use strict';

var utils = require('../utils/writer.js');
var Default = require('../service/DefaultService');

module.exports.get_gradeGET = function get_gradeGET (req, res, next) {
  Default.get_gradeGET()
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
  var student = req.swagger.params['student'].value;
  Default.landingPOST(student)
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};
