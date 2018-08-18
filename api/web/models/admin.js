const connection = require("./connect")

//对群体发送公告，通知定位到具体班级上
function update_notice(id,notice, callback) {
    connection.query("CALL `class_notice`("+id+",'"+notice+"')",(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//查看课程的排课情况
function get_class_timetable(config, callback) {
    connection.query("CALL `get_experiment_recard`("+config+")", params,(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//教室的使用情况
function get_classromm_timetable(config, callback) {
    connection.query("CALL `get_classroom_timetable`("+config+")", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//手动增加课程负责人
function create_class_user(id,password,name,type, callback) {
    connection.query("CALL `create_user`("+id+",'"+password+"','"+name+"','"+type+"')",(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//手动增加实验课程
function create_experiment(subject, callback) {
    connection.query("CALL `create_experiment`('"+subject+"')",(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//手动增加教师
function create_teacher(id,name, callback) {
    connection.query("CALL `create_teacher`("+id+",'"+name+"')",(err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows[0])
        }
    })
}

//手动增加学生
function create_student(id,name,callback) {
    connection.query("CALL `create_student`('"+id+"','"+name+"')",(err, rows, fields) => {
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
    'create_student':create_student,
    'create_teacher' :create_teacher,
    'create_experiment':create_experiment,
    'create_class_user':create_class_user,
    'get_classromm_timetable':get_classromm_timetable,
    'get_class_timetable':get_class_timetable,
    'update_notice':update_notice
}