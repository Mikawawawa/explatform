const mysql = require('mysql');
const config = require('../config.json');
const connection = mysql.createConnection({
    host: "101.132.116.211",
    port: 3306,
    user: "root",
    password: "aptx4869",
    database: 'explatform',
    charset: "UTF8_GENERAL_CI",
    debug: false
});
// const connection = mysql.createConnection(config.mysql);
connection.connect();
connection.on("connect", (err) => {
    if (err) {
        console.error('error connecting: ' + err.stack);
        return;
    }
    console.log("db:ok")
})

module.exports = connection

connection.execute=async function(command,params){
    return new Promise((resolve,reject)=>{
        connection.query(command,params,(error,results)=>{
            //console.log(error)
            // 错误处理
            if(error){
                console.log(error)
                resolve({
                    status:0,
                    info:"ACTION ERROR!"
                })
            // 空值处理
            }else{
                results=results[0]
                if(typeof(results)=='undefined'){
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
            }
        })
    })
}
