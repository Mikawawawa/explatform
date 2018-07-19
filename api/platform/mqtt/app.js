const mosca = require('mosca');
//构建自带服务器
const package = require("./package.json");
const MqttServer = new mosca.Server({
    port: package.config.mport
});

MqttServer.on('clientConnected', function(client) {
    //监听连接
    console.log('client connected', client.id);
});
/**
 * 监听MQTT主题消息
 **/
MqttServer.on('published', function(packet, client) {
    //当客户端有连接发布主题消息
    console.log(`topic:${packet.topic}\tpayload:${packet.payload.toString()}`)
    MqttServer.publish({ topic: 'other', payload: 'sssss' });
});

MqttServer.on('ready', function(payload) {
    //当服务开启时
    console.log(`mqtt is running on ${package.config.mport}`);
});