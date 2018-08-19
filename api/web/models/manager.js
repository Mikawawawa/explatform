const connection = require("./connect")
const config = require('../config.json')

var params = config.params;

//对该课程下的班级群体发送公告
function update_notice(notice_id,user_id,content,time,class_id, callback) {
    connection.query("CALL `create_notice`("+notice_id+","+user_id+","+content+","+time+","+class_id+")", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//查看所负责的课程的排课情况
function get_teacher_timetable(teacher_id, callback) {
    connection.query("CALL `get_teacher_timetable`("+teacher_id+")",(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//发布老师的带课申请
function update_class_application(class_id,teacher, callback) {
    connection.query("CALL `class_application`("+class_id+","+teacher+")",(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            callback("ok")
        }
    })
}

//查看老师的带课申请
function get_teacher_application(teacher, callback) {
    connection.query("CALL `get_teacher_application`("+teacher+")",(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//审核老师的带课申请
function check_application(class_id,teacher,status, callback) {
    connection.query("CALL `update_class_application`("+class_id+","+teacher+","+status+")",(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//发布报告模板（编辑报告内容包括：文字、表格（按图片方式存在）、图像文件、视频文件等）
function update_template(subject_id,template_id, callback) {
    connection.query("CALL `create_template`("+subject_id+","+template_id+")" ,(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//查看各班级的学生的签到信息
function get_student_recard(student, callback) {
    connection.query("CALL `get_student_recard`("+student+")" ,(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

module.exports = {
    'get_student_recard':get_student_recard,
    'update_template' :update_template,
    'check_application':check_application,
    'get_teacher_application':get_teacher_application,
    'update_class_application':update_class_application,
    'get_teacher_timetable':get_teacher_timetable,
    'update_notice':update_notice
}