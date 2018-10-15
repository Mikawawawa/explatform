CREATE TABLE `user`(
	`user_id` VARCHAR(32) NOT NULL,
	`user_type`TINYINT not NULL,
	`password` VARCHAR(32) not NULL,
	PRIMARY KEY (`user_id`,`user_type`)
	);
CREATE TABLE `subject`(
	`subject_id` VARCHAR(32) NOT NULL,
	`subject_name` VARCHAR(32) NOT NULL,
	 PRIMARY KEY (`subject_id`)
	 );
CREATE TABLE `teacher`(
	`teacher_id` VARCHAR(32) NOT NULL,
	`teacher_name` VARCHAR(32) NOT NULL,
	 PRIMARY KEY (`teacher_id`)
	 );
CREATE TABLE `student`(
	`student_id` VARCHAR(32) NOT NULL,
	`student_name` VARCHAR(32) NOT NULL,
	 PRIMARY KEY (`student_id`)
	 );

CREATE TABLE `template`  (
	`template_id` varchar(32) NOT NULL,
	`operation` json not NULL,
	`section` json not NULL,
	`choice` json not NULL,
	PRIMARY KEY (`template_id`)
);

CREATE TABLE `platform`(
	`mac_address` varchar(32) NOT NULL,
	`status` TINYINT NOT NULL DEFAULT 0,
	PRIMARY KEY (`mac_address`)
);

CREATE TABLE `peroid`(
	`peroid_id` tinyint not null,
	`defination` varchar(64) not null,
	PRIMARY KEY (`peroid_id`)
);

CREATE TABLE `semester` (
	`semester_id` varchar(32) not null,
	`semester_peroid` int not null,
	`semester_stage` bit not null,
	PRIMARY KEY (`semester_id`)
);

CREATE TABLE `logs` (
	`log_id`  tinyint not null ,
	`log`  varchar(255) not null
)
;
