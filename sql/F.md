experiment(***experiment_id*,*template_id***)
> experiment_id:实验号\
> template_id:模板编号 

classroom(**classroom_id**,*class_id*,*progress*)
> classroom_id:教室名\
> class_user:当前占用班级\
> progress:当前应当进行的实验

platform(**mac_address**,status)
> mac_address:MAC地址\
> status:状态

experiment_recard(***student_id*,*experiment_id***,*subject_id*,grade,present,operation,choice,section)
> student_id:学生学号\
> experiment_id:实验号\
> subject_id:对应课程教务编号\
> grade:总分\
> present:签到信息\
> operation:实验操作\
> choice:选择题\
> section:报告栏目

classroom_grant(***class_id*,*classroom_id***,*peroid*,*semester_id*)
> class_id:班级号\
> classroom_id:教室编号\
> peroid:时间段
> semester_id:占用学期

class_testbed(***class_id*,*mac_address***,column,row)
> class_id:班级号\
> mac_address:MAC地址\
> column：列\
> row:行