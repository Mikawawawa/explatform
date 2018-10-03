const express = require('express');
const router = express.Router();
const models = require("../models/teacher");
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
        if(String(user_type)!=="teacher"){
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

//查看教师的课表
router.get('/get_timetable',function(req,res,next){
     models.get_timetable((req.url.substr(-8,8)), (data) => {
         res.send({
             code: 0,             
             data: JSON.stringify(data)
            });
    })
});

//查看已发布的需要招募老师的课程
router.get('/get_application',function(req,res,next) {
        models.get_application((req.url.substr(-8,8)), (data) => {
            res.send({
                code: 0,               
                data: JSON.stringify(data)
            });
        })
});

//递交申请
router.post('/update_application',function(req,res,next) {
        models.update_application((req.body.classid,req.body.teacher), (data) => {
            res.send({
                code: 0,               
                data: JSON.stringify(data)
            });
        })
});

//对操作各题成绩进行现场扫描学生二维码打分或补登成绩
router.post('/update_grade',function(req,res,next) {
        models.update_grade((req.body.student),(req.body.experiment),(req.body.operation), (data) => {
            res.send({
                code: 0,              
                data: JSON.stringify(data)
            });
        })
});

//查看并批阅报告；对学生的预习、报告、大作业、考试等进行打分 查看自己带课教学班级学生实验的分数 查看代课班级学生的签到信息
router.post('/update_recard',function(req,res,next) {
        models.update_recard((req.body.subject,req.body.grade,req.body.present,req.body.operation,req.body.section,req.body.choice), (data) => {
            res.send({
                code: 0,               
                data: JSON.stringify(data)
            });
        })
 });

 //老师开始上课后，对课程中的某个实验进行签到开始上电，实验完成后对实验各题结果进行递交；实验课结束后签离，切断电源
 router.post("start_exp",function(req,res){
    models.start_exp(req.body.classroom_id,req.body.class_id,process,(data)=>{
        data=data[0]
        res.send({
            code:0,
            data:JSON.stringify(data)
        })
    })
 })

module.exports = router;