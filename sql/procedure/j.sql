-- 新增用户
CREATE PROCEDURE create_user(
	in $id varchar(32),
	in $password varchar(32),
	in $name varchar(32),
	in $type tinyint
)
BEGIN
	DECLARE code TINYINT;
	IF $type>0 THEN
			insert into user(user_id,password,user_type) VALUES ($id,$password,$type);
			set code=1;
			CASE $type
	-- 		1:学科
				WHEN 1 THEN
					call create_subject($id,$name);
	-- 		2:教师
				WHEN 2 THEN
					call create_teacher($id,$name);
	-- 		3:学生
				WHEN 3 THEN
					call create_student($id,$name);
			END CASE;
	ELSE
		set code=0;
	END IF;
	SELECT code;
end;
-- 新增课程
CREATE PROCEDURE create_subject(
	in $id varchar(32),
	in $name varchar(32)
)
BEGIN
	DECLARE code TINYINT;
	insert into `subject`(subject_id,subject_name) VALUES ($id,$name);
	if ROW_COUNT()>1 then
		set code=1;
	else
		set code=0;
	end if;
-- 	SELECT status;
end;
-- 新增学生
CREATE PROCEDURE create_student(
	in $id varchar(32),
	in $name varchar(32)
)
BEGIN
	DECLARE code TINYINT;
	insert into `student`(student_id,student_name) VALUES ($id,$name);
	if ROW_COUNT()>1 then
		set code=1;
	else
		set code=0;
	end if;
-- 	SELECT status;
end;
-- 新增教师
CREATE PROCEDURE create_teacher(
	in $id varchar(32),
	in $name varchar(32)
)
BEGIN
	DECLARE code TINYINT;
	insert into `teacher`(teacher_id,teacher_name) VALUES ($id,$name);
	if ROW_COUNT()>1 then
		set code=1;
	else
		set code=0;
	end if;
-- 	SELECT status;
end;

-- 新增教师带课申请
CREATE PROCEDURE class_application(
	in $class varchar(32),
	in $teacher varchar(32)
)
BEGIN
	declare open int;
	declare code int;
	select COUNT(*) into open from class_grant where class_id = $class;
	IF open>=1 THEN
		set code=0;
	ELSE
		insert into `class_application`(class_id,teacher_id,status) VALUES ($id,$name,0);
		if ROW_COUNT()>1 then
			set code=1;
		else
			set code=0;
		end if;
	END IF;
-- 	select code;
end;
-- 新增教师带课授权
CREATE PROCEDURE class_grant(
	in $class varchar(32),
	in $teacher varchar(32)
)
BEGIN
	declare open int;
	declare code int;
	select COUNT(*) into open from class_grant where class_id = $class;
	IF open>=1 THEN
		set code=0;
	ELSE
-- 	修改所有带课状态
		UPDATE class_application SET `status`=1 WHERE class_id = $class;
	-- 新增授权
		INSERT INTO class_grant (class_id,teacher_id)VALUES($class, $teacher);
		if ROW_COUNT()>1 then
			set code=1;
		else
			set code=0;
		end if;
	END IF;
-- 	select code;
end;
-- 修改带课申请状态
CREATE PROCEDURE update_class_application(
	in $class varchar(32),
	in $teacher varchar(32),
	in $status TINYINT
)
BEGIN
	declare open int;
	declare code int;
	select COUNT(*) into open from class_grant where class_id = $class;
	IF open>=1 THEN
		set code=0;
	ELSE
-- 	修改所有带课状态
		UPDATE class_application SET `status`=$status WHERE class_id = $class and teacher_id=$teacher;
		if ROW_COUNT()>1 then
			set code=1;
		else
			set code=0;
		end if;
	END IF;
-- 	select code;
end;

-- 按学生id查询实验记录
CREATE PROCEDURE get_student_recard(
	in $student varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM experiment_recard WHERE student_id = $student;
END;
-- 按班级id查询实验记录
CREATE PROCEDURE get_class_recard(
	in $class varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM experiment_recard WHERE class_id = $class GROUP BY student_id;
END;

-- 按班级查询带课申请
CREATE PROCEDURE get_class_application(
	in $class varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM class_application WHERE class_id = $class;
END;
-- 按教师查询带课申请
CREATE PROCEDURE get_teacher_application(
	in $teacher varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM class_application WHERE teacher_id = $teacher;
END;
-- 按班级查询负责老师
CREATE PROCEDURE get_class_grant(
	in $class varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM
		teacher 
	WHERE
		teacher_id IN 
		(
			SELECT teacher_id FROM class_grant WHERE class_id = $class
		);
END;
-- 查询教师带的班级
CREATE PROCEDURE get_teacher_grant(
	in $teacher varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM
		class 
	WHERE
		class_id IN 
		(
			SELECT class_id FROM class_grant WHERE teacher_id = $teacher
		);
END;
-- 查询用户拥有的权限
CREATE PROCEDURE get_user_power(
	in $user_id varchar(32)
)
BEGIN
	SELECT user_type FROM `user` WHERE user_id=$user_id;
END;