

#ifndef _EXTRACTBPI_H_
#define _EXTRACTBPI_H_
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "mactoll_lltomac.h"

#define echo_enable 			": Enable Factory Mode"
#define echo_set				": Set DOCSIS Private&Public Key"
#define echo_Commit 			": Commit"

#define cdPvtMibEnableKeyValue	"snmpset -v 1 -c private 192.168.100.1 cdPvtMibEnableKeyValue.1 s password"
#define cmFactOperMode			"snmpset -v 1 -c private 192.168.100.1 cmFactOperMode.0 i diagnostic"
#define cdPrivateMibEnable		"snmpset -v 1 -c private 192.168.100.1 cdPrivateMibEnable.0 i factory"

//public key
#define cmBpiPlusCaCertificate	"snmpset -v 1 -c private 192.168.100.1 cmBpiPlusCaCertificate.0 x"
#define cmBpiPlusRootPublicKey	"snmpset -v 1 -c private 192.168.100.1 cmBpiPlusRootPublicKey.0 x"

//private key
#define cmBpiPublicKey			"snmpset -v 1 -c private 192.168.100.1 cmBpiPublicKey.0 x"
#define cmBpiPrivateKey 		"snmpset -v 1 -c private 192.168.100.1 cmBpiPrivateKey.0 x"
#define cmBpiPlusCmCertificate	"snmpset -v 1 -c private 192.168.100.1 cmBpiPlusCmCertificate.0 x"
#define cdMacAddress			"snmpset -v 1 -c private 192.168.100.1 cdMacAddress.1 x"

#define Commit_cmFactOperMode	"snmpset -v 1 -c private 192.168.100.1 cmFactOperMode.0 i docsis"
#define Commit_cdPrivateMibEnable "snmpset -v 1 -c private 192.168.100.1 cdPrivateMibEnable.0 i 0"
#define Commit_cdFactCommitSettings "snmpset -v 1 -c private 192.168.100.1 cdFactCommitSettings.0 i 1"

#define __uint64_t				unsigned long long
#define start_bytes 			412		//文件中的起始偏移字节
#define stop_bytes				551		//文件中的终止偏移字节
#define filenamelen 			80
#define userinputlen			20

//源文件夹名称
char indir_private[filenamelen] = "private"; 
char indir_public[filenamelen] = "public"; 


//目的文件夹名称
char outdir[filenamelen] = "out"; 

//文件后缀名
char suffix_cer[filenamelen] = ".cer";
char suffix_prv[filenamelen] = ".prv";
char suffix_bat[filenamelen] = ".bat";

char inputpubcer[filenamelen]  = "public/euro_mfg_cert.cer";
char inputpubbin[filenamelen] = "public/euro_root_pub_key.bin";


void getmac(char * mac_start, char * mac_stop);
__uint64_t calc_file_num(char * dir);
int verify_input(char * dir, __uint64_t num);
void extract(char * file_cer, char * file_prv,
				char * file_pubcer, char * file_pubbin,
				char * file_bat, __uint64_t macnum);

int verify_output(char * dir);



#endif

