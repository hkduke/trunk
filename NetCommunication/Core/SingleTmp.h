
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
		// ���캯��
		explicit Singleton(void)
		{
			// ����ȷ�� ����Ϊ��
			assert(m_pSingleton == nullptr);

#if defined(_MSC_VER) && _MSC_VER < 1200
			// �����ַ����
			int offset = (int)(T*)1 - (int)(Singleton<T>*)(T*)1;
			m_pSingleton = (T*)((int)this + offset);
#else
			m_pSingleton = static_cast<T*>(this);
#endif
		}
		// ��������
		~Singleton(void)
		{
			// ����ָ�벻Ϊ��
			assert (m_pSingleton != nullptr);
			m_pSingleton = nullptr;
		}

	public:
		// ��ȡ��������
		static T* GetInstancePtr(void)
		{
			return (m_pSingleton);
		}

		static T& GetInstance(void)
		{
			//����ָ�벻Ϊ��
			assert(nullptr != m_pSingleton);
			return (*m_pSingleton);
		}

	protected:
		static T* m_pSingleton; // ��������

	private:
		// ��ֹ= �� ��������
		Singleton(const Singleton<T>& );
		Singleton& operator=(const Singleton<T>& );
	};

	template<typename T>
	T* Singleton<T>::m_pSingleton = nullptr;
}

#endif // SINGLETMP_H