const request=require("./request").request
const config=require("./config.json")

let hello=function(){
    return "a"
}
//用户登录
let Login=async (id,password) => {
    let response=await request('post',`${config.LOGIN}`,{
        id:id,
        password:password
    })
    return JSON.parse(JSON.stringify(response))
}
//获取用户权限
let getPower=async (type) => {
    let response=await request('get',`${config.GET_POWER}`,{
       type:type
    })
    return JSON.parse(JSON.stringify(response.data))
}
//根据学生的账号返回学生课表
let sGetCourse=async (id) => {
    let response=await request('get',`${config.S_GET_COURSE}`,{
       id:id
    })
    return JSON.parse(JSON.stringify(response.data))
}
//根据课程号获取实验的详情
let sGetExp=async (student_id,course_id) => {
    let response=await request('get',`${config.S_GET_EXP}`,{
        student_id:student_id,
        course_id:course_id
    })
    return JSON.parse(JSON.stringify(response.data))
}
//提交报告
let setReport=async (student_id,exp_id,article) => {
    let response=await request('post',`${config.SET_REPORT}`,{
        student_id:student_id,
        exp_id:exp_id,
        article:article
    })
    return JSON.parse(JSON.stringify(response.data))
}
//根据实验id获取所有学生的该实验信息
let tGetExp=async (class_id) => {
    let response=await request('get',`${config.T_GET_EXP}`,{
        class_id:class_id
    })
    return JSON.parse(JSON.stringify(response.data))
}
//设置某个学生某个实验的成绩(传入学生id、实验id和完整的成绩，设置学生信息)
let setGrade=async (student_id,exp_id,preview,action,report) => {
    let response=await request('post',`${config.SET_GRADE}`,{
        student_id:student_id,
        exp_id:exp_id,
        preview:preview,
        action:action,
        report:report
    })
    return JSON.parse(JSON.stringify(response.data))
}
//获取实验报告 根据报告id获取markdown报告的原始内容
let getReport=async (report_id) => {
    let response=await request('get',`${config.GET_REPORT}`,{
        report_id:report_id
    })
    return JSON.parse(JSON.stringify(response.data))
}
//根据教师号获取教师课表
let tGetCourse=async (teacher_id) => {
    let response=await request('get',`${config.T_GET_COURSE}`,{
        teacher_id:teacher_id
    })
    return JSON.parse(JSON.stringify(response.data))
}
//教师开始实验
let startExp=async (classroom_id,class_id, process) => {
    let response=await request('post',`${config.SET_GRADE}`,{
        classroom_id:classroom_id,
        class_id:class_id,
        process: process
    })
    return JSON.parse(JSON.stringify(response.data))
}
//获取教师课程实验
let getExplist=async (id) => {
    let response=await request('get',`${config.GET_EXPLIST}`,{
        id:id
    })
    return JSON.parse(JSON.stringify(response.data))
}

export default {
    request:request,
    Login:Login,
    getPower:getPower,
    sGetCourse:sGetCourse,
    sGetExp:sGetExp,
    setReport:setReport,
    tGetExp:tGetExp,
    setGrade:setGrade,
    getReport:getReport,
    tGetCourse:tGetCourse,
    startExp:startExp,
    getExplist:getExplist,
    hello:hello
}