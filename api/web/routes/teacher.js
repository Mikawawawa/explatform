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

// //查看已发布的需要招募老师的课程，并递交申请
// connection.query('CALL get_class_application(1,@class)', function (err, rows, fields) {
//     if (err) {
//         throw err;
//     }

// });
// connection.query('CALL class_application(1,@class,@teacher)', function (err, rows, fields) {
//     if (err) {
//         throw err;
//     }

// });

// //查看自己的课表
// connection.query('CALL get_teacher_grant(1,@teacher)', function (err, rows, fields) {
//     if (err) {
//         throw err;
//     }

// });

// //查看并批阅报告；对学生的预习、报告、大作业、考试等进行打分 查看自己带课教学班级学生实验的分数 查看代课班级学生的签到信息
// connection.query('update_experiment_recard(1,@student，@grade，@present)', function (err, rows, fields) {
//     if (err) {
//         throw err;
//     }

// });

// //对操作各题成绩进行现场扫描学生二维码打分或补登成绩
// connection.query('CALL create_experiment_recard(1,@student，@grade)', function (err, rows, fields) {
//     if (err) {
//         throw err;
//     }

// });

module.exports = router;