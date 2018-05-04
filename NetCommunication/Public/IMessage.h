/************************************************************************/
/* 作者： LJ                                                            */
/* 用途:  消息接口				                                        */
/* 时间： 2015-08-27                                                    */
/* 修改时间:                                                            */
/************************************************************************/
#ifndef _PUBLIC_IMESSAGE_H_
#define _PUBLIC_IMESSAGE_H_

namespace VR_Soft
{
	class VRSOFT_DLL IMessage
	{
	public:
		
		//************************************
		// Method:    ~IMessage
		/// 析构函数
		// FullName:  VR_Soft::IMessage::~IMessage
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~IMessage() { };
		
		//************************************
		// Method:    GetSender
		/// 获得发送者
		// FullName:  VR_Soft::IMessage::GetSender
		// Access:    virtual public 
		// Returns:   VR_Soft::IEntityBase*
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual IEntityBase* GetSender(void) const = 0;
		
		//************************************
		// Method:    SetSender
		/// 设置发送者
		// FullName:  VR_Soft::IMessage::SetSender
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const uint64_t uID 发送者ID标识
		//************************************
		virtual void SetSender(const uint64_t uID) = 0;
		
		//************************************
		// Method:    GetReceiver
		/// 获得接受者
		// FullName:  VR_Soft::IMessage::GetReceiver
		// Access:    virtual public 
		// Returns:   VR_Soft::IEntityBase*
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual IEntityBase* GetReceiver(void) const  = 0;
		
		//************************************
		// Method:    SetReceiver
		/// 设置接收者
		// FullName:  VR_Soft::IMessage::SetReceiver
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const uint64_t uID 接收者ID标识
		//************************************
		virtual void SetReceiver(const uint64_t uID)  = 0;
		
		//************************************
		// Method:    SetMessage
		/// 设置消息
		// FullName:  VR_Soft::IMessage::SetMessage
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: UINT uMsg 设置消息ID
		//************************************
		virtual void SetMessage(UINT uMsg) = 0;
		
		//************************************
		// Method:    GetMessage
		/// 获得消息
		// FullName:  VR_Soft::IMessage::GetMessage
		// Access:    virtual public 
		// Returns:   UINT
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual UINT GetMessage(void) const = 0;
		
		//************************************
		// Method:    SetDispatch
		/// 设置处理时间
		// FullName:  VR_Soft::IMessage::SetDispatch
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const double dDispatchTime 处理的时间
		//************************************
		virtual void SetDispatch(const double dDispatchTime) = 0;
		
		//************************************
		// Method:    GetDispatch
		/// 获得处理时间
		// FullName:  VR_Soft::IMessage::GetDispatch
		// Access:    virtual public 
		// Returns:   double
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual double GetDispatch(void) const = 0;
		
		//************************************
		// Method:    SetExpendInfo
		/// 设置扩展消息
		// FullName:  VR_Soft::IMessage::SetExpendInfo
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void * pExInfo 
		//************************************
		virtual void SetExpendInfo(void* pExInfo) = 0;
		
		//************************************
		// Method:    GetExpendInfo
		/// 获得扩展消息
		// FullName:  VR_Soft::IMessage::GetExpendInfo
		// Access:    virtual public 
		// Returns:   void*
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual void* GetExpendInfo(void) const = 0;
	};
}

#endif // _PUBLIC_IMESSAGE_H_