const request=require("./request")

exports.Login=async (id,password) => {
    let response=await request('post',`${config.LOGIN}`,{
        id:id,
        password:password
    })
    return JSON.parse(JSON.stringify(response.data))
}

exports.getPower=async (type) => {
    let response=await request('post',`${config.GET_POWER}`,{
       type:type
    })
    return JSON.parse(JSON.stringify(response.data))
}

exports.sGetCourse=async (id) => {
    let response=await request('post',`${config.S_GET_COURSE}`,{
       id:id
    })
    return JSON.parse(JSON.stringify(response.data))
}

exports.sGetExp=async (student_id,course_id) => {
    let response=await request('post',`${config.S_COURSE_DETAIL}`,{
        student_id:student_id,
        course_id:course_id
    })
    return JSON.parse(JSON.stringify(response.data))
}

exports.setReport=async (student_id,exp_id,article) => {
    let response=await request('post',`${config.SET_REPORT}`,{
        student_id:student_id,
        exp_id:exp_id,
        article:article
    })
    return JSON.parse(JSON.stringify(response.data))
}

exports.tCourseDetail=async (class_id) => {
    let response=await request('post',`${config.T_COURSE_DETAIL}`,{
        class_id:class_id
    })
    return JSON.parse(JSON.stringify(response.data))
}

exports.setGrade=async (student_id,exp_id,preview,action,report) => {
    let response=await request('post',`${config.SET_GRADE}`,{
        student_id:student_id,
        exp_id:exp_id,
        preview:preview,
        action:action,
        report:report
    })
    return JSON.parse(JSON.stringify(response.data))
}

exports.getReport=async (report_id) => {
    let response=await request('post',`${config.GET_REPORT}`,{
        report_id:report_id
    })
    return JSON.parse(JSON.stringify(response.data))
}

exports.tGetCours=async (teacher_id) => {
    let response=await request('post',`${config.T_GET_COURSE}`,{
        teacher_id:teacher_id
    })
    return JSON.parse(JSON.stringify(response.data))
}
exports.startExp=async (classroom_id,class_id, process) => {
    let response=await request('post',`${config.SET_GRADE}`,{
        classroom_id:classroom_id,
        class_id:class_id,
        process: process
    })
    return JSON.parse(JSON.stringify(response.data))
}