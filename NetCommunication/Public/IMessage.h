/************************************************************************/
/* ���ߣ� LJ                                                            */
/* ��;:  ��Ϣ�ӿ�				                                        */
/* ʱ�䣺 2015-08-27                                                    */
/* �޸�ʱ��:                                                            */
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
		/// ��������
		// FullName:  VR_Soft::IMessage::~IMessage
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~IMessage() { };
		
		//************************************
		// Method:    GetSender
		/// ��÷�����
		// FullName:  VR_Soft::IMessage::GetSender
		// Access:    virtual public 
		// Returns:   VR_Soft::IEntityBase*
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual IEntityBase* GetSender(void) const = 0;
		
		//************************************
		// Method:    SetSender
		/// ���÷�����
		// FullName:  VR_Soft::IMessage::SetSender
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const uint64_t uID ������ID��ʶ
		//************************************
		virtual void SetSender(const uint64_t uID) = 0;
		
		//************************************
		// Method:    GetReceiver
		/// ��ý�����
		// FullName:  VR_Soft::IMessage::GetReceiver
		// Access:    virtual public 
		// Returns:   VR_Soft::IEntityBase*
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual IEntityBase* GetReceiver(void) const  = 0;
		
		//************************************
		// Method:    SetReceiver
		/// ���ý�����
		// FullName:  VR_Soft::IMessage::SetReceiver
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const uint64_t uID ������ID��ʶ
		//************************************
		virtual void SetReceiver(const uint64_t uID)  = 0;
		
		//************************************
		// Method:    SetMessage
		/// ������Ϣ
		// FullName:  VR_Soft::IMessage::SetMessage
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: UINT uMsg ������ϢID
		//************************************
		virtual void SetMessage(UINT uMsg) = 0;
		
		//************************************
		// Method:    GetMessage
		/// �����Ϣ
		// FullName:  VR_Soft::IMessage::GetMessage
		// Access:    virtual public 
		// Returns:   UINT
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual UINT GetMessage(void) const = 0;
		
		//************************************
		// Method:    SetDispatch
		/// ���ô���ʱ��
		// FullName:  VR_Soft::IMessage::SetDispatch
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: const double dDispatchTime �����ʱ��
		//************************************
		virtual void SetDispatch(const double dDispatchTime) = 0;
		
		//************************************
		// Method:    GetDispatch
		/// ��ô���ʱ��
		// FullName:  VR_Soft::IMessage::GetDispatch
		// Access:    virtual public 
		// Returns:   double
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual double GetDispatch(void) const = 0;
		
		//************************************
		// Method:    SetExpendInfo
		/// ������չ��Ϣ
		// FullName:  VR_Soft::IMessage::SetExpendInfo
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void * pExInfo 
		//************************************
		virtual void SetExpendInfo(void* pExInfo) = 0;
		
		//************************************
		// Method:    GetExpendInfo
		/// �����չ��Ϣ
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