class(**class_id**,*subject_id*,*semester_id*,*process*)
| 类型        | 名称               | 解释 |
| ----------- | ------------------ | ---- |
| class_id    | 教学班编号         |
| subject_id  | 学科编号           |
| semester_id | 所在学科           |
| process     | 当前应当进行的实验 |

experiment_recard(***student_id*,*experiment_id***,*subject_id*,grade,present,operation,choice,section)
| 类型        | 名称          | 解释             |
| ----------- | ------------- | ---------------- |
| varchar(32) | student_id    | 学生学号         |
| varchar(32) | experiment_id | 实验号           |
| varchar(32) | subject_id    | 对应课程教务编号 |
| tinyint     | grade         | 总分             |
| datatime    | present       | 签到信息         |
| text        | operation     | 实验操作         |
| text        | choice        | 选择题           |
| text        | section       | 报告栏目         |