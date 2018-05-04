#pragma once
#ifndef _PUBLICE_DYLIB_H_
#define _PUBLICE_DYLIB_H_
#include <string>
#include <iostream>

#if ( __WIN32__ ) || defined( _WIN32 )
#    define DYNLIB_HANDLE hInstance
#    define DYNLIB_LOAD( a ) LoadLibraryExA( a, NULL, LOAD_WITH_ALTERED_SEARCH_PATH )
#    define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#    define DYNLIB_UNLOAD( a ) !FreeLibrary( a )

struct HINSTANCE__;
typedef struct HINSTANCE__* hInstance;

#else OGRE_PLATFORM == OGRE_PLATFORM_LINUX || OGRE_PLATFORM == OGRE_PLATFORM_ANDROID || OGRE_PLATFORM == OGRE_PLATFORM_NACL
#    define DYNLIB_HANDLE void*
#    define DYNLIB_LOAD( a ) dlopen( a, RTLD_LAZY | RTLD_GLOBAL)
#    define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#    define DYNLIB_UNLOAD( a ) dlclose( a )
#endif
using namespace std;
namespace NetCom
{
	class  DyLib
	{
	public:
		// ��̬��
		explicit DyLib(const string& fileName);
		~DyLib(void);

		// �����ļ�
		void Load(void);
		// ж���ļ�
		void Unload(void);
		// ��ȡ��̬������
		const string& GetName(void) const { return (m_strName); }

		
        /**
            Returns the address of the given symbol from the loaded library.
            @param
                strName The name of the symbol to search for
            @return
                If the function succeeds, the returned value is a handle to
                the symbol.
            @par
                If the function fails, the returned value is <b>NULL</b>.

        */
		void* GetSymbol(const string& strName) const throw();

	protected:
		DyLib(const DyLib&);
		DyLib& operator= (const DyLib&);
		bool operator==(const DyLib&);

	protected:
		// ��ô�����Ϣ
		string GetDyLibLastError(void);

	private:
		string m_strName; // ��̬���ļ�����
		DYNLIB_HANDLE m_hInstance; // ��̬����
	};
}

#endif // _PUBLICE_DYLIB_H_


