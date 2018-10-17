const connection=require("./connect")

/**
 * Author: 
 * Date: 
 * Time: 
 * Comment: 
 */
exports.getCourse= async function(student_id){
    var result=[];
    let data=await connection.batch(`
    SELECT * FROM subject WHERE subject_id in(
        SELECT DISTINCT subject_id FROM class WHERE class_id IN (
            SELECT DISTINCT class_id FROM class_join WHERE student_id=?
        )
    )`,[student_id]);
    //return data
    if(data.status == 0){
        return data
    }
    else{
        for(let i=0; i<data.info.length; i++){
            data.info[i]={
                course_id:data.info[i].subject_id,
                course_name:data.info[i].subject_name
            }
        }
        return data
    }
}

/**
 * Author: 
 * Date: 
 * Time: 
 * Comment: 
 */
exports.getExp=async function(course_id,student_id){
    var result=[];
    //let data =await connection.execute("SELECT * FROM `experiment_recard` where student_id=? and experiment_id in (SELECT experiment_id FROM experiment WHERE `subject_id` = ?)",[student_id, course_id]);
    let data =await connection.batch("SELECT * FROM `experiment_recard` where student_id=? and experiment_id in (SELECT experiment_id FROM experiment WHERE `subject_id` = ?)",[student_id, course_id]);
    if(data.info.length == 0){
        return{
            status:0,
            info:"Not Found!"
        }
    }
    else if(data.status != 1){
        return{
            status: 0,
            info:"Action Error!"
        }
    }
    else{
        for(let i=0; i<data.info.length; i++){
            result[i] = {
                id: data.info[i].experiment_id,
                name: null,
                score:data.info[i].grade,
                student_id:data.info[i].student_id
            }
        }
        return {
            status:1,
            info:result    
        }
    }
}

/**
 * Author: 
 * Date: 
 * Time: 
 * Comment: 
 */
exports.setReport=async function(student_id,exp_id,article){
    let data = await connection.execute("UPDATE experiment_recard set `section` = ? where `student_id` = ? and `experiment_id` = ?",[article, student_id,exp_id]);
    return{
       status:1,
       info:"EXECUTE DOWN!"
    }
}