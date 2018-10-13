/* eslint-disable */
import axios from 'axios'
import qs from 'qs'
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
    return axios [get](`${config.GET_COURSE}`, {
        params: form
      }, config.get)
    }


  