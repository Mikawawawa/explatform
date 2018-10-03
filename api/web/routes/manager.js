const express = require('express');
const router = express.Router();
const models = require("../models/manager");
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
        if(String(user_type)!=="manager"){
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

//对该课程下的班级群体发送公告
router.post('/update_notice',function(req,res,next){
     models.update_notice(req.body.notice_id,req.body.user_id,req.body.content,req.body.time,req.body.class_id, (data) => {
         res.send({
             code: 0,            
             data: JSON.stringify(data)
            });
    })
});

//查看所负责的课程的排课情况
router.get('/get_teacher_timetable',function(req,res,next) {
        models.get_teacher_timetable((req.url.substr(-8,8)), (data) => {
            res.send({
                code: 0,               
                data: JSON.stringify(data)
            });
        })
});

//发布老师的带课申请
router.post('/update_class_application',function(req,res,next) {
        models.update_class_application(req.body.class_id,req.body.teacher, (data) => {
            res.send({
                code: 0,               
                info:data
            });
        })
});

//查看老师的带课申请
router.get('/get_teacher_application',function(req,res,next) {
        models.get_teacher_application((req.url.substr(-8,8)), (data) => {
            res.send({
                code: 0,               
                data: JSON.stringify(data)
            });
        })
});

//审核老师的带课申请
router.post('/check_application',function(req,res,next) {
        models.check_application(req.body.class_id,req.body.teacher,req.body.status, (data) => {
            res.send({
                code: 0,                
                data: JSON.stringify(data)
            });
        })
 });

 //发布报告模板（编辑报告内容包括：文字、表格（按图片方式存在）、图像文件、视频文件等）
 router.post('/update_template',function(req,res,next) {
    models.update_template((req.body.subject_id,req.body.template_id), (data) => {
        res.send({
            code: 0,           
            data: JSON.stringify(data)
        });
    })
});

//查看各班级的学生的签到信息
router.get('/get_student_recard',function(req,res,next) {
    models.get_student_recard((req.url.substr(-8,8)),(data) => {
        res.send({
            code: 0,           
            data: JSON.stringify(data)
        });
    })
});

module.exports = router;