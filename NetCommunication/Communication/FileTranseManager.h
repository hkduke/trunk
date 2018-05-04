#pragma once
#include <map>
#include "../Core/Types.h"
#include "../Core/Hash.h"
#include <vector>
#include "../Core/CoreCommon.h"
#include "../Core/CommonTool.h"
#include <assert.h>
#include <utility>
namespace NetCom
{
	typedef struct _sFileObjectPack	// ‘§¡Ù
	{
		UInt32 _serid;
		void * _data;
		UInt32 _len;
		// ≤ªøΩ±¥data
		_sFileObjectPack(void * data, UINT32 len, UInt32 id)
		{
			_serid = id;
			_len = len;
			_data = data;
		}
		_sFileObjectPack() :_serid(0), _data(nullptr), _len(0) {}

	}FileObjectPack;

	typedef struct _FileSerial
	{
		UInt32 _id;
		UInt32 _maxLength;
		_FileSerial(UInt32 id, UInt32 max) :_id(id), _maxLength(max) {}

		inline bool operator==(const _FileSerial &rhs)const
		{
			return rhs._id == _id;
		}

		inline bool operator<(const _FileSerial &rhs)const
		{
			return rhs._id < _id;
		}
		inline void SetMaxLength(UInt32 id)
		{
			_maxLength = id;
		}
	}FileSerial;


	typedef std::map<UInt32, FileObjectPack> MapOfstream;
	typedef std::map<FileSerial, MapOfstream*> MapNodeFile;
	class FileTranseHandle;


	class NETCOMMUNICATION_EXPORT FileTranseManager
	{
	public:

		FileTranseManager();
		~FileTranseManager();

		void Init();

		inline MapNodeFile & GetMapNodeFile()
		{
			return m_fileData;
		}

		inline void PushFrameObj(void * data,UInt32 len , UInt32 ser , MapOfstream & stream)
		{
			assert(data&&len >= 0);
			FileObjectPack obj;
			obj._data = MALLOC(len);
			memcpy(obj._data, data, len);
			assert(obj.data);
			obj._serid = ser;
			obj._len = len;
			stream.insert(std::pair<UInt32, FileObjectPack>(ser, obj));
		}

		inline bool HasId(UInt8 id)
		{
			FileSerial fs =  FileSerial(id, 0);
			MapNodeFile::iterator iterMap = m_fileData.find(fs);
			return (iterMap != m_fileData.end());
		}

		inline MapOfstream & GetMapOfstream(UInt32 id)
		{
			FileSerial fs =  FileSerial(id, 0);
			MapNodeFile::iterator iterMap = m_fileData.find(fs);
			if (iterMap != m_fileData.end())
			{
				return *iterMap->second;
			}
			else
			{
				FileSerial fs =  FileSerial(id, 0);
				fs._id = id;
				fs._maxLength = -1;
				MapOfstream *stream = new MapOfstream;
				m_fileData.insert(std::make_pair(fs, stream));
				return *stream;
			}
		}

		inline bool IsEndPack(void * data)
		{
			UInt32 packType = ToolClass::GetPackFlag(data);
			if (packType == 3)
			{
				return true;
			}
			return false;
		}

		bool WirteFile(UInt8 id,std::string fileName);
		bool CheckSumFileSerid(UInt32 id = 0);

		bool Check(std::vector<UInt32> & ser,UInt32 maxId, const MapOfstream &stream);
		void Check(UInt32 id);
		inline void SetFileNodeId(UInt32 id)
		{
			m_fileNodeid = id;
		}

		inline UInt32 GetFileNodeId()
		{
			return m_fileNodeid;
		}
	private:
		FileTranseHandle * m_fileptr;
		MapNodeFile m_fileData;
		bool m_bIsEnableAck;
		bool m_isRecEndPack;
		UInt32 m_fileNodeid;
	};
}
