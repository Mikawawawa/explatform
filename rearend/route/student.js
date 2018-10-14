const app = require("express").Router()
const student=require("../service/StudentService")

app.get("/get_course", async(req, res) => {
    let params=await student.studentGet_courseGET(req.query.student_id)
    res.send(JSON.stringify({
        status:params.status,
        info:params.info
    }))
})
app.get("/get_exp", async(req, res) => {
    let params=await student.studentGet_expGET(req.query.student_id,req.query.course_id)
    res.send(JSON.stringify({
        status:params.status,
        info:params.info
    }))
})
app.get("/set_report", async(req, res) => {
    let params=await student.studentSet_reportPOST(req.query.student_id,req.query.exp_id,req.query.article)
    res.send(JSON.stringify({
        status:params.status,
        info:params.info
    }))
})
module.exports = app