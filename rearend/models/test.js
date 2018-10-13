const teacher=require("./teacher")

// teacher.getCourse("17031803").then(data=>{
//     console.log(data)
// })

// teacher.getExp('17040318').then(data=>{
//     console.log(data)
// })

// teacher.getReport('123').then(data=>{
//     console.log(data)
// })

// teacher.setGrade('17041802','123',{
//     action:4,
//     report:3
// }).then(data=>{
//     console.log(data)
// })

teacher.startExp(
    '254','17040318','123'
).then(data=>{
    console.log(data)
})