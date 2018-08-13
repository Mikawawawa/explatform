const express = require('express');
const router = express.Router();
const models = require("../models/student")

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
*/
router.get('/create_student',function(req,res,next){
     models.create_student({}, (data) => {
         res.send({
             code: 0,
             info: "has not logined",
             data: JSON.stringify(data)
            });
    })
    next();
});
router.get('/create_teacher',function(req,res,next) {
        models.create_teacher({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    next();
});

router.get('/create_experiment',function(req,res,next) {
        models.create_experiment({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    next();
});

router.get('/create_class_user',function(req,res,next) {
        models.create_class_user({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    next();
});

router.get('/get_classromm_timetable',function(req,res,next) {
        models.get_classromm_timetable({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    next();
 });

 router.get('/get_class_timetable',function(req,res,next) {
    models.get_class_timetable({}, (data) => {
        res.send({
            code: 0,
            info: "has not logined",
            data: JSON.stringify(data)
        });
    })
    next();
});

router.get('/update_notice',function(req,res,next) {
    models.update_notice({}, (data) => {
        res.send({
            code: 0,
            info: "has not logined",
            data: JSON.stringify(data)
        });
    })
    next();
});

module.exports = router;