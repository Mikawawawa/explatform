const app = require("express").Router()

const teacher=require("../service/TeacherService")


app.get("/get_exp", async(req, res) => { 
    
    let params =await teacher.get_exp(req.query.class_id) 
    res.send(JSON.stringify({
        params
    }))
})
app.get("/set_grade", async(req, res) => {
    let params =await teacher.set_grade(req.query.student_id,req.query.exp_id,req.query.grade) 
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
    let params=await teacher.teacherStart_expPOST(req.query.classroom_id,req.query.class_id,req.query.process)
    res.send(JSON.stringify({
        params
    }))
})


module.exports = app