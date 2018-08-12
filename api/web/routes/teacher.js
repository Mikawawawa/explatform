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

router.get('/a',function(req,res,next){
     models.get_timetable({}, (data) => {
         res.send({
             code: 0,
             info: "has not logined",
             data: JSON.stringify(data)
            });
    })
    next();
});
router.get('/b',function(req,res,next) {
        models.get_application({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    next();
});

router.get('/c',function(req,res,next) {
        models.update_application({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    next();
});

router.get('/d',function(req,res,next) {
        models.update_grade({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    next();
});

router.get('/e',function(req,res,next) {
        models.update_recard({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    next();
 });

module.exports = router;