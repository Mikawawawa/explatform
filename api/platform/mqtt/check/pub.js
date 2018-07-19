const mqtt = require('mqtt')
const package = require("../package.json")
const client = mqtt.connect(`mqtt://${package.config.mhost}:${package.config.mport}`)



client.on('connect', function () {
    console.log(`connect to mqtt://${package.config.mhost}:${package.config.mport}`)
})
client.on("error",(err)=>{
    console.log(err)
})

let message = 'setr=xxxxxxx1xx'
setInterval(()=>{
    client.publish('test', message, { qos: 0, retain: true })
}, 2000);