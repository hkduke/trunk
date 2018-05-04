#pragma once
#include "CoreCommon.h"
#include "../Core/Types.h"
#include "../Core/Any.h"
#include <iostream>
#include <vector>
#include "../Core/Export.h"
#define MAXPACKAGESIZE 1024//�����ļ����ְ����ֵ
//�ļ�ͷ���֣��ܹ�11��
//ǰ�������ֶθ�ʽ�̶�
const int DATALENTHSIZEPOSE = 1;
const int  DATALENTHSIZE = 2;//�����򳤶ȴ�С,λ��1

const int TOPICSIZE = 2;//�����С,λ��3
const int  TOPICSIZEPOSE = (DATALENTHSIZEPOSE + DATALENTHSIZE);

const int  SOURCEIDSIZE = 1;//Դ��ַ��С��λ��5
const int  SOURCEIDSIZEPOSE = (TOPICSIZEPOSE + TOPICSIZE);//Դ��ַ��С

const int TARGETIDSIZE = 1;//Ŀ���ַ��С ,λ��6
const int TARGETIDSIZEPOSE = (SOURCEIDSIZEPOSE + SOURCEIDSIZE);//Ŀ���ַ��С 


const int  DATAGENERALTIMESIZE = 4;//���ݲ���ʱ��,λ��7
const int  DATAGENERALTIMESIZEPOSE = (TARGETIDSIZEPOSE + TARGETIDSIZE);

const int STANDAREDHEADSIZE = (DATAGENERALTIMESIZEPOSE + DATAGENERALTIMESIZE);//֡ͷ��С,��11

const int   FRAMTAILCHECKSIZE= 2;//βУ���
//����������

const int FILETOPICIDSIZE = 3; //�ļ�����Ŵ�С,λ��11
const int FILETOPICIDPOSE = STANDAREDHEADSIZE;

const int  FILECHECKLENTHSIZE = 1; //�ļ�֤�볤��,λ��14
const int  FILECHECKLENTHPOSE = (FILETOPICIDPOSE + FILETOPICIDSIZE);
const int FILECHECKPOSE = (FILECHECKLENTHPOSE + FILECHECKLENTHSIZE);
const int FILENAMLENTHSIZE = 1; // �ļ�����С��λ��
const int  FILECHECKSIZE = 1;//������У���

const int NODEJOINNETTYPE=1;

namespace NetCom
{

	namespace  ToolClass
	{

		NETCOMMUNICATION_EXPORT UInt8  GenerateUint32UUID();

		//��ȡ֡����
		NETCOMMUNICATION_EXPORT int  GetPackFramType(void* buff);
		//��ȡ����־
		NETCOMMUNICATION_EXPORT int  GetPackFlag(void* buff);
		//��ȡ���ȼ�
		NETCOMMUNICATION_EXPORT int  GetPackProperity(void* buff);
		//��ȡ��������
		NETCOMMUNICATION_EXPORT UINT16  GetPacketType(void* buff);
		//��ȡ���ݰ���С
		NETCOMMUNICATION_EXPORT unsigned int GetPacketSize(void* buff);
		//��ȡ���ݲ���ʱ��
		NETCOMMUNICATION_EXPORT UInt64 GetPackGeneralTime(void* buff);
		//��ȡ������ϢԴ�豸��ʶ
		NETCOMMUNICATION_EXPORT UInt32 GetSourceDevID(void* buff);
		//��ȡ�����豸Ŀ���豸��Ϣ
		NETCOMMUNICATION_EXPORT UInt32 GetSourceTargetID(void* buff);
		//��ȡȷ�ϱ�־
		NETCOMMUNICATION_EXPORT UInt16 GetAnsoweFlag(void* buff);
		//��ȡ������
		NETCOMMUNICATION_EXPORT UInt16 GetReserveC(void* buff);

		//��ӡ�ļ�ͷ
		NETCOMMUNICATION_EXPORT void PrintMessageHeader(void* buff);

		//����֡����
		NETCOMMUNICATION_EXPORT void  SetPackFramType(void* buff, int framType);
		//���ð���־
		NETCOMMUNICATION_EXPORT void  SetPackFlag(void* buff, int packFlag);
		//�������ȼ�
		NETCOMMUNICATION_EXPORT void  SetPackProperity(void* buff, int properity);
		//���ñ�������
		NETCOMMUNICATION_EXPORT void  SetPacketType(void* buff, EPackType packType);
		//�������ݰ���С
		NETCOMMUNICATION_EXPORT void  SetPacketSize(void* buff, int packSize);
		//�������ݲ���ʱ��
		NETCOMMUNICATION_EXPORT void  SetPackGeneralTime(void* buff, UInt64 generalTime);
		//����������ϢԴ�豸��ʶ
		NETCOMMUNICATION_EXPORT void  SetSourceDevID(void* buff, UInt32 sourceID);
		//���������豸Ŀ���豸��Ϣ
		NETCOMMUNICATION_EXPORT void  SetSourceTargetID(void* buff, UInt32 targetID);
		//����ȷ�ϱ�־
		NETCOMMUNICATION_EXPORT void  SetAnsoweFlag(void* buff, UInt16 ansowFlag);
		//���ñ�����
		NETCOMMUNICATION_EXPORT void  SetReserveC(void* buff, UInt16 reserver);
		//��ȡ��ͷ�Ĵ�С
		NETCOMMUNICATION_EXPORT int GetHeaderSize();
		//��ȡ����IP�ַ�
		NETCOMMUNICATION_EXPORT std::string TransAddressToStr(unsigned int address);

		//У��ͺ���
		
		//��ȡ�̶�λ�ñ���
		template<typename T>
		T GetFixData(void* buff, int begin)
		{
			std::vector<BYTE> vects;
			int size = sizeof(T);
			for (int i = begin; i < begin + size; i++)
			{
				vects.push_back(((BYTE*)buff)[i]);
			}
			return *(T*)vects.data();
		}
		//���ù̶�λ�ñ���
		template<typename T>
		void  SetFixData(void* buff, int begin, T var)
		{
			memcpy((char*)buff + begin, &var, sizeof(var));
		}
	}
}