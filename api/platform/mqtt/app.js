const mosca = require('mosca');
//构建自带服务器
const MqttServer = new mosca.Server({
    port: 1883
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
});

MqttServer.on('ready', function() {
    //当服务开启时
    console.log('mqtt is running...');
});