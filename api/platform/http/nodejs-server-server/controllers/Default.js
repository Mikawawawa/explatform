'use strict';

var utils = require('../utils/writer.js');
var Default = require('../service/DefaultService');

module.exports.exprimentsGET = function exprimentsGET (req, res, next) {
  Default.exprimentsGET()
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};

module.exports.exprimentsPOST = function exprimentsPOST (req, res, next) {
  var report = req.swagger.params['report'].value;
  Default.exprimentsPOST(report)
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};

module.exports.usersPOST = function usersPOST (req, res, next) {
  var user = req.swagger.params['user'].value;
  Default.usersPOST(user)
    .then(function (response) {
      utils.writeJson(res, response);
    })
    .catch(function (response) {
      utils.writeJson(res, response);
    });
};
