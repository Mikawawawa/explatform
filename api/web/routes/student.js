const express = require('express')
const router = express.Router()
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
*/
// 业务代码
//登录
router.post('/landing', function (req, res, next) {                             
    models.landing((req.body.id),(req.body.password),(data)=>{
        let abc = JSON.stringify(data);
        let bcd = JSON.parse(abc);
        let user_type = bcd[0].user_type;
        console.log(user_type);
        if(String(user_type)!=="student"){
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

//获取学生课表
 router.get('/get_timetable',function(req,res,next){
    models.get_timetable((req.url.substr(-8,8)), (data) =>{
         res.send({
             code: 0,
             data: JSON.stringify(data)
        })
    })
})

//获取实验报告
router.get('/get_report',function(req,res,next) {
    models.get_report((req.url.substr(-8.8)), (data) => {
        res.send({
            code: 0,
            data: JSON.stringify(data)
        })
    })
})

//上传实验数据
router.post('/update_exp',function(req,res,next) {
    models.update_exp((req.body.student,req.body.experiment,req.body.subject,req.body.grade,req.body.present,req.body.operation,req.body.section,req.body.choice), (data) => {
        res.send({
            code: 0,
            info:data
        })
    })
})

//查看学生实验成绩
router.get('/get_grade',function(req,res,next) {
    models.get_grade((req.url.substr(-8,8)), (data) => {
        res.send({
            code: 0,
            data: JSON.stringify(data)
        })
    })
 })

module.exports = router