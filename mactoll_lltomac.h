#ifndef __MACTOLL_LLTOMAC_H__
#define __MACTOLL_LLTOMAC_H__

#define __uint64_t unsigned long long

/**********************************************************************
* 函数名称： lltomac
* 功能描述： 将unsigned long long 型的数字转为“-”分割的MAC地址
* 输入参数： 被转换的数字和转换后的字符串
* 输出参数： 无
* 返 回 值： 无
* 注意事项： 形参数组必须清空
**********************************************************************/
void lltomac(__uint64_t num, char * mac);
/**********************************************************************
* 函数名称： mactoll
* 功能描述： 将“-”分割形式的MAC转换为unsigned long long 型的数字
* 输入参数： char 型的mac数组
* 输出参数： 无
* 返 回 值： 转换后的unsigned long long 型的数字
* 注意事项： 无
**********************************************************************/
__uint64_t mactoll(char * input_mac);


#endif
