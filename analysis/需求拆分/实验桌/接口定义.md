### 硬件侧接口定义
> 本文档定义了具体接口及其实现的功能，但是具体接口及文档将另外制作

根据流程图，可以拆分出如下事件

1. 教师向服务器更新实验进度
2. 服务器向网关推送班级号、实验进度，并请求网关打开全部打分机
3. 打分机从网关处获取到班级号、实验进度，从二维码中获得学生的学号，以及自己的mac地址，将上述信息上传至服务器，服务器进行签到处理。
    1. 若签到成功，服务器向打分机返回成功信息及操作信息，并向网关请求打开对应的试验台电源，并在数据库中更新桌子的占用信息
    2. 若签到失败，服务器向打分机返回错误码

需要实现的api

教师更新进度
/teacher/update_processs/

网关获取电源信息
/gateway/get_pmessage?class=
```json
{
    powerp:-1|0|1,
    powert:[
        {
            row:1,
            line:3
        },
        {
            row:1,
            line:3
        }
    ],
}
```
网关获取实验信息

/getway/get_emessage/
```json

{
    class:16040315,
    process:7
}
```
/dialing/sign?sid=&cid=&process=&mac=
- 成功:
```
{
    code:1,
    info:["操作一","操作二"]
}
```
- 失败:
```
{
    code:0,
    info:"错误的学生信息"
}
```
除流程图中给出的事件，可以预见将会有注册等其他事件，预计会有
1. 打分机注册自身身份
2. 打分机验证教师身份
3. 打分机打分
4. .......没想到

/dialing/init?cid=&row=&line=
```
{
    code:1|0
}
```
/dialing/check_teacher?tid=
```
{
    code:1|0
}
```
/dialing/put_grade/?sid=&cid=&process=&act=&grade=
```
{
    code:2|1|0...
}
```