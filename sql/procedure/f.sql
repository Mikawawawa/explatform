-- 新增实验
CREATE PROCEDURE create_experiment(
	in $id varchar(32),
	in $name varchar(32)
)
BEGIN
	DECLARE code TINYINT;
	insert into `experiment`(experiment_id,template_id) VALUES ($id,$name);
	if ROW_COUNT()>1 then
		set code=1;
	else
		set code=0;
	end if;
-- 	SELECT status;
end;
-- 新增实验桌
CREATE PROCEDURE create_platform(
	in $mac_address varchar(32),
	in $status varchar(32)
)
BEGIN
	DECLARE code TINYINT;
	insert into `platform`(mac_address,status) VALUES ($mac_address,$status);
	if ROW_COUNT()>1 then
		set code=1;
	else
		set code=0;
	end if;
-- 	SELECT status;
end;
-- 新增教室
CREATE PROCEDURE create_classroom(
	in $classroom_id varchar(32),
	in $class_id varchar(32),
	in $progress varchar(32)
)
BEGIN
	DECLARE code TINYINT;
	insert into `classroom`(classroom_id,class_id,progress) VALUES ($classroom_id,$class_id,$progress);
	if ROW_COUNT()>1 then
		set code=1;
	else
		set code=0;
	end if;
-- 	SELECT status;
end;

-- 新增班级占用教室
CREATE PROCEDURE classroom_grant(
	in $class_id varchar(32),
	in $classroom_id varchar(32),
	in $peroid varchar(32),
	in $semester_id TINYINT
)
BEGIN
	declare open int;
	declare code int;
	select COUNT(*) into open from classroom_grant where class_id = $class_id;
	IF open>=1 THEN
		set code=0;
	ELSE
		insert into `class_grant`(class_id,classroom_id,peroid,semester_id) VALUES ($class_id,$classroom_id,$peroid,$semester_id);
		if ROW_COUNT()>1 then
			set code=1;
		else
			set code=0;
		end if;
	END IF;
-- 	select code;
end;
-- 新增教室内试验台
CREATE PROCEDURE platform_grant(
    in $class_id varchar(32),
    in $mac_address varchar(32),
	in $column TINYINT,
	in $row TINYINT
)
BEGIN 
    declare open int;
    declare code int;
    select COUNT(*) into open from platform where mac_address = $mac_address;
    if open >= 1 then 
        set code = 0;
    else 
        insert into `platform_grant`(class_id,mac_address) value ($class_id,$mac_address);
        if ROW_COUNT() > 1 then
            set code = 1;
        else 
            set code = 0;
        end if;
    end if;
--  select code;
end;

-- 修改用户的密码
CREATE PROCEDURE update_user_password(
    in $id varchar(32),
    in $type TINYINT,
    in $password varchar(32)
)
BEGIN
    declare code int;
    update user set `password` = $password where `user_id` = $id and `user_type` = $type;
    if ROW_COUNT() > 1 then
        set code = 1;
    else 
        set code = 0;
    end if;
--  select code;
END;
-- 修改试验台状态
CREATE PROCEDURE update_platform_status(
    in $mac_address varchar(32),
    in $status varchar(32)
)
BEGIN
    declare code int;
    update platform set `status` = $status where `mac_address` = $mac_address;
    if ROW_COUNT() > 1 then
        set code = 1;
    else 
        set code = 0;
    end if;
--  select code;
END;
-- 修改教室占用状态及进度
CREATE PROCEDURE update_classroom(
    in $classroom_id varchar(32),
    in $class_id varchar(32),
    in $progress varchar(32)
)
BEGIN
    declare code int;
    update classroom set `class_id` = $class_id and `progress` = $progress where `classroom_id` = $classroom_id;
    if ROW_COUNT() > 1 then
        set code = 1;
    else 
        set code = 0;
    end if;
--  select code;
END;

-- 按学科查询实验并按班级group by
CREATE PROCEDURE get_experiment_recard(
	in $subject varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM experiment_recard WHERE `subject` = $subject GROUP BY `class_id`;
END;
-- 根据班级查询公告信息
CREATE PROCEDURE get_notice(
	in $class_id varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM notice WHERE `class_id` = $class_id;
END;
-- 根据学期查询班级，并按学科group by
CREATE PROCEDURE get_class(
	in $semester varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM class WHERE `semester_id` = $semester GROUP BY `subject_id`;
END;
-- 按班级查询实验
CREATE PROCEDURE get_experiment(
	in $class_id varchar(32)
)
BEGIN
	declare code int;
	SELECT * FROM experiment WHERE `class_id` = $class_id;
END;