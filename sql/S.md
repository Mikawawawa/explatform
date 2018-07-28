user(**user_id,user_type**,password)
> user_id:用户登陆名
> user_type:用户类型
> password:用户密码

subject（**subject_id**,subject_name)
> subject_id:教务编号\
> subject_name:学科名称

teacher(**teacher_id**,teacher_name)
> teacher_id:教师工号\
> teacher_name:教师名字

student(**student_id**,student_name)
> student_id:学生学号\
> student_name:学生姓名

template(**template_id**,operation,choice,section)
> template_id:模板编号\
> operation:实验操作\
> choice:选择题\
> section:报告栏目

subejct_template(***subject_id*,*template_id***)
> subject_id:学科教务编号\
> template_id:模板编号