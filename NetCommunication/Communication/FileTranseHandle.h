#pragma once
#include "../Core/EventHandle.h"
#include <map>
#include <fstream>
#include "../Core/Types.h"
namespace NetCom
{
	
	class FileTranseManager;
	class FileTranseHandle :
		public EventHandle
	{
	public:
		FileTranseHandle();
		~FileTranseHandle();

		virtual int HandleEnter(void *ptr);

		virtual int Handle(void *ptr);

		virtual int HandleClose(void *ptr);

		void SetNodeId(UInt32 id);

		inline void SetFileTranseManager(FileTranseManager * ptr)
		{
			m_pFileTranseManager = ptr;
		}
		
	private:
		UInt32 m_nodeid;
		UInt32 m_fileSer;
		FileTranseManager * m_pFileTranseManager;
		friend class FileTranseManager;
	};


}


