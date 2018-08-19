-- 新增学期
CREATE PROCEDURE create_semester(
	in $id varchar(32),
	in $peroid varchar(32),
	in $stage varchar(32)
)
BEGIN
	DECLARE code TINYINT;
	insert into `semester`(semester_id,semester_peroid,semester_stage) VALUES ($id,$period,$stage);
	if ROW_COUNT()>1 then
		set code=1;
	else
		set code=0;
	end if;
-- 	SELECT status;
end;
-- 新增教学班
CREATE PROCEDURE create_class(
	in $class_id varchar(32),
	in $subject_id varchar(32),
	in $semester_id varchar(32),
	in $process varchar(32)
)
BEGIN
	DECLARE code TINYINT;
	insert into `class`(class_id,subject_id,semester_name) VALUES ($class_id,$subjec_id,$semester_id);
	insert into `experiment`(experiment_id) VALUES ($process);
	if ROW_COUNT()>1 then
		set code=1;
	else
		set code=0;
	end if;
-- 	SELECT status;
end;
--  新增实验模板
CREATE PROCEDURE create_template(
	in $subject_id varchar(32),
	in $template_id varchar(32)
)
BEGIN
	DECLARE CODE TINYINT;
	insert into `template_grant`(subject_id,template_id) VALUES ($subject_id,$template_id);
	if ROW_COUNT()>1 then
		set code=1;
	else 
		set code=0;
	end if;
-- SELECT status;
end;
--  新增实验记录
CREATE PROCEDURE create_experiment_recard(
	in $student_id varchar(32),
	in $experiment_id varchar(32),
	in $subject_id varchar(32),
	in $grade tinyint,
	in $present datetime,
	in $operation json,
	in $choice json,
	in $section json
)
BEGIN
	DECLARE CODE TINYINT;
	insert into `experiment_recard`(student_id,experiment_id,subject_id,grade,present,operation,choice,section) VALUES ($student_id,$experiment_id,$subject_id,$grade,$present,$operation,$choice,$section);
	if ROW_COUNT()>1 then
		set code=1;
	else 
		set code=0;
	end if;
-- SELECT status;
end;
--  新增班级下属实验
CREATE PROCEDURE create_experiment_grant(
	in $class_id varchar(32),
	in $template_id varchar(32)
)
BEGIN
	DECLARE CODE TINYINT;
	insert into `experiment_grant`(class_id,template_id) VALUES ($class_id,$template_id);
	if ROW_COUNT()>1 then
		set code=1;
	else 
		set code=0;
	end if;
-- SELECT status;
end;
--  修改班级进度
CREATE PROCEDURE update_class_process(
	in $class_id varchar (32),
	in $subject_id varchar(32),
	in $semester_id varchar(32),
	in $process varchar (32)
)
BEGIN
	DECLARE CODE TINYINT;
	update class set `process` = $process where `class_id`= $class_id and `subject_id`=$subject_id and `semester_id`=$semester_id;
	if ROW_COUNT()>1 then
		set code=1;
	else 
		set code=0;
	end if;
-- SELECT status;
end;
--  修改实验记录的签到信息
CREATE PROCEDURE update_experiment_recard_present(
	in $student_id varchar(32),
	in $experiment_id varchar(32),
	in $subject_id varchar(32),
	in $grade tinyint,
	in $present datetime,
	in $operation json,
	in $choice json,
	in $section json
)
BEGIN
	DECLARE CODE TINYINT;
	update experiment_recard set `present`=$present where `student_id`=$student_id and `experiment_id`=$experiment_id and `subject_id` =$subject_id;
	if ROW_COUNT()>1 then
		set code=1;
	else 
		set code=0;
	end if;
-- SELECT status;
end;
-- 按学生id查询课表
CREATE PROCEDURE get_student_timetable(
	in $student_id varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM
		class 
	WHERE
		class_id IN 
		(
			SELECT class_id FROM class_join WHERE student_id = $student_id
		);
END;
-- 按教室查询课表
CREATE PROCEDURE get_classroom_timetable(
	in $classroom varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM class WHERE classroom_id = $classroom_id;
END;
-- 按教师查询课表
CREATE PROCEDURE get_teacher_timetable(
	in $teacher_id varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM
		class 
	WHERE
		class_id IN 
		(
			SELECT class_id FROM class_grant WHERE teacher_id = $teacher_id
		);
END;
-- 按课程新增公告
CREATE PROCEDURE create_notice(
	in $notice_id varchar(32),
	in $user_id varchar(32),
	in $content varchar(32),
	in $time tinyint,
	in $class varchar(32)
)
BEGIN
	DECLARE code TINYINT;
	update notice set `class`=$content where class_id=$class;
	if ROW_COUNT()>1 then
			set code=1;
		else
			set code=0;
			end if;
-- 	select code;
END;