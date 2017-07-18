

#include "extractbpi.h"

#define NDEBUG

#undef pr_debug

#ifdef NDEBUG

#define pr_debug(fmt, args...)

#else

#define pr_debug(fmt, args...) fprintf(stderr, fmt, ## args)

#endif


int main(void)
{
	__uint64_t num,sum = 0;
	__uint64_t num_start, num_stop;
	char mac_start[userinputlen] = "\0";
	char mac_stop[userinputlen] = "\0";
	char mac_cur[userinputlen] = "\0";
	char inputcer[filenamelen] = "\0";
	char inputprv[filenamelen] = "\0";
	char outputbat[filenamelen] = "\0";
	//输入MAC范围
	getmac(mac_start, mac_stop);

	//校验MAC范围和源文件数量
	num_start = mactoll(mac_start);
	num_stop = mactoll(mac_stop);
	if(-1 == verify_input(indir_private, num_stop - num_start))
	{
		exit(EXIT_FAILURE);
	}

	
	if(2 != calc_file_num(indir_public))
	{
		printf("Error: Files in %s is more/less than 2 !", indir_public);
		exit(EXIT_FAILURE);
	}
	
	if(-1 == verify_output(outdir))
	{
		exit(EXIT_FAILURE);
	}
	
	system("clear");
	for(num = num_start; num <= num_stop; ++num)
	{
		bzero(mac_cur, sizeof(mac_cur));
		lltomac(num, mac_cur);
		
		sprintf(inputcer, "%s/%s%s",indir_private, mac_cur, suffix_cer);
		sprintf(inputprv, "%s/%s%s",indir_private, mac_cur, suffix_prv);
		sprintf(outputbat, "%s/%s%s",outdir, mac_cur, suffix_bat);
		
		extract(inputcer, inputprv, 
				inputpubcer, inputpubbin, 
				outputbat, num);
		fprintf(stderr, "Complete: %s.bat\n",mac_cur);
		++sum;
	}
	printf("====== %lld files Complete Down! ======\n",sum);

	return 0;
}


//检查输出文件夹是否为空
int verify_output(char *dir)
{
	
	char isgo[userinputlen];
	if (0 != calc_file_num(dir))
	{
		printf("Warning: Out directory is not empty,\
If there is a file have the same name, all of them will be covered!\n\
Are you sure go on?[y/n]");
		
		while(getchar() != '\n');
		scanf("%s",isgo);
		if (0 == strcmp(isgo, "y"))
		{
			return 1;
		}
		else
		{
			printf("Your choice is [%s],Program exits now!\n",isgo);			
			return -1;
		}
	}
	else
	{
		return 1;
	}
	
}
int verify_input(char *dir, __uint64_t num)
{
	__uint64_t file_num = calc_file_num(dir);
	char isgo[userinputlen];
	
		
	if(num+1 > file_num/2)
	{
		printf("Error：The scope of your input MAC is %lld ,but only %lld files already searched,\
Please check your input MAC or files in directory \"files\"!\n",
				num+1, file_num);
		return -1;
	}
	else if(num+1 < file_num/2)
	{
		
		printf("Warning: The scope of your input MAC is %lld ,but %lld files already searched,\
Make sure to extract only your input MAC ?[y/n]",
				num+1, file_num);
		while(getchar() != '\n');
		scanf("%s",isgo);
		if (0 == strcmp(isgo, "y"))
		{
			return 1;
		}
		else
		{
			printf("Your choice is [%s],Program exits now!\n",isgo);			
			return -1;
		}
	}
	else
	{
		return 1;
	}
}

//统计文件夹内的文件数量
__uint64_t calc_file_num(char * dir)
{

	DIR * dir_pointer;

	struct dirent * p_dir;
	dir_pointer = opendir(dir);
	__uint64_t file_num = 0;

	if(NULL == dir_pointer)
	{
		printf("open %s failed,No such file or directory\n", dir);
		exit(EXIT_FAILURE);
	}

	while(NULL != (p_dir = readdir(dir_pointer)))
	{
		//过滤 .. 和 . (p_dir->d_type是4)
		if(8 == p_dir->d_type)
		{
			//printf("%s\n",p_dir->d_name);
			++file_num;
		}
	}

	closedir(dir_pointer);
	return file_num;

}

//让用户输入起止MAC
void getmac(char * mac_start, char * mac_stop)
{

	int isloop = 0;
	__uint64_t num;
	system("clear");
	do
	{
		printf("Please Input Start MAC[00-00-00-00-00-00]:");
		scanf("%s", mac_start);
		num = mactoll(mac_start);
		if(num <= 0 || num >= 0XFFFFFFFFFFFF)
		{
			printf("Input MacAddress Error!\n");
			isloop = 1;
		}
		else
		{
			isloop = 0;
		}
	}
	while(isloop);

	do
	{		
		printf("Please Input Stop MAC[00-00-00-00-00-00]:");		
		scanf("%s", mac_stop);
		num = mactoll(mac_stop);
		if(num <= 0 || num >= 0XFFFFFFFFFFFF)
		{
			printf("Input MacAddress Error!\n");
			isloop = 1;
		}
		else
		{
			isloop = 0;
		}
	}
	while(isloop);

}

//提取文件
void extract(char * file_cer, char * file_prv,
				char * file_pubcer, char * file_pubbin, 
				char * file_bat, __uint64_t macnum)
{
	FILE * read_cer, *read_prv, *read_pubcer, *read_pubbin, *write_bat;
	char a;


	read_cer = fopen(file_cer, "r");
	if(read_cer == NULL)
	{
		printf("open %s failed,No such file or directory\n", file_cer);
		exit(EXIT_FAILURE);
	}

	read_prv = fopen(file_prv, "r");
	if(read_prv == NULL)
	{
		printf("open %s failed,No such file or directory\n", file_prv);
		exit(EXIT_FAILURE);
	}
	
	read_pubcer = fopen(file_pubcer, "r");
	if(read_prv == NULL)
	{
		printf("open %s failed,No such file or directory\n", file_pubcer);
		exit(EXIT_FAILURE);
	}
	
	read_pubbin = fopen(file_pubbin, "r");
	if(read_prv == NULL)
	{
		printf("open %s failed,No such file or directory\n", file_pubbin);
		exit(EXIT_FAILURE);
	}
	
	write_bat = fopen(file_bat, "w");
	if(write_bat == NULL)
	{
		printf("open %s failed,No such file or directory\n", file_bat);
		exit(EXIT_FAILURE);
	}

	/********** enable factory mode **********/
	fprintf(write_bat, "%s\n", echo_enable);
	fprintf(write_bat, "%s\n", cdPvtMibEnableKeyValue);
	fprintf(write_bat, "%s\n", cmFactOperMode);
	fprintf(write_bat, "%s\n", cdPrivateMibEnable);

	/********** Set DOCSIS Private Key **********/
	fprintf(write_bat, "\n%s\n", echo_set);
	fprintf(write_bat, "%s ", cmBpiPlusCmCertificate);
	while(fscanf(read_cer, "%c", &a) != EOF)
	{ //cmBpiPlusCmCertificate
		pr_debug("%02X\n",a);
		fprintf(write_bat, "%02X", a & 0xFF);		//清除高位,保留最低位的一个字节

	}

	fprintf(write_bat, "\n%s ", cmBpiPrivateKey);
	while(fscanf(read_prv, "%c", &a) != EOF)
	{ //cmBpiPrivateKey
		fprintf(write_bat, "%02X", a & 0xFF);

	}

	fprintf(write_bat, "\n%s ", cmBpiPublicKey);
	fseek(read_cer, start_bytes - 1, SEEK_SET);
	pr_debug("[sun]==========%ld\n", ftell(read_cer));
	while(fscanf(read_cer, "%c", &a) != EOF)
	{ //cmBpiPublicKey	
		if(ftell(read_cer) > stop_bytes)
		{
			break;
		}

		fprintf(write_bat, "%02X", a & 0xFF);

	}
	
	fprintf(write_bat, "\n%s ", cmBpiPlusCaCertificate);
	while(fscanf(read_pubcer, "%c", &a) != EOF)
	{ //cmBpiPlusCaCertificate
		fprintf(write_bat, "%02X", a & 0xFF);

	}
	
	fprintf(write_bat, "\n%s ", cmBpiPlusRootPublicKey);
	while(fscanf(read_pubbin, "%c", &a) != EOF)
	{ //cmBpiPlusRootPublicKey
		fprintf(write_bat, "%02X", a & 0xFF);

	}

	fprintf(write_bat, "\n%s %llX", cdMacAddress, macnum);
	fprintf(write_bat, "\n");

	/********** Commit **********/
	fprintf(write_bat, "\n%s\n", echo_Commit);
	fprintf(write_bat, "%s\n", Commit_cmFactOperMode);
	fprintf(write_bat, "%s\n", Commit_cdPrivateMibEnable);
	fprintf(write_bat, "%s", Commit_cdFactCommitSettings);


	fclose(read_cer);
	fclose(read_prv);
	fclose(read_pubcer);
	fclose(read_pubbin);
	fclose(write_bat);
}


