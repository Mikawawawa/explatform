const connection=require("./connect")



/**
 * Author: 
 * Date: 
 * Time: 
 * Comment: 
 */
exports.getCourse= async function(student_id){
    var res=[];
    let data=await connection.execute("call get_student_timetable(?)",[student_id]);
    //return data
    for(let i=0; i<data.info.length; i++){
        res[i] = {
            course_id: data.info[i].subject_id,
            type: null,
            description: "课程id号"
        }
    }
    return {
        status:1,
        info:res
    }

}

/**
 * Author: 
 * Date: 
 * Time: 
 * Comment: 
 */
exports.getExp=async function(course_id,student_id){
    var res=[];
    let data =await connection.execute("SELECT * FROM `experiment_recard` where student_id=? and experiment_id in (SELECT experiment_id FROM experiment WHERE `subject_id` = ?)",[student_id, course_id]);
    //let data = await connection.execute("SELECT * FROM `experiment_recard` where student_id='17041802' and experiment_id in (SELECT experiment_id FROM experiment WHERE `subject_id` = '101')")
    // for(let i=0; i<data.info.length; i++){
    //     res[i] = {
    //         id: data.info[i].experiment_id,
    //         name: null,
    //         score:data.info[i].grade,
    //         student_id:data.info[i].student_id
    //     }
    // }
    return {
        status:1,
        info:{
            id: data.info.experiment_id,
            name: null,
            score:{
                grade:data.info.grade,
                operation:data.info.operation
            },
            student_id:data.info.student_id
        }      
    }
    // return {
    //     res
    // } 
    // return{
    //     status:1,
    //     info:"EXECUTE DOWN!"
    // }
}

/**
 * Author: 
 * Date: 
 * Time: 
 * Comment: 
 */
exports.setReport=async function(student_id,exp_id,article){
    let data =await connection.execute("UPDATE experiment_recard set `section` = ? where `student_id` = ? and `experiment_id` = ?",[article, student_id,exp_id]);
    return{
        status:1,
        info:"EXECUTE DOWN!"
    }
}