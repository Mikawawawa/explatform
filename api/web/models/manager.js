const connection = require("./connect")
const config = require("./config.json")

var params = config.params;

//对该课程下的班级群体发送公告
function application(config, callback) {
    connection.query("CALL `create_notice`", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//查看所负责的课程的排课情况
function get_application(config, callback) {
    connection.query("CALL `get_teacher_timetable`", params,(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//发布老师的带课申请
function ttimetable(config, callback) {
    connection.query("CALL `class_application`", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//查看老师的带课申请
function ttimetable(config, callback) {
    connection.query("CALL `get_teacher_application`", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//审核老师的带课申请
function ttimetable(config, callback) {
    connection.query("CALL `update_class_application`", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//发布报告模板（编辑报告内容包括：文字、表格（按图片方式存在）、图像文件、视频文件等）
function ttimetable(config, callback) {
    connection.query("CALL `create_template`", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//查看各班级的学生的签到信息
function ttimetable(config, callback) {
    connection.query("CALL `get_student_recard`", (err, rows, fields) => {
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