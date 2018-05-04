
#ifndef _ERRORINFO_H_ 
#define _ERRORINFO_H_

namespace NetCom
{
#define ERROR_OK				1<<1 // 正常
#define ERROR_MALLOC			1<<2 // 分配内存失败
#define ERROR_EXCEPT			1<<3 // 错误异常
#define ERROR_MODEL_NULL		1<<4 // 错误异常
#define ERROR_NOT_FIND			1<<5 // 没有找到
#define ERROR_FAILE_CONVERT		1<<6 // 类型转换失败
#define ERRROR_MESSAGE_NOHANLD  1<<7 // 消息没有响应
#define ERRROR_NOT_TYPE			1<<8 // 类型不一致
#define ERRROR_HAVEED			1<<9 // 类型不一致
#define ERRROR_OPENFAILD		1<<10 // 打开失败
#define ERROR_ITEM_LOADED		1<<11 // 当前项已经存在
}
#endif