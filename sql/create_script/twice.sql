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
