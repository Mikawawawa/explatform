semester(**semester_id**,semester_peroid,semester_stage)
> semester_id:学期编号\
> semester_peroid:学期年段\
> semester_stage:学期阶段

class(**class_id**,*subject_id*,*semester_id*,*process*)
> class_id:教学班编号\
> subject_id:学科编号\
> semester_id:所在学科\
> process:当前应当进行的实验

class_application(***class_id*,*teacher_id***,status)
> class_id:教学班编号\
> teacher_id:教师工号\
> status:申请状态

class_grant(***class_id*,*teacher_id***)
> class_id:教学班编号\
> teacher_id:教师工号

notice(**notice_id**,*user_id*,notice_content,notice_time)
> notice_id:通知编号\
> user_id:发布者id\
> notice_content:发布内容\
> notice_time:发布日期时间

class_notice(***class_id*,*notice_id***)
> class_id:教学班编号\
> notice_id:通知编号

class_join(***class_id*,*student_id***)
> class_id:教学班编号\
> student_id:学生学号