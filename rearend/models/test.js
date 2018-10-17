const teacher=require("./teacher")
const user=require("./user")
const student=require("./student")
const mqtt=require("./mqtt")

// mqtt.beginExperiment("111","0|123")
//mqtt.noticePower("000","1")
// student.getCourse("17041802").then(data=>{
//     console.log(data)
//     // console.log(error)

// })

// student.getExp("101","17041801").then(data=>{
//     console.log("out",data)
// })

// student.setReport("17041802","123",'123').then(data=>{
//     console.log(data)
// })
// user.login("17031803","aptx4869").then(data=>{
//     console.log(data)
// })
// user.getPower("17031803").then(data=>{
//     console.log(data)
// })
/**
 * 测试人：姜佐腾
 * 日期：2018年10月13日
 */

teacher.getCourse("17031803").then(data=>{
    console.log(data)
})

// teacher.get_exp('17040318').then(data=>{
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

// teacher.startExp(
//     '254','17040318','123'
// ).then(data=>{
//     console.log(data)
// })


/** 
 * 测试人：姜佐腾
 * 日期：2018年10月14日
*/
// user.login('17041802',"aptx4869").then(data=>{
//     console.log(data)
// })

// user.getPower('17041802').then(data=>{
//     console.log(data)
// })

// student.getCourse("17041802").then(data=>{
//     console.log(data)
// })