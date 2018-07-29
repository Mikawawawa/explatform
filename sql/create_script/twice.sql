CREATE TABLE `experiment_recard`(
	`student_id` varchar(32),
	`experiment_id` varchar(32),
	`subject_id` varchar(32),
	`grade` TINYINT DEFAULT 0,
	`present` datetime,
	`operation` json not NULL,
    `section` json not NULL,
    `choice` json not NULL,
	PRIMARY KEY(`student_id`,`experiment_id`),
	FOREIGN KEY(`student_id`) REFERENCES student(student_id),
	FOREIGN KEY(`experiment_id`) REFERENCES experiment(experiment_id),
	FOREIGN KEY(`subject_id`) REFERENCES subject(subject_id)
);

CREATE TABLE`class`(
	`class_id` VARCHAR(32) not NULL,
	`subject_id` VARCHAR(32) not NULL,
	`semester_id`VARCHAR(32) not NULL,
	`process` VARCHAR(32) not NULL,
	PRIMARY KEY (`class_id`),
	FOREIGN KEY(`subject_id`) REFERENCES subject(subject_id),
	FOREIGN KEY(`semester_id`) REFERENCES semester(semester_id),
	FOREIGN KEY(`process`) REFERENCES experiment(experiment_id)
);