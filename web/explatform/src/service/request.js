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
export const request= async (method, url, body={}, queryParameters={}, form={}) => {
  method = method.toLowerCase()
  let keys = Object.keys(queryParameters)
  let queryUrl = url
  if (keys.length > 0) {
    queryUrl = domain+url + '?' + qs.stringify(queryParameters)
  }
  //post
  if (body) {
    body=qs.stringify(body)
    let response=await axios[method](queryUrl, body, config.post)
    return JSON.parse(JSON.stringify(response.data))
  } 
  //get
  else if (method === 'get') {
    return axios[method](queryUrl, {
      params: form
    }, config.get)
  }
  //other
  else {
    return axios[method](queryUrl, qs.stringify(form))
  }
}