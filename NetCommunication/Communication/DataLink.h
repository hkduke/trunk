#pragma once
#include "../Core/Export.h"
#include "DataSampleElementList.h"

#include "../Reactor/SocketReactor.h"
#include <string.h>
#include "NodeAddr.h"
#include "../Core/Timer.h"

namespace NetCom
{
	class NodeBase;
	class TransportSendStrategy;
	class Transport;
	
	class NETCOMMUNICATION_EXPORT DataLink  
	{
	public:

		typedef std::vector<UInt32> ResourceIdList;


		typedef struct _ResIdStatus
		{
			UInt32 _ResId;
			bool _sendFlag;	// �Ƿ���
			int m_count;
			bool _cureentTimeOut;	// ��ǰ��Դ�Ƿ�ʱ
			Timer *timer;
			TimerCallback<_ResIdStatus> *tc;
			UInt32 _as; // 1ʧ�� 0 �ɹ�

			void SetAckStatus(UInt32 ts)
			{
				_as = ts;
			}
			void SetResIdTimeOut(Timer& timer)
			{
				_cureentTimeOut = true;
			}
			void SetResIdTimeOut(bool isTimeout)
			{
				_cureentTimeOut = isTimeout;
			}

			_ResIdStatus()
			{
				timer = new NetCom::Timer(100,100);
				tc = new TimerCallback<_ResIdStatus>(*this, &_ResIdStatus::SetResIdTimeOut);
				_ResId = -1;
				_sendFlag = true;
				_cureentTimeOut = false;
				//StartResCount();
				timer->start(*tc);
			}
			UInt32 GetResId()
			{
				return _ResId;
			}

			inline bool GetResIdTimeOut()
			{
				return _cureentTimeOut;
			}

			bool GetResSendFlag()
			{
				return _sendFlag;
			}
			void SetIsNeedResSend(bool b)
			{
				_sendFlag = b;
			}
			void SetResId(UInt32 id)
			{
				_ResId = id;
			}
			void StartResCount()
			{
				timer->restart();
				//timer->start(*tc);
			}
		}ResIdStatus;

		enum DataControlInfo
		{
			None,	
			SubPub,	// ���ķ���
			Manager,// ������Ϣ
			// ��·�������
		};


		typedef struct _QosStrategy
		{
			UInt64 m_time;
			virtual bool IsTransport()
			{
			}


		}QosStrategy;


		DataLink();
		~DataLink();

		virtual void SetStart();
		virtual void Send(DataSampleElementList* element, bool relink = false);
		virtual void Send(DataSampleElement* element, bool relink = false);
		virtual void SetSendStrategy(TransportSendStrategy * strategy);
		virtual void SetDataSampleElementList(DataSampleElementList* ptr);
		virtual void SetTransport(Transport * ptr);
		void	SetDataControlInfo(DataControlInfo info);
		DataControlInfo GetDataControlInfo();
		inline UInt32 GetdscNodeId()
		{
			return m_dscNodeId;
		}

		void SetDscNodeId(UInt32 id);
		// �ж��Ƿ���
		virtual bool DecideTransport();
		void SetAckSendFlag(bool isSend);

		ResourceIdList & GetResourceIdList()
		{
			return m_resourceList;
		}
		inline bool GetIsAckSendFlag()
		{
			return m_isAckSend;
		}
		inline ResIdStatus &GetCurrentResource()
		{
			return m_currentres;
		}
		inline void SetResIdStatus(ResIdStatus rs)
		{
			m_currentres = rs;
		}
		inline void SetAffirm(bool b)
		{
			isAffirm = b;
		}
		inline bool GetAffirm()
		{
			return isAffirm;
		}
		virtual void Bind();
		int m_LinkPriority;	// ���ȼ�
		//NodeBase * m_RemoteAddr;	// Զ�̷��͵�ַ������p2pͨ��
		int delay;	// ����

		DataSampleElementList * m_dataSampleList;
		TransportSendStrategy * m_sendStrategy;
		Transport * m_pTransport;		// ����ʵ��
		NodeAddr m_NodeAddr;
		DataControlInfo m_linkInfo;
		UInt32 m_srcNodeId;	// Դ�ڵ�Id
		UInt32 m_dscNodeId;	// Ŀ��ڵ�Id

		bool m_isAckSend;	// �Ƿ���з���

		ResourceIdList m_resourceList;	// δ������Դ����

		ResIdStatus m_currentres;
		bool isAffirm;	// ��·�ϵ������Ƿ��Ѿ�ȷ�Ϲ���
	};

}

