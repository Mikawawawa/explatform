const connection = require("./connect")
const config = require("../config.json")

var params = config.params;

//查看已发布的需要招募老师的课程
function application(config, callback) {
    connection.query("CALL `get_class_application`", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//递交申请
function get_application(config, callback) {
    connection.query("CALL `class_application`", params,(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//查看自己的课表
function ttimetable(config, callback) {
    connection.query("CALL `get_teacher_timetable`", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//查看并批阅报告；对学生的预习、报告、大作业、考试等进行打分 查看自己带课教学班级学生实验的分数 查看代课班级学生的签到信息
function recard(config, callback) {
    connection.query("CALL `update_experiment_recard`", params,(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//对操作各题成绩进行现场扫描学生二维码打分或补登成绩
function grade(config, callback) {
    connection.query("CALL `update_experiment_operation`",params, (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

module.exports = {
    'recard':recard,
    'grade' :grade,
    'ttimetable':ttimetable,
    'application':application,
    'get_application':get_application
}