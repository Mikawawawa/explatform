const connection = require("./connect")

//查看自己的课表
function timetable(config, callback) {
    console.log(callback)
    connection.query("select * FROM `get_student_timetable`", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows)
            callback(rows)
        }
    })
}

//查看报告；
function report(config, callback) {
    console.log(callback)
    connection.query("select * FROM `get_student_recard`", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
        else {
            console.log(rows);
            callback(rows);
        }
    })
}
//实验课前对预习作业进行递交 
//课后能对实验报告进行编辑填写（允许对虚拟测量软件的测量结果截图粘贴、填写表格、粘贴图像文件、粘贴视频文件等操作）、递交
function up_exp(config, callback) {
    console.log(callback)
    connection.query("INSERT INTO `update_experiment_recard` where `student_id` = $student and `experiment_id` = $experiment",params, (err, rows, fields) => {
        if(err){
            console.log(err);
        }
    })
}

//老师开始上课后，对课程中的某个实验进行签到开始上电，实验完成后对实验各题结果进行递交；实验课结束后签离，切断电源
function create_exp(config, callback) {
    console.log(callback)
    connection.query("INSERT INTO  `create_experiment_recard`where `student_id` = $student_id and `experiment_id` = $experiment_id",params, (err, rows, fields) => {
        if(err){
            console.log(err);
        }
    })
}

////查看自己的各门实验课的分数（含操作的小题分
function grade(config, callback) {
    console.log(callback)
    connection.query("select * FROM `get_student_recard`", (err, rows, fields) => {
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
    'timetable':timetable,
    'report':report,
    'up_exp':up_exp,
    'create_exp':create_exp,
    'grade':grade
}