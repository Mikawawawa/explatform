template_grant(***subject_id*,*template_id***)
| 类型        | 名称        | 解释         |
| ----------- | ----------- | ------------ |
| varchar(32) | subject_id  | 学科教务编号 |
| varchar(32) | template_id | 模板编号     |

notice(**notice_id**,*user_id*,notice_content,notice_time)
| 类型        | 名称           | 解释         |
| ----------- | -------------- | ------------ |
| varchar(32) | notice_id      | 通知编号     |
| varchar(32) | user_id        | 发布者id     |
| text        | notice_content | 发布内容     |
| datetime    | notice_time    | 发布日期时间 |

experiment(***experiment_id*,*template_id***)
| 类型        | 名称          | 解释     |
| ----------- | ------------- | -------- |
| varchar(32) | experiment_id | 实验号   |
| varchar(32) | template_id   | 模板编号 |
