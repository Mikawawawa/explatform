const request=require("./request")

exports.Login=async (id,password) => {
    let response=await request('post',`${config.LOGIN}`,{
        id:id,
        password:password
    })
    return JSON.parse(JSON.stringify(response.data))
}

exports.getPower= async () => {
    return axios [get](`${config.GET_POWER}`, {
        params: form
    }, config.get)
}

exports.sGetCourse= async () => {
    return axios [get](`${config.S_GET_COURSE}`, {
        params: form
    }, config.get)
}

exports.sGetExp=async () => {
    return axios [get](`${config.S_COURSE_DETAIL}`, {
        params: form
    }, config.get)
}

exports.setReport=async (student_id,exp_id,article) => {
    let response=await request('post',`${config.SET_REPORT}`,{
        student_id:student_id,
        exp_id:exp_id,
        article:article
    })
    return JSON.parse(JSON.stringify(response.data))
}

exports.tCourseDetail=async () => {
    return axios [get](`${config.T_COURSE_DETAIL}`, {
        params: form
    }, config.get)
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

exports.getReport=async () => {
    return axios [get](`${config.GET_REPORT}`, {
        params: form
    }, config.get)
}

exports.tGetCourse=async () => {
    return axios [get](`${config.T_GET_COURSE}`, {
        params: form
    }, config.get)
}

exports.startExp=async (classroom_id,class_id, process) => {
    let response=await request('post',`${config.SET_GRADE}`,{
        classroom_id:classroom_id,
        class_id:class_id,
        process: process
    })
    return JSON.parse(JSON.stringify(response.data))
}