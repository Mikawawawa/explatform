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

router.get('/get_timetable',function(req,res,next){
     models.get_timetable((req.url.substr(-8,8)), (data) => {
         res.send({
             code: 0,             
             data: JSON.stringify(data)
            });
    })
});

router.get('/get_application',function(req,res,next) {
        models.get_application((req.url.substr(-8,8)), (data) => {
            res.send({
                code: 0,               
                data: JSON.stringify(data)
            });
        })
});

router.post('/update_application',function(req,res,next) {
        models.update_application((req.body.classid,req.body.teacher), (data) => {
            res.send({
                code: 0,               
                data: JSON.stringify(data)
            });
        })
});

router.post('/update_grade',function(req,res,next) {
        models.update_grade((req.body.student),(req.body.experiment),(req.body.operation), (data) => {
            res.send({
                code: 0,              
                data: JSON.stringify(data)
            });
        })
});

router.post('/update_recard',function(req,res,next) {
        models.update_recard((req.body.subject,req.body.grade,req.body.present,req.body.operation,req.body.section,req.body.choice), (data) => {
            res.send({
                code: 0,               
                data: JSON.stringify(data)
            });
        })
 });

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