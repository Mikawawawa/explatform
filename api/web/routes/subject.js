const express = require('express');
const router = express.Router();
const mysql = require('mysql');
const config = require('../config.json');
// 这里已经是object了
// var connection = mysql.createConnection(JSON.parse(require('./config.json')));
const connection = mysql.createConnection(config.mysql);
// 这个语句提前比较好
connection.connect();

/* GET users listing. */
router.get('/', function (req, res, next) {
    if (req.session.key) {
        res.send({
            code: 1,
            info: req.session.key
        });
        next();
    } else {
        res.send({
            code: 0,
            info: "has not logined"
        });
    }
});

module.exports = router;