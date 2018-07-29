CREATE TABLE `classroom`  (
  `classroom_id` varchar(32) NOT NULL,
	`class_user` varchar(32) NOT NULL,
	`progress` varchar(32) NOT NULL,
  `column` TINYINT not NULL,
  `row` TINYINT not NULL,
  PRIMARY KEY (`classroom_id`)
);

CREATE TABLE `experiment_grant`  (
  `class_id` varchar(32) NOT NULL,
	`experiment_id` varchar(32) NOT NULL,
  PRIMARY KEY (`class_id`,`experiment_id`),
	FOREIGN KEY(`experiment_id`) REFERENCES experiment(experiment_id),
	FOREIGN KEY(`class_id`) REFERENCES class(class_id)
);

CREATE TABLE `classroom_grant`  (
  `class_id` varchar(32) NOT NULL,
	`classroom_id` varchar(32) NOT NULL,
	`peroid` TINYINT	NOT NULL,
  `semester_id` varchar(32) NOT NULL,
  PRIMARY KEY (`class_id`,`classroom_id`),
	FOREIGN KEY(`class_id`) REFERENCES class(class_id),
	FOREIGN KEY(`classroom_id`) REFERENCES classroom(classroom_id)
);

CREATE TABLE `platform_grant`  (
  `class_id` varchar(32) NOT NULL,
	`mac_address` varchar(32) NOT NULL,
	`column` TINYINT	NOT NULL,
  `row` TINYINT NOT NULL,
  PRIMARY KEY (`class_id`,`mac_address`),
	FOREIGN KEY(`class_id`) REFERENCES class(class_id),
	FOREIGN KEY(`mac_address`) REFERENCES platform(mac_address)
);

CREATE TABLE `class_application`  (
  `class_id` varchar(32) NOT NULL,
	`teacher_id` varchar(32) NOT NULL,
	`status` TINYINT	NOT NULL,
  PRIMARY KEY (`class_id`,`teacher_id`),
	FOREIGN KEY(`class_id`) REFERENCES class(class_id),
	FOREIGN KEY(`teacher_id`) REFERENCES teacher(teacher_id)
);

CREATE TABLE `class_grant`  (
  `class_id` varchar(32) NOT NULL,
	`teacher_id` varchar(32) NOT NULL,
  PRIMARY KEY (`class_id`,`teacher_id`),
	FOREIGN KEY(`class_id`) REFERENCES class(class_id),
	FOREIGN KEY(`teacher_id`) REFERENCES teacher(teacher_id)
);

CREATE TABLE `class_notice`  (
  `class_id` varchar(32) NOT NULL,
	`notice_id` varchar(32) NOT NULL,
  PRIMARY KEY (`class_id`,`notice_id`),
	FOREIGN KEY(`class_id`) REFERENCES class(class_id),
	FOREIGN KEY(`notice_id`) REFERENCES notice(notice_id)
);


CREATE TABLE `class_join`  (
  `class_id` varchar(32) NOT NULL,
	`student_id` varchar(32) NOT NULL,
  PRIMARY KEY (`class_id`,`student_id`),
	FOREIGN KEY(`class_id`) REFERENCES class(class_id),
	FOREIGN KEY(`student_id`) REFERENCES student(student_id)
);
