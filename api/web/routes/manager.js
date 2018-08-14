const express = require('express');
const router = express.Router();
const models = require("../models/manager")

//验证身份
/*router.use((req, res, next) => {
    if (!req.session.key || req.session.type !== "student") {
        res.send({
            code: 0,
            info: "身份错误"
        })
    } else {
        next()
    }
});
*/
// 业务代码
/*
router.get('/', function (req, res, next) {
    if (req.session.key) {
        res.send({
            code: 1,
            info: req.session.key
        });
        next();
    }
 });
 */
qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq
router.post('/create_student',function(req,res,next){
    models.create_student(req.body.config,req.body.id, (data) => {
        res.send({
            code: 0,
            info: "has not logined",
            data: JSON.stringify(data)
           });
   })
});


router.post('/update_notice',function(req,res,next){
     models.update_notice(req.body.notice_id,req.body.user_id,req.body.content,req.body.time,req.body.class_id, (data) => {
         res.send({
             code: 0,
             info: "has not logined",
             data: JSON.stringify(data)
            });
    })
});
router.get('/get_teacher_timetable',function(req,res,next) {
        models.get_teacher_timetable((req.url.substr(-8,8)), (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
});

router.post('/update_class_application',function(req,res,next) {
        models.update_class_application(req.body.class_id,req.body.teacher,req.body.status, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
});

router.get('/get_teacher_application',function(req,res,next) {
        models.get_teacher_application((req.url.substr(-8,8)), (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
});

router.post('/check_application',function(req,res,next) {
        models.check_application(req.body.class_id,req.body.teacher,req.body.status, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
 });

 router.post('/update_template',function(req,res,next) {
    models.update_template((req.body.subject_id,req.body.template_id), (data) => {
        res.send({
            code: 0,
            info: "has not logined",
            data: JSON.stringify(data)
        });
    })
});

router.get('/get_student_recard',function(req,res,next) {
    models.get_student_recard((req.url.substr(-8,8)), (data) => {
        res.send({
            code: 0,
            info: "has not logined",
            data: JSON.stringify(data)
        });
    })
});

module.exports = router;