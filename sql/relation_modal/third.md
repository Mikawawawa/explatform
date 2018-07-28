classroom(**classroom_id**,*class_id*,*progress*,column,row)
> classroom_id:教室名\
> class_user:当前占用班级\
> progress:当前应当进行的实验\
> column：列\
> row:行

experiment_grant(***class_id*,*experiment_id***)
> class_id:班级号\
> experiment_id:实验号\

classroom_grant(***class_id*,*classroom_id***,*peroid*,*semester_id*)
> class_id:班级号\
> classroom_id:教室编号\
> peroid:时间段\
> semester_id:占用学期

platform_grant(***class_id*,*mac_address***,column,row)
> class_id:班级号\
> mac_address:MAC地址\
> column:列\
> row:行

class_application(***class_id*,*teacher_id***,status)
> class_id:教学班编号\
> teacher_id:教师工号\
> status:申请状态

class_grant(***class_id*,*teacher_id***)
> class_id:教学班编号\
> teacher_id:教师工号

class_notice(***class_id*,*notice_id***)
> class_id:教学班编号\
> notice_id:通知编号

class_join(***class_id*,*student_id***)
> class_id:教学班编号\
> student_id:学生学号