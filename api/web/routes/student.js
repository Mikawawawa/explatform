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
router.post('/landing', function (req, res, next) {
    models.landing((req.body.id),(req.body.password),(data)=>{
        if(data!=="admin"){
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
    models.get_timetable((req.url.substr(-8,8)), (data) =>{
         res.send({
             code: 0,
             data: JSON.stringify(data)
        })
    })
})

router.get('/get_report',function(req,res,next) {
    console.log(req.baseUrl);
    console.log(req.originalUrl);
    models.get_report((req.url.substr(-8.8)), (data) => {
        res.send({
            code: 0,
            data: JSON.stringify(data)
        })
    })
})

router.post('/update_exp',function(req,res,next) {
    models.update_exp((req.body.subject,req.body.grade,req.body.present,req.body.operation,req.body.section,req.body.choice), (data) => {
        res.send({
            code: 0,
            data: JSON.stringify(data)
        })
    })
})

router.get('/get_grade',function(req,res,next) {
    models.get_grade((req.url.substr(-8,8)), (data) => {
        res.send({
            code: 0,
            data: JSON.stringify(data)
        })
    })
 })

module.exports = router