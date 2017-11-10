#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "mactoll_lltomac.h"

void lltomac(__uint64_t num, char * mac)
{
	__uint64_t *pnum = &num;
	int i, macAddress[6];
	char * cpoint;
	cpoint = (char *)pnum;
	for(i = 0; i < 6; ++i)
	{ //Little-Endian
		sprintf((char *)(& (macAddress[5 - i])), "%c", cpoint[i]);
	}

	//清除高位（3个字节），保留低位（1个字节），并按16进制“-”分割的形式输出到mac字符串数组中	
	sprintf(mac, "%02X-%02X-%02X-%02X-%02X-%02X", 
		macAddress[0] &0xFF, macAddress[1] &0xFF, macAddress[2] &0xFF, 
		macAddress[3] &0xFF, macAddress[4] &0xFF, macAddress[5] &0xFF);
}


__uint64_t mactoll(char * input_mac)
{
	__uint64_t num;
	int macAddress[6];
	int numScanned;
	char mac[20] = "\0";

	if(17 != strlen(input_mac))
	{
		return - 1;
	}
	strncpy(mac, input_mac,17);
	//过滤MAC分隔符
	numScanned = sscanf(mac, "%2X%*[:.-]%2X%*[:.-]%2X%*[:.-]%2X%*[:.-]%2X%*[:.-]%2X", 
		& (macAddress[0]), & (macAddress[1]), & (macAddress[2]), 
		& (macAddress[3]), & (macAddress[4]), & (macAddress[5]));
	if(numScanned != 6)
	{
		return - 1;
	}

	sprintf(mac, "%02X%02X%02X%02X%02X%02X", 
		macAddress[0], macAddress[1], macAddress[2], 
		macAddress[3], macAddress[4], macAddress[5]);
	num = strtoull(mac, NULL, 16);
	if(num == errno)
	{
		perror("strtoll");
		return - 1;
	}
	return num;
}

