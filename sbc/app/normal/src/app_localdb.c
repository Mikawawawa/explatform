#include "ep_app.h"

static int db_init(void);
static char * db_read(const char * filename);
static int db_write(const char * filename, const char *wr_buffer);


dbInfoTypedef local_db = {
	db_init,
	db_read,
	db_write
};

static FATFS dbfs;
char *FL = NULL;

static int db_init()
{
	static FRESULT result;
	FIL f;
	
	result = f_mount(&dbfs, LOCALDB_ROOT, 1);
	/* 未检测到文件系统时，执行格式化 */
	if (FR_NO_FILESYSTEM == result)	{
		
		f_mkfs(LOCALDB_ROOT, 0, 0);
		f_mount(NULL, LOCALDB_ROOT, 0);
		result = f_mount(&dbfs, LOCALDB_ROOT, 1);
		if (FR_OK != result) {
			local_db.info = fs_not_exist;
			return 0;
		}
		
		f_mkdir(LOCALDB_LOCAL_PATH);
		f_mkdir(LOCALDB_INFO_PATH);
		f_mkdir(LOCALDB_SETTING_PATH);
		f_mkdir(LOCALDB_RECORD_PATH);
		f_mkdir(LOCALDB_USER_PATH);
	}
	
	else if(FR_OK == result)
		local_db.info = fs_exist;
	
	else {
		local_db.info = fs_not_exist;
		f_mount(&dbfs,LOCALDB_ROOT,NULL);
		return 0;
	}
		
	/*尝试创建info.bin文件*/
	result = f_open(&f, DB_FILE_INFO, FA_CREATE_NEW | FA_READ);
	if(FR_OK == result) {
		local_db.info = fs_new;
		f_close(&f);
	}
	else if(FR_EXIST == result) {
		f_close(&f);
		local_db.info = fs_exist;
	}
	else {
		local_db.info = fs_crashed;
		f_mount(&dbfs,LOCALDB_ROOT,NULL);
		return 0;
	}
	
	/*尝试创建setting.bin文件*/
	result = f_open(&f, DB_FILE_SETTING, FA_CREATE_NEW | FA_READ);
	if(FR_OK == result) {
		local_db.info = fs_new;
		f_close(&f);
	}
	else if(FR_EXIST == result) {
		f_close(&f);
		local_db.info = fs_exist;
	}
	else {
		local_db.info = fs_crashed;
		f_mount(&dbfs,LOCALDB_ROOT,NULL);
		return 0;
	}
	
	/*尝试创建record.bin文件*/
	result = f_open(&f, DB_FILE_RECORD, FA_CREATE_NEW | FA_READ);
	if(FR_OK == result) {
		local_db.info = fs_new;
		f_close(&f);
	}
	else if(FR_EXIST == result) {
		f_close(&f);
		local_db.info = fs_exist;
	}
	else {
		local_db.info = fs_crashed;
		f_mount(&dbfs,LOCALDB_ROOT,NULL);
		return 0;
	}
	
	/*尝试创建log.bin文件*/
	result = f_open(&f, DB_FILE_LOG, FA_CREATE_NEW | FA_READ);
	if(FR_OK == result) {
		local_db.info = fs_new;
		f_close(&f);
	}
	else if(FR_EXIST == result) {
		f_close(&f);
		local_db.info = fs_exist;
	}
	else {
		local_db.info = fs_crashed;
		f_mount(&dbfs,LOCALDB_ROOT,NULL);
		return 0;
	}
	
	f_mount(&dbfs,LOCALDB_ROOT,NULL);
	
	return 1;

}

static char * db_read(const char * filename) {
	FIL f;
	FRESULT result;
	UINT br;
	char *file_contents;
	
	result = f_open(&f, filename, FA_OPEN_ALWAYS | FA_READ);
	
	if (result != FR_OK) {
		return NULL;
	}
	
	f_rewind(&f);
	file_contents = (char*)calloc(sizeof(char), (f.fsize + 1));
	if (!file_contents) {
		f_close(&f);
		return NULL;
	}
	if (f_read(&f, file_contents, f.fsize, &br) < 1) {
		if (f_error(&f)) {
			f_close(&f);
			free(file_contents);
			return NULL;
		}
	}
	
	f_close(&f);
	file_contents[f.fsize] = '\0';
	return file_contents;
	
}


static int db_write(const char * filename, const char *wr_buffer)
{
	return 0;
}


