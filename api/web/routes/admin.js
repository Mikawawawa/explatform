const express = require('express');
const router = express.Router();
const models = require("../models/admin")

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
     models.create_student((req.Url), (data) => {
         res.send({
             code: 0,
             info: "has not logined",
             data: JSON.stringify(data)
            });
    })
});
router.get('/create_teacher',function(req,res,next) {
        models.create_teacher((req.url), (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
});

router.get('/create_experiment',function(req,res,next) {
        models.create_experiment((req.url), (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
});

router.get('/create_class_user',function(req,res,next) {
        models.create_class_user((req.url), (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
});

router.get('/get_classromm_timetable',function(req,res,next) {
        models.get_classromm_timetable((req.url.substr(-8,8)), (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
 });

 router.get('/get_class_timetable',function(req,res,next) {
    models.get_class_timetable((req.url.substr(-8,8)), (data) => {
        res.send({
            code: 0,
            info: "has not logined",
            data: JSON.stringify(data)
        });
    })
});

router.get('/update_notice',function(req,res,next) {
    models.update_notice((req.url), (data) => {
        res.send({
            code: 0,
            info: "has not logined",
            data: JSON.stringify(data)
        });
    })
});

module.exports = router;