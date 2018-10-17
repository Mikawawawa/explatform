const app = require("express").Router()

const teacher=require("../service/TeacherService")


app.get("/get_exp", async(req, res) => { 
    
    let params =await teacher.get_exp(req.query.class_id) 
    if(params.status != 1 ){
        res.send(JSON.stringify({
            status: 0,
            info: "Action error:" + params.info
        }))
    }
    else{
        res.send(JSON.stringify({
            status: 1,
            info: params.info
        }))
    }
    
})
app.get("/set_grade", async(req, res) => {
    let params =await teacher.set_grade(req.query.student_id,req.query.exp_id,req.query.grade) 
    if(params.status != 1 ){
        res.send(JSON.stringify({
            status: 0,
            info: "Action error:" + params.info
        }))
    }
    else{
        res.send(JSON.stringify({
            status: 1,
            info: params.info
        }))
    }
    
})
app.get("/get_report", async(req, res) => {
    let params=await teacher.teacherGet_reportGET(req.query.report_id)
    if(params.status != 1 ){
        res.send(JSON.stringify({
            status: 0,
            info: "Action error:" + params.info
        }))
    }
    else{
        res.send(JSON.stringify({
            status: 1,
            info: params.info
        }))
    }   
})
app.get("/get_course", async(req, res) => {
    let params=await teacher.get_teacher_timetableById(req.query.teacher_id)
    if(params.status != 1){
        res.send(JSON.stringify({
            status: 0,
            info: "Action error:" + params.info
        }))
    }
    else if(params.info.length == 0){
        res.send(JSON.stringify({
            status: 0,
            info:"Action error: Not found"
        }))
    }
    else{
        res.send(JSON.stringify({
            status: 1,
            info: params.info
        }))
    }
    
})
app.get("/start_exp", async(req, res) => {
    let params=await teacher.teacherStart_expPOST(req.query.classroom_id,req.query.class_id,req.query.process)
    if(params.status != 1 ){
        res.send(JSON.stringify({
            status: 0,
            info: "Action error:" + params.info
        }))
    }
    else{
        res.send(JSON.stringify({
            status: 1,
            info: params.info
        }))
    }   
})


module.exports = app