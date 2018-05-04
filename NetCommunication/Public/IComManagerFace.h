#ifndef _ICOMMANAGERFACE_H_
#define _ICOMMANAGERFACE_H_

#pragma once

#include "IComManagerFaceImp.h"

namespace VR_Soft
{
	class  IComManagerFace //: public IComManagerFaceImp<IComManagerFace>
	{
	public:
		// ��������
		//************************************
		// Method:    ~IComManagerFace
		// FullName:  VR_Soft::IComManagerFace::~IComManagerFace
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		// Parameter: void
		//************************************
		virtual ~IComManagerFace(void) { }
		
		//************************************
		// Method:    GetTypeName// ��ȡ��������
		// FullName:  VR_Soft::IComManagerFace::GetTypeName
		// Access:    virtual public 
		// Returns:   const VR_Soft::VRString&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const string& GetTypeName(void) const = 0;
		
		//************************************
		// Method:    Init // ��������г�ʼ��
		// FullName:  VR_Soft::IComManagerFace::Init
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: void
		//************************************
		virtual void Init(void) = 0;
	public:
		// ���û�ȡ����
		//SET_GET_PROPERTY_INTERFACE(Name, VRString);
		// static const VRString COM_TYPE_NAME;
	};
}
#endif