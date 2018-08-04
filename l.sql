-- 新建班级公告信息
CREATE PROCEDURE class_notice(
    in $class varchar(32),
    in $notice varchar(32)
)
BEGIN
    declare code int;
    insert into `class_notice`(class_id , notice_id) value ($class , $notice);
    if ROW_COUNT() > 1 then 
        set code = 0;
    else 
        set code = 1;
    end if;
--  select code;
END 

-- 新增学生加入班级
CREATE PROCEDURE class_join(
    in $class varchar(32),
    in $student varchar(32)
)
BEGIN 
    declare open int;
    declare code int;
    select COUNT(*) into open from class_join where student_id = $student;
    if open >= 1 then 
        set code = 0;
    else 
        insert into `class_join`(class_id , student_id) value ($class , $student);
        if ROW_COUNT() > 1 then
            set code = 1;
        else 
            set code = 0;
        end if;
    end if;
--  select code;
END

-- 修改实验记录里的选择题
CREATE PROCEDURE update_experiment_choice(
    in $student varchar(32),
    in $experiment varchar(32),
    in $choice json
)
BEGIN
    declare code int;
    update experiment_recard set `choice` = $choice where `student_id` = $student and `experiment_id` = $experiment;
    if ROW_COUNT() > 1 then
        set code = 1;
    else 
        set code = 0;
    end if;
--  select code;
END

-- 修改实验记录里的操作题
CREATE PROCEDURE update_experiment_operation(
    in $student varchar(32),
    in $experiment varchar(32),
    in $operation json
)
BEGIN
    declare code int;
    update experiment_recard set `operation` = $choice where `student_id` = $student and `experiment_id` = $experiment;
    if ROW_COUNT() > 1 then
        set code = 1;
    else 
        set code = 0;
    end if;
--  select code;
END

-- 修改实验记录里的栏目内容
CREATE PROCEDURE update_experiment_recard(
    in $student varchar(32),
    in $experiment varchar(32),
    in $subject varchar(32),
	in $grade TINYINT,
	in $present datetime,
	in $operation json,
    in $section json,
    in $choice json
)
BEGIN
    declare code int;
    update experiment_recard set `subject_id` = $subject , `garde` = $grade , `present` = $present , `operation` = $operation , `choice` = $choice , `section` = $section  where `student_id` = $student and `experiment_id` = $experiment;
    if ROW_COUNT() > 1 then
        set code = 1;
    else 
        set code = 0;
    end if;
--  select code;
END

