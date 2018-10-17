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
exports.student_signin = async function(id,mac,exp){
    let data = await connection.execute("SELECT `student_name` FROM `student` WHERE `student_id`= ? ",[id])
    if(data.status==0){
        return {
            status:0
        }
    }
    await connection.execute("UPDATE `experiment_recard` SET `present`= ? WHERE (`student_id`=?) AND (`experiment_id`=?)",[new Date().toLocaleString(),mac,exp])
    return {
        status:data.status,
        info:data.info.student_name,
        sid: id
    }
}

//老师验证
exports.check_teacher = async function(password,id){   
    let data = await connection.execute("SELECT `user_type` FROM `user` WHERE `password`= ? AND `user_id`= ?",[password,id])
    let nam = await connection.execute("SELECT `teacher_name` FROM `teacher` WHERE `teacher_id`= ?",[id])
    return {
        status:data.status,
        info:data.info.user_type,
        name:nam.info.teacher_name
    } 
}

//上传成绩
exports.put_grade = async function(mark,id,experiment_id){
    let data = await connection.execute("UPDATE `experiment_recard` SET `operation` = ? WHERE `student_id` = ? AND `experiment_id` = ?",[mark,id,experiment_id])
    return {
        status:1,
        info: "EXECUTE DOWN!"
    }
}

//管理员验证
exports.check_admin = async function(password,id){
    let data = await connection.execute("SELECT `user_type` FROM `user` WHERE `user_id`= ? AND `password`= ?",[id,password])
    return {    
        //status:1,
        status:data.status,
        info:data.info
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


