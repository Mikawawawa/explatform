const app = require("express").Router()

const user=require("../service/TeacherService")
var bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({extended:true}));

app.get("/get_exp", async(req, res) => { 
    
    let params =await user.get_exp(req.query.class_id) 
    res.send(JSON.stringify({
        params
    }))
})
app.get("/set_grade", async(req, res) => {
    let params =await user.set_grade(req.query.student_id,req.query.exp_id,req.query.grade) 
    res.send(JSON.stringify({
        params
    }))
})
app.get("/get_report", async(req, res) => {
    let params=await teacher.teacherGet_reportGET(req.query.report_id)
    res.send(JSON.stringify({
        params
    }))
})
app.get("/get_course", async(req, res) => {
    let params=await teacher.get_teacher_timetableById(req.query.teacher_id)
    res.send(JSON.stringify({
        params
    }))
})
app.get("/start_exp", async(req, res) => {
    let params=await teacher.teacherStart_expPOST(req.query.class_id)
    res.send(JSON.stringify({
        params
    }))
})


module.exports = app