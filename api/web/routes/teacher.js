const express = require('express');
const router = express.Router();
const models = require("../models/teacher")

//验证身份
router.use((req, res, next) => {
    if (!req.session.key || req.session.type !== "student") {
        res.send({
            code: 0,
            info: "身份错误"
        })
    } else {
        next()
    }
});

// 业务代码
router.get('/', function (req, res, next) {
    if (req.session.key) {
        res.send({
            code: 1,
            info: req.session.key
        });
        next();
    }
 });

router.get('/get_timetable',function(req,res,next){
     models.get_timetable((req.url.substr(-8,8)), (data) => {
         res.send({
             code: 0,
             info: "has not logined",
             data: JSON.stringify(data)
            });
    })
});

router.get('/get_application',function(req,res,next) {
        models.get_application((req.url.substr(-8,8)), (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
});

router.post('/update_application',function(req,res,next) {
        models.update_application((req.body.classid,req.body.teacher), (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
});

router.post('/update_grade',function(req,res,next) {
        models.update_grade((req.body.operation), (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
});

router.post('/update_recard',function(req,res,next) {
        models.update_recard((req.body.subject,req.body.grade,req.body.present,req.body.operation,req.body.section,req.body.choice), (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
 });

module.exports = router;