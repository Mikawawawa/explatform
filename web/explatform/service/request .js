/* eslint-disable */
import axios from 'axios'
import config from "./config.json"
let domain = config.domain
config.post={
    headers:{'Content-Type':'application/x-www-form-urlencoded'}
}
config.get={}

export const getDomain = () => {
  return domain
}
export const setDomain = ($domain) => {
  domain = $domain
}

/**
 * 
 * @param {*} method 
 * @param {*} url 
 * @param {*} body 
 * @param {*} queryParameters URL传参
 * @param {*} form FORMDATA
 */
export default async (id,password) => {
    let response=await request('post',`${config.LOGIN}`,{
        id:id,
        password:password
    })
    return JSON.parse(JSON.stringify(response.data))
}

export default async () => {
    return axios [get](`${config.GET_POWER}`, {
        params: form
    }, config.get)
}

export default async () => {
    return axios [get](`${config.S_GET_COURSE}`, {
        params: form
    }, config.get)
}

export default async () => {
    return axios [get](`${config.S_COURSE_DETAIL}`, {
        params: form
    }, config.get)
}

export default async (student_id,exp_id,article) => {
    let response=await request('post',`${config.SET_REPORT}`,{
        student_id:student_id,
        exp_id:exp_id,
        article:article
    })
    return JSON.parse(JSON.stringify(response.data))
}

export default async () => {
    return axios [get](`${config.T_COURSE_DETAIL}`, {
        params: form
    }, config.get)
}

export default async (student_id,exp_id,preview,action,report) => {
    let response=await request('post',`${config.SET_GRADE}`,{
        student_id:student_id,
        exp_id:exp_id,
        preview:preview,
        action:action,
        report:report
    })
    return JSON.parse(JSON.stringify(response.data))
}

export default async () => {
    return axios [get](`${config.GET_REPORT}`, {
        params: form
    }, config.get)
}

export default async () => {
    return axios [get](`${config.T_GET_COURSE}`, {
        params: form
    }, config.get)
}

export default async (classroom_id,class_id, process) => {
    let response=await request('post',`${config.SET_GRADE}`,{
        classroom_id:classroom_id,
        class_id:class_id,
        process: process
    })
    return JSON.parse(JSON.stringify(response.data))
}