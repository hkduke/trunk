
#ifndef _ERRORINFO_H_ 
#define _ERRORINFO_H_

namespace NetCom
{
#define ERROR_OK				1<<1 // ����
#define ERROR_MALLOC			1<<2 // �����ڴ�ʧ��
#define ERROR_EXCEPT			1<<3 // �����쳣
#define ERROR_MODEL_NULL		1<<4 // �����쳣
#define ERROR_NOT_FIND			1<<5 // û���ҵ�
#define ERROR_FAILE_CONVERT		1<<6 // ����ת��ʧ��
#define ERRROR_MESSAGE_NOHANLD  1<<7 // ��Ϣû����Ӧ
#define ERRROR_NOT_TYPE			1<<8 // ���Ͳ�һ��
#define ERRROR_HAVEED			1<<9 // ���Ͳ�һ��
#define ERRROR_OPENFAILD		1<<10 // ��ʧ��
#define ERROR_ITEM_LOADED		1<<11 // ��ǰ���Ѿ�����
}
#endif