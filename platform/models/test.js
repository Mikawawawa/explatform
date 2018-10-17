const modules=require("./modules")

//  modules.student_signin("17041802","戴维南等效电路","1").then(data=>{
//      console.log(data)
//  })

// modules.get_progress(17040318).then(data=>{
//     console.log(data)
// })

modules.student_signin(17031803,1,'创新性实验').then(data=>{
    console.log(data)
})

// modules.check_teacher(17041802).then(data=>{
//     console.log(data)
// })

// modules.put_grade(5,'17041802','123').then(data=>{
//     console.log(data)
// })

// modules.check_admin(17032117).then(data=>{
//     console.log(data)
// })

// modules.read_time(1).then(data=>{
//     console.log(data)
// })

// modules.put_log(10,'test=1').then(data=>{
//     console.log(data)
// })

// modules.read_log(1).then(data=>{
//     console.log(data)
// })

/*  name            parameter                   status
 *  get_progress    id                          OK.
 *  student_signin  password,id,experiment_id   OK
 *  check_teacher   password,id                 OK
 *  put_grade       mark,id,experiment_id       OK.
 *  check_admin     id                          OK
 *  read_time       id                          OK.
 *  put_log         id,log                      OK.
 *  read_log        id                          OK.
 */