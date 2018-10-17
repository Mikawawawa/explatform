const connection=require("./connect")

/**
 * Author: 姜佐腾
 * Date: 2018年10月13日
 * Time: 16点50分
 * Comment: 
 */
exports.getCourse=async function(id) {
    // SELECT * FROM experiment_recard WHERE experiment_id in (
    //     SELECT experiment_id from experiment_grant WHERE class_id in(
    //         SELECT class_id FROM class WHERE class_id="17040318"
    //     )
    // )
    let data=await connection.batch(`
    SELECT * FROM experiment_recard WHERE experiment_id in (
        SELECT experiment_id from experiment_grant WHERE class_id in(
            SELECT class_id FROM class WHERE class_id=?
        )
    )`,[id])
    if(data.status!=1){
        return {    
            status: 0,
            info: "Action Error!"
        }
    }else{
        console.log(data)
        for(let i=0;i<data.info.length;i++){
            data.info[i]={
                student_id:data.info[i].student_id,
                article:data.info[i].experiment_id,
                grade:{
                    action:Number(data.info[i].operation),
                    report:Number(data.info[i].grade)
                }
            }
        }
        return data
    }
}

/**
 * Author: 李心慧
 * Date: 2018年10月15日
 * Time: 18点32分
 * Comment: 
 */
exports.get_exp=async function(class_id){
    let data=await connection.batch("SELECT * FROM `experiment_recard` where student_id in (select student_id from `class_join` where class_id=?)",[class_id])
    // console.log(data)
    if(data.status!=0){
        for(let i=0;i<data.info.length;i++){
            data.info[i]={
                student_id:data.info[i].student_id,
                article:data.info[i].experiment_id,
                grade:{
                    report:data.info[i].grade,
                    action:data.info[i].operation
                }
            }
        }
        return data
    }else{
        return data
    }
}

/**
 * Author: 姜佐腾
 * Date: 2018年10月13日
 * Time: 
 * Comment: 
 */
exports.getReport=async function(report_id){
    let data=await connection.execute("SELECT * FROM `experiment_recard` where experiment_id=?",[report_id])
    if(data.status!=0){
        data.info=data.info.section
        return data
    }else{
        return data
    }
}

/**
 * Author: 
 * Date: 
 * Time: 
 * Comment: grade需要在前面处理好，这里是实际要修改成的分数，
 * 包括action、report、preview属性，
 * 如果不修改某个值的话，要传进来原来的值
 */
exports.setGrade=async function(student_id,exp_id,grade){
    let data=await connection.execute("UPDATE `experiment_recard` SET `operation` = ?,`grade`=? WHERE `student_id` = ? AND `experiment_id` = ?",[grade.action,grade.report,student_id,exp_id])
    if(data.info!='ACTION ERROR!'){
        return {
            status:1,
            info:"ACTION SUCCESSFUL!"
        }
    }else{
        return data
    }
}

/**
 * Author: 
 * Date: 
 * Time: 
 * Description: 
 */
exports.startExp=async function(classroom_id,class_id,process){
    await connection.execute("UPDATE `class` SET `process` = ? where class_id=?",[process,class_id])
    await connection.execute("UPDATE `classroom` SET `progress` = ? where classroom_id=?",[process,classroom_id])
    return{
        status:1,
        info:"ACTION SUCCESS"
    }
}

exports.getExplist=async function(course_id){
    let data=await connection.execute('SELECT DISTINCT experiment_id FROM experiment_recard WHERE subject_id=?',[course_id])
    if(data.status==0){
        return data
    }else{
        return data
    }
}