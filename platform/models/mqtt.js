var mqtt    = require('mqtt');
var client  = mqtt.connect('mqtt://120.79.88.153:8201');
/*
  mqtt：
    1.开始实验 主题 编号 内容{expre 110}
    2.通知电源 内容{id:110}
*/
const beginExperiment = function (target,message) {
  client.publish(`experiment_${target}`, message);
}

const noticePower = function (target, message) {
  client.publish(`power_${target}`, message);
}


exports.beginExperiment = beginExperiment;
exports.noticePower = noticePower;


