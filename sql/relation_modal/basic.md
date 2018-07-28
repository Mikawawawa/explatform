<!-- 不存在外键的表项 -->
user(**user_id,user_type**,password)
| 类型        | 名称      | 解释       |
| ----------- | --------- | ---------- |
| varchar(32) | user_id   | 用户登陆名 |
| tinyint     | user_type | 用户类型   |
| varchar(32) | password  | 用户密码   |

subject(**subject_id**,subject_name)
| 类型        | 名称         | 解释     |
| ----------- | ------------ | -------- |
| varchar(32) | subject_id   | 教务编号 |
| varchar(32) | subject_name | 学科名称 |

teacher(**teacher_id**,teacher_name)
| 类型        | 名称         | 解释     |
| ----------- | ------------ | -------- |
| varchar(32) | teacher_id   | 教师工号 |
| varchar(32) | teacher_name | 教师名字 |

student(**student_id**,student_name)
| 类型        | 名称         | 解释     |
| ----------- | ------------ | -------- |
| varchar(32) | student_id   | 学生学号 |
| varchar(32) | student_name | 学生姓名 |

template(**template_id**,operation,choice,section)
| 类型        | 名称        | 解释     |
| ----------- | ----------- | -------- |
| varchar(32) | template_id | 模板编号 |
| text        | operation   | 实验操作 |
| text        | choice      | 选择题   |
| text        | section     | 报告栏目 |

platform(**mac_address**,status)
| 类型        | 名称        | 解释    |
| ----------- | ----------- | ------- |
| varchar(32) | mac_address | MAC地址 |
| varchar(32) | status      | 状态    |

peroid(**peroid_id**,defination)
| 类型        | 名称       | 解释           |
| ----------- | ---------- | -------------- |
| tinyint     | peroid_id  | 上课时间段编号 |
| varchar(64) | defination | 文字定义       |

semester(**semester_id**,semester_peroid,semester_stage)
| 类型        | 名称            | 解释     |
| ----------- | --------------- | -------- |
| varchar(32) | semester_id     | 学期编号 |
| int         | semester_peroid | 学期年段 |
| bit         | semester_stage  | 学期阶段 |