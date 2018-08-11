const express = require('express');
const router = express.Router();
var mysql = require('mysql');
var connection = mysql.createConnection(JSON.parse(require('./config.json')));

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

connection.connect();

//查看自己的课表
connection.query('CALL get_student_timetable(1,@student)', function(err, rows, fields) {
    if (err) {
        throw err;
    }

});

//查看报告；实验课前对预习作业进行递交 
//课后能对实验报告进行编辑填写（允许对虚拟测量软件的测量结果截图粘贴、填写表格、粘贴图像文件、粘贴视频文件等操作）、递交
connection.query('CALL update_experiment_recard(1,@student)', function(err, rows, fields) {
    if (err) {
        throw err;
    }

});

//老师开始上课后，对课程中的某个实验进行签到开始上电，实验完成后对实验各题结果进行递交；实验课结束后签离，切断电源
connection.query('CALL create_experiment_recard(1,@student，@present)', function(err, rows, fields) {
    if (err) {
        throw err;
    }

});

//查看自己的各门实验课的分数（含操作的小题分
connection.query('CALL get_student_recard(1,@student)', function(err, rows, fields) {
    if (err) {
        throw err;
    }

});

module.exports = router;
