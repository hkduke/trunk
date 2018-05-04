#ifndef _ICOMFACTORY_H
#define _ICOMFACTORY_H

#include <string>
using namespace std;

namespace NetCom
{
	class IComManagerFace;

	typedef struct ComManagerMetaData_TYP
	{
		string strType;
		string strInstanceName;
		string strDescription;
	}ComManagerMetaData, *PTR_ComManagerMetaData;

	class  IFactory
	{
	public:
		//************************************
		// Method:    IComFactory 
		///构造函数
		// FullName:  VR_Soft::IComFactory::IComFactory
		// Access:    public 
		// Returns:   
		// Qualifier: :m_bMetaDataInit(true)
		//************************************
		IFactory():m_bMetaDataInit(true){}
		
		//************************************
		// Method:    ~IComFactory
		/// 析构函数
		// FullName:  VR_Soft::IComFactory::~IComFactory
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~IFactory() { }
		
		//************************************
		// Method:    CreateInstance 
		/// 创建实例
		// FullName:  VR_Soft::IComFactory::CreateInstance
		// Access:    virtual public 
		// Returns:   VR_Soft::IComManagerFace*返回创建的实例
		// Qualifier:
		// Parameter: const VRString & strInstaneName 实例名称
		//************************************
		virtual IComManagerFace* CreateInstance(const VRString& strInstaneName) = 0;
		
		//************************************
		// Method:    DestoryInstance 
		/// 销毁实例
		// FullName:  VR_Soft::IComFactory::DestoryInstance
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: IComManagerFace * pInstance 需要销毁的实例
		//************************************
		virtual void DestoryInstance(IComManagerFace* pInstance) = 0;
		
		//************************************
		// Method:    InitMetaData
		/// 初始化属性
		// FullName:  VR_Soft::IComFactory::InitMetaData
		// Access:    virtual public 
		// Returns:   void
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual void InitMetaData(void) const = 0;
		
		//************************************
		// Method:    GetMetaData 
		/// 获取属性
		// FullName:  VR_Soft::IComFactory::GetMetaData
		// Access:    virtual public 
		// Returns:   const VR_Soft::ComManagerMetaData&
		// Qualifier: const
		// Parameter: void
		//************************************
		virtual const ComManagerMetaData& GetMetaData(void) const
		{
			if (m_bMetaDataInit)
			{
				InitMetaData();
				m_bMetaDataInit = false;
			}
			return m_MetaDate;
		}

	protected:
		mutable ComManagerMetaData m_MetaDate;
		mutable bool m_bMetaDataInit;
	};

	// 定义工厂宏
#define REGISTER_COMFACTORY(classname, factoryname, stypename, instancename, sDesc) \
	class C##factoryname##Factory : public IFactory{\
	public:\
		virtual ~C##factoryname##Factory() { }\
		virtual IComManagerFace* CreateInstance(const string& strInstaneName ){return (new classname(strInstaneName));}\
		virtual void DestoryInstance(IComManagerFace* pInstance){delete pInstance;}\
		virtual void InitMetaData(void) const {m_MetaDate.strType=stypename; m_MetaDate.strInstanceName=instancename; m_MetaDate.strDescription=sDesc;} \
	public:\
		static const string FACTORY_TYPE_NAME;};\

}

#endif // _ICOMFACTORY_H