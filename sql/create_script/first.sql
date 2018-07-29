CREATE TABLE `template_grant`(
	`subject_id` varchar(32),
	`template_id` varchar(32),
	PRIMARY KEY(`subject_id`,`template_id`),
	FOREIGN KEY(`subject_id`) REFERENCES subject(subject_id),
	FOREIGN KEY (`template_id`) REFERENCES template(template_id)
);

CREATE TABLE `experiment`(
	`experiment_id` varchar(32),
	`template_id` varchar(32),
	PRIMARY KEY(`experiment_id`,`template_id`),
	FOREIGN KEY(`template_id`) REFERENCES template(template_id)
);

CREATE TABLE `notice`(
	`notice_id` VARCHAR(32) NOT NULL,
	`user_id` VARCHAR(32) NOT NULL,
	`notice_content` text NOT NULL,
	`notice_time` datetime not null,
	PRIMARY KEY (`notice_id`),
	FOREIGN KEY(`user_id`) REFERENCES user(user_id)
);