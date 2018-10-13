const mysql = require('mysql');
const config = require('../config.json');
const connection = mysql.createConnection(config.mysql);
connection.connect();
connection.on("connect", () => {
    console.log("ok")
})

module.exports = connection

connection.execute=async function(command,params){
    return new Promise((resolve,reject)=>{
        connection.query(command,params,(error,results)=>{
            results=typeof(results)!=="undefined"?JSON.parse(JSON.stringify(results)):results
            // 错误处理
            if(error){
                resolve({
                    status:0,
                    info:"ACTION ERROR!"
                })
            // 空值处理
            }else if(typeof(results[0])=='undefined'){
                resolve({
                    status:0,
                    info:"NOT FOUND!"
                })
            // 返回结果
            }else{
                resolve({
                    status:1,
                    info:results
                })
            }
        })
    })
}