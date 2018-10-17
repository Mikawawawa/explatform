const teacher = require("./TeacherService")

teacher.teacherStart_expPOST("254","17040318","123").then(data=>{
    console.log(data)
})