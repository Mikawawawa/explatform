const connection=require("./connect")
const QRCode = require('qrcode')
const fs = require('fs')
const md5=require('md5')
/**
 * Author: 姜佐腾
 * Date: 2018年10月14日
 * Time: 13点59分
 * Description: 
 */
exports.login=async function login(id,password) {
    let data=await connection.execute("SELECT * FROM `user` WHERE `user_id`=? and `password`=?",[id,password])
    if(typeof(data.info)!="string"){
        return data
    }else{
        data.info="LOGIN SUCCESSFUL"
        return data
    }
}

/**
 * Author: 姜佐腾
 * Date: 2018年10月14日
 * Time: 
 * Description: 1:学科、2:教师、3:学生
 */
exports.getPower=async function getPower(id){
    let data=await connection.execute("SELECT DISTINCT user_type FROM `user` WHERE `user_id`=?",[id])
    if(data.status==0){
        return data
    }else{
        console.log(data.info.user_type)
        if(data.info.user_type==1){
            data.info={
                user_type:"学科负责人"
            }
        }else if(data.info.user_type==2){
            data.info={
                user_type:"教师"
            }
        }else{
            data.info={
                user_type:"学生"
            }
        }
        return data
    }
}



exports.getQrcode=async function qrcode(prams="123"){
    return Promise((resolve,reject)=>{
        prams=md5(prams)
        QRCode.toFile(`./public/${prams}.png`, prams, {
            color: {
              dark: '#333',  // Blue dots
              light: '#0000' // Transparent background
            }
          }, function (err) {
            if (err) 
                console.log(err)
                var timeout_ms = 10*60*1000; // 5 seconds
                setTimeout(function() {
                //删除文件
                    fs.unlink(`../public/${prams}.png`, function (err) {
                        // 判断 如果有错 抛出错误 否则 打印删除成功
                        if (err) {
                            throw err;
                        } 
                        console.log('删除成功!')
                    })
                }, timeout_ms);
                resolve(`./public/${prams}.png`)            
          })
    })
}

