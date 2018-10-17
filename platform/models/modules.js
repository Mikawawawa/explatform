const connection=require('./connect')

//获取实验进度：发MAC地址
exports.get_progress = async function(id){
    let data = await connection.execute(`
        SELECT process FROM 
        class JOIN platform_grant
        ON platform_grant.class_id=class.class_id
        WHERE platform_grant.mac_address=? 
    `,[id])
    return {
        status:data.status,
        info:data.info.process
    }
}

//学生签到
exports.student_signin = async function(id,mac_id,exp_id){
    let data = await connection.execute("SELECT `student_name` FROM `student` WHERE `student_id`= ? ",[id])
    await connection.execute("UPDATE `experiment_recard` SET `present`= ? WHERE (`student_id`=?) AND (`experiment_id`=?)",[new Date().toLocaleString(),id,exp_id])
    //console.log(arguments)
    return {
        status:data.status,
        info:data.info.student_name,
        sid: id
    }
}

//老师验证
//打分机发过来的password是数据库里的user_id
//打分机发过来的id是数据库里的user_type
exports.check_teacher = async function(id){   
    // let data = await connection.execute("SELECT `user_type` FROM `user` WHERE `password`= ? AND `user_id`= ?",[password,id])
    // let nam = await connection.execute("SELECT `teacher_name` FROM `teacher` WHERE `teacher_id`= ?",[id])
    //let data = await connection.execute("SELECT user_type FROM teacher JOIN user ON teacher.teacher_id=user.user_id WHERE `user`.user_id=?",[id])
    let data = await connection.execute("SELECT COUNT(*) FROM user WHERE user_type = '2' AND user_id =?",[id])
    return {
        status:data.status,
    } 

}

//上传成绩
exports.put_grade = async function(mark,id,experiment_id){
    let data = await connection.execute("UPDATE `experiment_recard` SET `operation` = ? WHERE `student_id` = ? AND `experiment_id` = ?",[mark,id,experiment_id])
    return {
        status:1
    }
}

//管理员验证
exports.check_admin = async function(password){
    //let data = await connection.execute("SELECT `user_type` FROM `user` WHERE `user_id`= ?",[password])
    let data = await connection.execute("SELECT COUNT(*) FROM user WHERE user_type = '1' AND user_id =  17041802",[password])
    /////////////////////////////////////////第一次改动
    // return {    
    //     //status:1,
    //     status:data.status,
    //     data.info.user_type
    // }
    /////////////////////////////////////////第二次改动
    // if(data.info.user_type==1)
    //     return{status:1}
    // else return{status:0}
    return {
        status:data.status,
    }
}

//时间
exports.read_time = async function(id){
    var myDate = new Date();
    return {
        status:1,
        info: myDate.toLocaleString()
    }
}

//上传日志信息
exports.put_log = async function(id,log){
    let data = await connection.execute("INSERT INTO logs(log_id,log) VALUES (?,?)",[id,log])
    return {
        //status:1,
        status:data.status,
        info:data.info
    }
}

//读取日志信息
exports.read_log = async function(id){
    let data = await connection.execute("SELECT `log` FROM `logs` WHERE `log_id`=?",[id])
    return {
        //status:1,
        status:data.status,
        info:data.info
    }
}


