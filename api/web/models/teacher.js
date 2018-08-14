const connection = require("./connect")
const config = require('../config.json')

//查看已发布的需要招募老师的课程
function get_application(config, callback) {
    connection.query("CALL `get_class_application`("+config+")", (err, rows, fields) => {
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
function update_application(classid,teacher, callback) {
    connection.query("CALL `class_application`("+classid+","+teacher+")",(err, rows, fields) => {
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
function get_timetable(config, callback) {
    connection.query("CALL `get_teacher_timetable`("+config+")", (err, rows, fields) => {
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
function update_recard(subject,grade,present,operation,section,choice,callback) {
    connection.query("CALL `update_experiment_recard`("+subject+","+grade+","+present+","+operation+","+section+","+choice+")",(err, rows, fields) => {
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
function update_grade(config, callback) {
    connection.query("CALL `update_experiment_operation`("+config+")", (err, rows, fields) => {
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
    'update_recard':update_recard,
    'update_grade' :update_grade,
    'get_timetable':get_timetable,
    'update_application':update_application,
    'get_application':get_application
}