const mqtt = require('mqtt')
const package = require("../package.json")
const client = mqtt.connect(`mqtt://${package.config.mhost}:${package.config.mport}`)

client.on('connect', function () {
    console.log(`connect to ${package.config.mhost}:${package.config.mport}`)
    client.subscribe('test',{qos:1});//订阅主题为test的消息  
})
  
client.on('message',function(top,message) {  
    console.log(message.toString());  
});  