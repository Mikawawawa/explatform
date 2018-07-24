import paho.mqtt.client as mqtt  

# python 连接mqtt的参考函数，预计会出现使用mqtt进行进程间通信的情况

def on_connect(client, userdata, flags, rc):  
    print("Connected with result code "+str(rc))  
  
    # 放在on_connect函数里意味着  
    # 重新连接时订阅主题将会被更新  
    client.subscribe("test")  
  
def on_message(client, userdata, msg):  
    print("Topic:"+msg.topic+" Message:"+str(msg.payload))  
  
client = mqtt.Client()  

client.on_connect = on_connect
client.on_message = on_message
client.connect("101.132.116.211", 8201, 60)
client.loop_forever()  