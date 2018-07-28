classroom(**classroom_id**,*class_id*,*progress*,column,row)
| 类型        | 名称          | 解释     |
| ----------- | ------------- | -------- |
|varchar(32)|classroom_id|教室名|
|varchar(32)|class_user|当前占用班级|
|varchar(32)|progress|当前应当进行的实验|
|tinyint|column|列|
|tinyint|row|行|

experiment_grant(***class_id*,*experiment_id***)
| 类型        | 名称          | 解释     |
| ----------- | ------------- | -------- |
|varchar(32)|class_id|班级号|
|varchar(32)|experiment_id|实验号|

classroom_grant(***class_id*,*classroom_id***,*peroid*,*semester_id*)
| 类型        | 名称          | 解释     |
| ----------- | ------------- | -------- |
|varchar(32)|class_id|班级号|
|varchar(32)|classroom_id|教室编号|
|tinyint|peroid|时间段|
|varchar(32)|semester_id|占用学期

platform_grant(***class_id*,*mac_address***,column,row)
| 类型        | 名称          | 解释     |
| ----------- | ------------- | -------- |
|varchar(32)|class_id|班级号|
|varchar(32)|mac_address|MAC地址|
|tinyint|column|列|
|tinyint|row|行|

class_application(***class_id*,*teacher_id***,status)
| 类型        | 名称          | 解释     |
| ----------- | ------------- | -------- |
|varchar(32)|class_id|教学班编号|
|varchar(32)|teacher_id|教师工号|
|tinyint|status|申请状态|

class_grant(***class_id*,*teacher_id***)
| 类型        | 名称          | 解释     |
| ----------- | ------------- | -------- |
|varchar(32)|class_id|教学班编号|
|varchar(32)|teacher_id|教师工号|

class_notice(***class_id*,*notice_id***)
| 类型        | 名称          | 解释     |
| ----------- | ------------- | -------- |
|varchar(32)|class_id|教学班编号|
|varchar(32)|notice_id|通知编号|

class_join(***class_id*,*student_id***)
| 类型        | 名称          | 解释     |
| ----------- | ------------- | -------- |
|varchar(32)|class_id|教学班编号|
|varchar(32)|student_id|学生学号|