
#ifndef SINGLETMP_H
#define SINGLETMP_H
#include "Export.h"
#include <assert.h>

namespace NetCom
{
	template <typename T>
	class  Singleton
	{
	public:
		// 构造函数
		explicit Singleton(void)
		{
			// 断言确认 对象为空
			assert(m_pSingleton == nullptr);

#if defined(_MSC_VER) && _MSC_VER < 1200
			// 计算地址对象
			int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
			m_pSingleton = (T*)((int)this + offset);
#else
			m_pSingleton = static_cast<T*>(this);
#endif
		}
		// 析构函数
		~Singleton(void)
		{
			// 断言指针不为空
			assert (m_pSingleton != nullptr);
			m_pSingleton = nullptr;
		}

	public:
		// 获取单例对象
		static T* GetInstancePtr(void)
		{
			return (m_pSingleton);
		}

		static T& GetInstance(void)
		{
			//断言指针不为空
			assert(nullptr != m_pSingleton);
			return (*m_pSingleton);
		}

	protected:
		static T* m_pSingleton; // 单例对象

	private:
		// 禁止= 和 拷贝函数
		Singleton(const Singleton<T>& );
		Singleton& operator=(const Singleton<T>& );
	};

	template<typename T>
	T* Singleton<T>::m_pSingleton = nullptr;
}

#endif // SINGLETMP_H