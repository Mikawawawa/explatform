const connection=require("./connect")

/**
 * Author: 姜佐腾
 * Date: 2018年10月13日
 * Time: 16点50分
 * Comment: 
 */
exports.getCourse=async function(id) {
    let data=await connection.execute("CALL get_teacher_timetable(?)",[id])
    if(data.status!=1){
        return {    
            status: 0,
            info: "Action Error!"
        }
    }else{
        for(let i=0;i<data.info.length;i++){
            let subject_name=await connection.execute(`SELECT subject_name as name FROM subject WHERE subject_id=?`,[data.info[i].subject_id])
            subject_name=subject_name.info.name
            data.info[i].subject_name=subject_name
            data.info[i]={
                course_id:data.info[i].class_id,
                course_name:data.info[i].subject_name
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
    let data=await connection.execute("SELECT * FROM `experiment_recard` where student_id in (select student_id from `class_join` where class_id=?)",[class_id])
    console.log(data)
    if(data.status!=0){
        data.info={
            student_id:data.info.student_id,
            article:data.experiment_id,
            grade:{
                report:data.info.grade,
                action:data.info.operation
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