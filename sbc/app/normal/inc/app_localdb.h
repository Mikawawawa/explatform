#ifndef __LOCALDB_H
#define __LOCALDB_H

#define LOCALDB_ROOT "0:"
#define LOCALDB_LOCAL_PATH 			"0:local"

#define LOCALDB_INFO_PATH 			"0:local/info"
#define LOCALDB_SETTING_PATH 		"0:local/setting"
#define LOCALDB_RECORD_PATH 		"0:local/record"
#define LOCALDB_USER_PATH 			"0:local/user"

#define DB_FILE_INFO 				"0:local/info/info.bin"
#define DB_FILE_SETTING 			"0:local/setting/setting.bin"
#define DB_FILE_RECORD			 	"0:local/record/record.bin"
#define DB_FILE_LOG			 		"0:local/user/log.bin"

typedef struct volume_info {
	unsigned char state;
	unsigned int	degree;
	
}volume_info_struct;

typedef enum machine_type {
	SUBSCRIBE_TYPE,
	NORMAL_TYPE
	
}machine_type_enum;

typedef enum
{
	fs_not_exist,
	fs_crashed,
	fs_new,
	fs_exist
	
}fs_info_enum;


typedef enum
{
	cmd_db_get_subscription,
	cmd_db_student_sign,
	cmd_db_add_stage,
	cmd_db_teacher_sign,
	cmd_db_grade,
	cmd_db_quit,
	cmd_db_umount
	
}db_cmd_enum;


typedef struct machine_info {
	
	char school[20];
	char building[10];
	char floor[10];
	char room[10];
	char id[10];
	char mac[20];
	
}machineInfoTypedef;

typedef struct setting_info {
	volume_info_struct	volume;
	machine_type_enum 	type;
	
}settingInfoTypedef;	

typedef struct experiment_stage{
	
	char 											stage_time[20];
	char 											stage_desc[20];
	struct experiment_stage 	*next;
	
}experiment_stage_struct;

typedef struct experiment_info{
	
	char 														subscribed_time[20];
	char 														subscribed_exp_name[20];
	char 														subscribed_stu_id[10];
	char 														subscribed_stu_name[10];
	unsigned int 										subscribed_exp_quantum[20];
	
	experiment_stage_struct 				stage_root;
	char														exp_end_time[20];
	char 														exp_stu_id[10];
	char 														exp_teacher_id[10];
	unsigned int										exp_quantum;
	unsigned int 										exp_grade;
	
}expInfoTypedef;
	
typedef struct db_info {
	
	int 				(*init)(void);
	char *				(*read)(const char * filename);
	int 				(*write)(const char * filename, const char *wr_buffer);
	
	machineInfoTypedef	machine;
	settingInfoTypedef	setting;
	expInfoTypedef		experiment;
	fs_info_enum		info;
	
	
	
}dbInfoTypedef;

extern dbInfoTypedef local_db;

#endif
