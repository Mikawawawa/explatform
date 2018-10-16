const request=require("./request").request
const config=require("./config.json")

let hello=function(){
    return "a"
}
let Login=async (id,password) => {
    let response=await request('post',`${config.LOGIN}`,{
        id:id,
        password:password
    })
    return JSON.parse(JSON.stringify(response))
}

let getPower=async (type) => {
    let response=await request('post',`${config.GET_POWER}`,{
       type:type
    })
    return JSON.parse(JSON.stringify(response.data))
}

let sGetCourse=async (id) => {
    let response=await request('post',`${config.S_GET_COURSE}`,{
       id:id
    })
    return JSON.parse(JSON.stringify(response.data))
}

let sGetExp=async (student_id,course_id) => {
    let response=await request('get',`${config.S_COURSE_DETAIL}`,{
        student_id:student_id,
        course_id:course_id
    })
    return JSON.parse(JSON.stringify(response.data))
}

let setReport=async (student_id,exp_id,article) => {
    let response=await request('post',`${config.SET_REPORT}`,{
        student_id:student_id,
        exp_id:exp_id,
        article:article
    })
    return JSON.parse(JSON.stringify(response.data))
}

let tCourseDetail=async (class_id) => {
    let response=await request('post',`${config.T_COURSE_DETAIL}`,{
        class_id:class_id
    })
    return JSON.parse(JSON.stringify(response.data))
}

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

let getReport=async (report_id) => {
    let response=await request('post',`${config.GET_REPORT}`,{
        report_id:report_id
    })
    return JSON.parse(JSON.stringify(response.data))
}

let tGetCourse=async (teacher_id) => {
    let response=await request('post',`${config.T_GET_COURSE}`,{
        teacher_id:teacher_id
    })
    return JSON.parse(JSON.stringify(response.data))
}
let startExp=async (classroom_id,class_id, process) => {
    let response=await request('post',`${config.SET_GRADE}`,{
        classroom_id:classroom_id,
        class_id:class_id,
        process: process
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
    tCourseDetail:tCourseDetail,
    setGrade:setGrade,
    getReport:getReport,
    tGetCourse:tGetCourse,
    startExp:startExp,
    hello:hello
}