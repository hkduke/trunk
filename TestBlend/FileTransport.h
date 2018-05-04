#pragma once
#include "../Communication/FileTranseManager.h"

using namespace NetCom;
class FileTransport
{
public:
	FileTransport();
	~FileTransport();

	void process(void * ptr);

	FileTranseManager  m_pFileTranseManager;
	UINT32 m_nodeid;
};

