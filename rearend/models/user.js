const connection=require("./connect")

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