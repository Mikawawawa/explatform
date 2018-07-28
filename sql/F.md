experiment(**experiment_id**)
> experiment_id:实验号 

classroom(**classroom_id**,class_user,progress)
> classroom_id:教室名\
> class_user:占用班级\
> progress:进度

testbed（**mac_address**,state)
> mac_address:MAC地址\
> state:状态

student_experiment(***student_id*,*experiment_id***)
> student_id:学生学号\
> experiment_id:实验号

experiment_template(***experiment_id*,*template_id***)
> experiment_id:实验号\
> template_id:模板编号

class_classroom(***class_id*,*classroom_id***)
> class_id:班级号\
> classroom_id:教室名

class_testbed(***class_id*,*mac_address***,column,row)
> class_id:班级号\
> mac_address:MAC地址\
> column：列\
> row:行