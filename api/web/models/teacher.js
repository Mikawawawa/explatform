const connection = require("./connect")

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
function update_grade(student,experiment,config, callback) {
    connection.query("CALL `update_experiment_operation`("+student+","+experiment+","+config+")", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//老师开始上课后，对课程中的某个实验进行签到开始上电，实验完成后对实验各题结果进行递交；实验课结束后签离，切断电源
function start_exp(classroom_id,class_id,process, callback) {
    connection.query(`call update_classroom('${classroom_id}','${class_id}','${process}')`, (err, rows, fields) => {
        if(err){
            console.log(err);
        }else{
            callback(rows)
        }
    })
}

module.exports = {
    'update_recard':update_recard,
    'update_grade' :update_grade,
    'get_timetable':get_timetable,
    'update_application':update_application,
    'get_application':get_application,
    'start_exp':start_exp,
}