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
			bool _sendFlag;	// 是发送
			int m_count;
			bool _cureentTimeOut;	// 当前资源是否超时
			Timer *timer;
			TimerCallback<_ResIdStatus> *tc;
			UInt32 _as; // 1失败 0 成功

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
			SubPub,	// 订阅发布
			Manager,// 管理信息
			// 链路配置相关
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
		// 判断是否发送
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
		int m_LinkPriority;	// 优先级
		//NodeBase * m_RemoteAddr;	// 远程发送地址，用于p2p通信
		int delay;	// 待定

		DataSampleElementList * m_dataSampleList;
		TransportSendStrategy * m_sendStrategy;
		Transport * m_pTransport;		// 传输实现
		NodeAddr m_NodeAddr;
		DataControlInfo m_linkInfo;
		UInt32 m_srcNodeId;	// 源节点Id
		UInt32 m_dscNodeId;	// 目标节点Id

		bool m_isAckSend;	// 是否进行发送

		ResourceIdList m_resourceList;	// 未发送资源队列

		ResIdStatus m_currentres;
		bool isAffirm;	// 链路上的数据是否已经确认过了
	};

}

