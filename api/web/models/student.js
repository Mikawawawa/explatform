/*
 * @Author: shengqiongyi
 * @Date: 2018-08-12 20:19:34 
 * @Last Modified by: Maktub
 * @Last Modified time: 2018-08-15 10:39:15
 */
const connection = require("./connect")
const config = require('../config.json')

// params是指route里文件调用这里的函数时，要传的参数，这个参数的来源在route
// 不要使用var作为变量定义时的修饰符，可能会出现意料之外的错误
// 对于引用的模块这类不变的对象，使用const
// 对于块级作用域内的变量，使用let
// let params = config.params;

// mysql里存储过程的调用方式
// call procedure(params...)
// https://www.cnblogs.com/geaozhang/p/6797357.html

// 为了后期维护（极有可能），函数命名一定要能够明白到底做了什么，
// 比如timetable，到底是get到这个表，还是delete还是什么，一定要写明白

// fileheader这个插件了解一下
// 在函数前面输入/**，然后按tab，写好注释，后面用的时候会方便很多，可以直接看到提示

/**
 * 查看自己的课表
 * @param {*} config 
 * @param function callback 
 */
function get_timetable(config, callback) {
    connection.query("CALL `get_student_timetable`("+config+")", (err, rows, fields) => {
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
function get_report(config, callback) {
    connection.query("CALL `get_student_recard`("+config+")", (err, rows, fields) => {
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
function update_exp(subject,grade,present,operation,section,choice,callback) {
    connection.query("CALL `update_experiment_recard`("+subject+","+grade+","+present+","+operation+","+section+","+choice+")", (err, rows, fields) => {
        if(err){
            console.log(err);
        }
    })
}

//查看自己的各门实验课的分数（含操作的小题分
function get_grade(config, callback) {
    connection.query("CALL `get_student_recard`("+config+")",(err, rows, fields) => {
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
    'get_timetable':get_timetable,
    'get_report':get_report,
    'get_grade':get_grade,
    'update_exp':update_exp,
}