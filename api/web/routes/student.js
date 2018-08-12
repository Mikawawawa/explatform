const express = require('express');
const router = express.Router();
const models = require("../models/student")

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
    } else if(req.url=='a') {
        models.timetable({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    }else if(req.url=='b') {
        models.report({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    }else if(req.url=='c') {
        models.up_exp({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    }else if(req.url=='d') {
        models.create_exp({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    }else if(req.url=='e') {
        models.grade({}, (data) => {
            res.send({
                code: 0,
                info: "has not logined",
                data: JSON.stringify(data)
            });
        })
    }
});

module.exports = router;