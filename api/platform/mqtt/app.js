const mosca = require('mosca')
const package = require("./package.json")
const MqttServer = new mosca.Server({
    port: package.config.mport
});

MqttServer.on('clientConnected', function(client) {
    //监听连接
    console.log('client connected', client.id);
});

MqttServer.on('published', function(packet, client) {
    //当客户端有连接发布主题消息
    console.log(`topic:${packet.topic}\tpayload:${packet.payload.toString()}`)
});

MqttServer.on('ready', function() {
    //当服务开启时
    console.log(`mqtt is running on ${package.config.mport}`);
});