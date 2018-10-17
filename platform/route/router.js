const express = require('express');
const router = express.Router();
const modle = require("../service/DefaultService");


/*
 *  验证管理员身份
 *  check_admin 
 */
router.get('/check_admin',async function(req,res,next) {
    //console.log(req.query.id)
    let data = await modle.check_adminPOST(req.query.password,req.query.id)
    console.log(data)
    res.send(
        JSON.stringify(data)
    );
});

/*
 *  老师验证
 *  check_teacher
 */
router.get('/check_teacher',async function(req,res,next) {
    let data = await modle.check_teacherPOST(req.query.password,req.query.id)
    res.send(
        JSON.stringify(data)
    );
});


/*
 *  获取实验进度：发MAC地址
 *  get_progress
 */
router.get('/get_progress',async function(req,res,next) {
    let data = await modle.get_progressPOST(req.query.id)
    console.log(data)
    res.send(
        JSON.stringify(data)
    );
});


/*
 *  上传成绩
 *  put_grade
 */
router.get('/put_grade',async function(req,res,next) {
    let data = await modle.put_gradePOST(req.query.mark,req.query.id,req.query.experiment_id)
    res.send(
        JSON.stringify(data)
    );
});


/*
 *  上传日志信息
 *  put_log
 */
router.get('/put_log',async function(req,res,next) {
    let data = await modle.put_logPOST(req.query.id,req.query.log)
    res.send(
        JSON.stringify(data)
    );
});


/*
 *  读取日志信息
 *  read_log
 */
router.get('/read_log',async function(req,res,next) {
    let data = await modle.read_logPOST(req.query.id)
    res.send(
        JSON.stringify(data)
    );
});


/*
 *  时间
 *  read_time
 */
router.get('/read_time',async function(req,res,next) {
    let data = await modle.read_timePOST(req.query.id)
    res.send(
        JSON.stringify(data)
    );
});



/*
 *  学生签到
 *  student_signin
 */
router.get('/student_signin',async function(req,res,next) {
    let data = await modle.student_signinPOST(req.query.id,req.query.mac_id,req.query.exp_id)
    res.send(
        JSON.stringify(data)
    );
});


module.exports = router;