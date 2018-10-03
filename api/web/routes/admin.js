const express = require('express');
const router = express.Router();
const models = require("../models/admin");
const land = require("../models/student");

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
//登录
router.post('/landing', function (req, res, next) {
    land.landing((req.body.id),(req.body.password),(data)=>{
        let abc = JSON.stringify(data);
        let bcd = JSON.parse(abc);
        let user_type = bcd[0].user_type;
        console.log(user_type);
        if(String(user_type)!=="admin"){
            res.send({
                code :0,
                info:"身份错误"
            })
        }
        else{
            res.send({
                code :0,
                info:"登录成功"
            })
        }
     })
})

//手动增加学生
router.post('/create_student',function(req,res,next){
     models.create_student(req.body.id,req.body.name,(data) => {
         res.send({
             code: 0,
             data: JSON.stringify(data)
            });
    })
});

//手动增加教师
router.post('/create_teacher',function(req,res,next) {
        models.create_teacher((req.body.id,req.body.name), (data) => {
            res.send({
                code: 0,
                data: JSON.stringify(data)
            });
        })
});

//手动增加实验课程
router.post('/create_experiment',function(req,res,next) {
        models.create_experiment((req.body), (data) => {
            res.send({
                code: 0,
                data: JSON.stringify(data)
            });
        })
});

//手动增加课程负责人
router.post('/create_class_user',function(req,res,next) {
        models.create_class_user((req.body.id,req.body.password,req.body.name,req.body.type), (data) => {
            res.send({
                code: 0,
                data: JSON.stringify(data)
            });
        })
});

//教室的使用情况
router.get('/get_classromm_timetable',function(req,res,next) {
        models.get_classromm_timetable((req.url.substr(-8,8)), (data) => {
            res.send({
                code: 0,
                data: JSON.stringify(data)
            });
        })
 });

 //查看课程的排课情况
 router.get('/get_class_timetable',function(req,res,next) {
    models.get_class_timetable((req.url.substr(-8,8)), (data) => {
        res.send({
            code: 0,
            data: JSON.stringify(data)
        });
    })
});

//对群体发送公告，通知定位到具体班级上
router.post('/update_notice',function(req,res,next) {
    models.update_notice((req.body.id,req.body.notice), (data) => {
        res.send({
            code: 0,
            data: JSON.stringify(data)
        });
    })
});

module.exports = router;