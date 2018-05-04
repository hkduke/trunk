#include "FilePack.h"
#include "../Core/CommonTool.h"
#include "../Core/ResourceManager.h"
#include "../Core/LogManager.h"
#include "time.h"
//#include "../Core/Checksum.h"
namespace NetCom
{
	FilePack::FilePack()
	{
		m_data = new char[1024];

		assert(m_data);

		memset(m_data, 0, 1024);

	}


	FilePack::FilePack(const FilePack& that)
	{
		m_data = new char[1024];

		assert(m_data);

		memset(m_data, 0, 1024);


		m_lenth = that.m_lenth;

		m_packType = that.m_packType;

		m_fileName = that.m_fileName;

		memcpy(m_data, that.m_data, 1024);

	}

	FilePack& FilePack::operator=(const FilePack & that)
	{
		if (this == &that)
		{
			return *this;
		}
		else
		{
			m_lenth = that.m_lenth;

			m_packType = that.m_packType;

			m_fileName = that.m_fileName;

			memcpy(m_data, that.m_data, 1024);

			return *this;
		}


	}

	FilePack::~FilePack()
	{
		delete[]m_data;
	}

	void FilePack::ParseFile(void * data)
	{
		//Timestamp timeStamp;
		UInt16 contentLenth = ToolClass::GetFixData<UInt16>(data, 1);
		//UInt16 contentLenth = ToolClass::GetFixData<UInt16>(data, DATALENTHSIZEPOSE);
		m_packType = ToolClass::GetPackFlag(data);
		char checkLenth = ToolClass::GetFixData<char>(data, 14);
		//char checkLenth = ToolClass::GetFixData<char>(data, FILECHECKLENTHPOSE);
		char fileNameLenth = ToolClass::GetFixData<char>(data, 14 + 1 + checkLenth);
		//char fileNameLenth = ToolClass::GetFixData<char>(data, FILECHECKPOSE + checkLenth);
		m_fileName = std::string((char*)data + 15 + checkLenth + 1, fileNameLenth);
		//m_fileName = std::string((char*)data + FILECHECKPOSE + checkLenth + FILENAMLENTHSIZE, fileNameLenth);
		m_lenth = contentLenth - 3 - 1 - checkLenth - 1 - fileNameLenth - 1;
		bool isCheckOK=true;
		//检验校验和
		//Checksum checkSum(Checksum::TYPE_ADLER32);
		//checkSum.update((char*)data, pack->m_lenth - FRAMTAILCHECKSIZE);
		//UInt16 checkNumber = (UInt16)checkSum.checksum();
		

		//checkSum.update((char*)data + STANDAREDHEADSIZE, FILETOPICIDSIZE + FILECHECKLENTHSIZE + checkedLenth +
		//	FILENAMLENTHSIZE + fileName.size() + packSize);
	//	checkNumber = (UInt8)checkSum.checksum();


		//m_lenth = contentLenth - FILETOPICIDSIZE - FILECHECKLENTHSIZE - checkLenth - FILENAMLENTHSIZE - fileNameLenth - FILECHECKSIZE;
		//LogManager::GetInstance().WriteMessage("接收到的可用字节为：%d个\n", m_lenth);
		try
		{
			memcpy(m_data, (char*)data + 11 + 3 + 2 + checkLenth + fileNameLenth, m_lenth);
		}
		
		catch (...)
		{
			std::cout << "FilePack::ParseFile::::" << "memcpy异常" << std::endl;
		}
		//std::cout << "FilePack::ParseFile::::jiebao::::::::::::" << (int)timeStamp.elapsed() << std::endl;
		//memcpy(m_data, (char*)data + FILECHECKPOSE + checkLenth +FILENAMLENTHSIZE+ fileNameLenth, m_lenth);
		//LogManager::GetInstance().WriteMessage("接收到的可用字节为：%d个\n", GetLenth());
	}

	int FilePack::GetLenth()
	{
		return m_lenth;
	}

	void FilePack::SetTotalCheckSum(int begin, UInt16 number)
	{
		ToolClass::SetFixData<UInt16>(m_data, begin, number);
	}

	UInt16 FilePack::GetTotalCheckSum(int begin)
	{
		return m_dataCheckSum;
	}

	void FilePack::SetDataCheckSum(int begin, UInt8 number)
	{
		ToolClass::SetFixData<UInt8>(m_data, begin, number);
	}

	UInt8 FilePack::GetDataCheckSum(int begin)
	{
		return m_filecheckSum;
	}


	char* FilePack::GetData()
	{
		return m_data;
	}

	char* FilePack::GetFileData()
	{
		return m_fileContent;
	}

	int FilePack::GetPackageType()
	{
		return m_packType;
	}

	void FilePack::SetPacketSize(int lenth)
	{
		m_data = new char[lenth];
		m_lenth = lenth;
	}
	//FIXME以后修改为根据外部传入数据长度来进行分包
	std::vector<FilePack*> FilePack::GetFilePackages(void * data, int lenth, std::string fileName, int checkedLenth)
	{
		std::vector<FilePack*> packList;
		if (!data)
		{
			return packList;
		}
		int n = lenth;
		int begin = 0;//记录文件打包的位置
		int packFlag = 0;//记录包的类型
		int packSize = 0;//记录包的大小
		int packNumber = 1;
		int reserveNumber = 1024 - 11 - 4 - checkedLenth - 1 - fileName.size() - 2 - 1;
		int temp = FILECHECKLENTHPOSE;
		/*int reserveNumber = MAXPACKAGESIZE - FILECHECKLENTHPOSE - checkedLenth -
		FILENAMLENTHSIZE - fileName.size() - FRAMTAILCHECKSIZE - FILECHECKSIZE;*/
		int packageNumber = 0;
		if (lenth % reserveNumber == 0)
		{
			packageNumber = lenth / reserveNumber;
		}
		else
		{
			packageNumber = lenth / reserveNumber + 1;
		}

		//int reserveNumber =pack.GetReserveNumber(fileName, checkedLenth);//计算的包的可用数据字节
		//总长度-可用长度-帧尾-帧尾校验和
		bool isFirst = true;
		//如果总长度小于保留长度，则单包发送
		Timestamp begintime = Timestamp();
		if (n < reserveNumber)
		{
			FilePack* pack = new FilePack;
			pack->GetReserveNumber(fileName, checkedLenth);
			pack->FillHeader(0, lenth + FILETOPICIDSIZE + FILECHECKLENTHSIZE + checkedLenth + FILENAMLENTHSIZE + fileName.size());
			pack->FillFilePack(data, 15 + checkedLenth + 1 + fileName.size(), lenth);
			pack->m_lenth = 4 + checkedLenth + 1 + fileName.size() + reserveNumber + 3 + 11;
			//pack->FillFilePack(data, FILECHECKPOSE + checkedLenth + FILENAMLENTHSIZE + fileName.size(), lenth);
			pack->SetFrameID(packNumber);
			packList.push_back(pack);
		}
		else
		{
			
			for (int i = 0; i < packageNumber; i++)
			{
				//Timestamp forTime;
				//Timestamp forTimeEnd;
				FilePack* pack = new FilePack;
				pack->GetReserveNumber(fileName, checkedLenth);
				if (isFirst)
				{
					packFlag = 1;
					packSize = 1024 - 11 - 4 - checkedLenth - 1 - fileName.size() - 2 - 1;
					/*packSize = MAXPACKAGESIZE - FILECHECKPOSE - checkedLenth - FILENAMLENTHSIZE -
					fileName.size() - FRAMTAILCHECKSIZE - FILECHECKSIZE;*/
					isFirst = false;
					//SetPacketSize();
				}
				else if (i == packageNumber - 1)
				{
					packFlag = 3;
					packSize = lenth - (packageNumber - 1)*reserveNumber;
				}
				else
				{
					packFlag = 2;
					packSize = 1024 - 11 - 4 - checkedLenth - 1 - fileName.size() - 2 - 1;
					/*packSize = MAXPACKAGESIZE - FILECHECKPOSE - checkedLenth - FILENAMLENTHSIZE -
					fileName.size() - FRAMTAILCHECKSIZE - FILECHECKSIZE;*/
				}
				//forTime = Timestamp();
				pack->FillHeader(packFlag, packSize + 4 + checkedLenth + 1 + fileName.size() + 1);
				// forTimeEnd = Timestamp();
				//LogManager::GetInstance().WriteMessage("FilePack::FillHeader分%d包总耗时为%d\n", i, (int)(forTimeEnd - forTime));
				/*pack->FillHeader(packFlag, packSize + FILETOPICIDSIZE+ FILECHECKLENTHSIZE +
				checkedLenth + FILENAMLENTHSIZE + fileName.size() + FILECHECKSIZE);*/
				pack->m_packType = packFlag;
				//forTime = Timestamp();
				pack->FillFilePack(((char*)data) + begin, 15 + checkedLenth + 1 + fileName.size(), packSize);
				//forTimeEnd = Timestamp();
				//LogManager::GetInstance().WriteMessage("FilePack::FillFilePack分%d包总耗时为%d\n", i, (int)(forTimeEnd - forTime));
				/*	pack->FillFilePack(((char*)data) + begin, FILECHECKPOSE + checkedLenth
				+ FILENAMLENTHSIZE + fileName.size(), packSize);*/
				//forTime = Timestamp();
				pack->SetFrameID(packNumber);
				pack->m_fileName = fileName;
				//forTimeEnd = Timestamp();;
				//LogManager::GetInstance().WriteMessage("FilePack::SetFrameID分%d包总耗时为%d\n", i, (int)(forTimeEnd - forTime));
				pack->m_lenth = 4 + checkedLenth + 1 + fileName.size() + packSize + 3 + 11;
				//pack->m_lenth = FILETOPICIDSIZE+ FILECHECKLENTHSIZE + checkedLenth +
				//FILENAMLENTHSIZE + fileName.size() + packSize + FRAMTAILCHECKSIZE +
					//FILECHECKSIZE + STANDAREDHEADSIZE;
				//Checksum checkSum(Checksum::TYPE_ADLER32);
				//checkSum.update((char*)data, pack->m_lenth - FRAMTAILCHECKSIZE);
				//UInt16 checkNumber = (UInt16)checkSum.checksum();
				//pack->SetTotalCheckSum(pack->m_lenth - FRAMTAILCHECKSIZE, checkNumber);

			//	checkSum.update((char*)data + STANDAREDHEADSIZE, FILETOPICIDSIZE + FILECHECKLENTHSIZE + checkedLenth +
				//	FILENAMLENTHSIZE + fileName.size() + packSize);
				//checkNumber= (UInt8)checkSum.checksum();
				//pack->SetDataCheckSum(pack->m_lenth - FRAMTAILCHECKSIZE - FILECHECKSIZE, checkNumber);
				packList.push_back(pack);
				//forTimeEnd = Timestamp();;
				//LogManager::GetInstance().WriteMessage("FilePack::push_back分%d包总耗时为%d\n", i, (int)(forTimeEnd - forTime));
				//pack->ParseFile(pack->m_data);
				//LogManager::GetInstance().WriteMessage("FilePack::GetFilePackages分包后的可用字节为：%d个\n,包的序号为%d\n，包的类型为%d", packSize, packNumber, packFlag);
				begin += packSize;
				packNumber += 1;
				
				//LogManager::GetInstance().WriteMessage("FilePack::GetFilePackages分%d包总耗时为%d\n",i, (int)(forTimeEnd - forTime));
			}
		}
		Timestamp endTime = Timestamp();
		LogManager::GetInstance().WriteMessage("FilePack::GetFilePackages分包总耗时为%d\n",(int)(endTime-begintime));
		return packList;
	}

	std::string FilePack::GetFileName()
	{
		return m_fileName;
	}

	void FilePack::SetSomeData(void* data, int begin, int lenth)
	{
		memcpy((char*)data + begin, data, lenth);
	}

	int FilePack::GetFileSerial(void* buff)
	{
		//UInt16 lowNumber= ToolClass::GetFixData<UInt16>(buff, 11);
		UInt16 lowNumber = ToolClass::GetFixData<UInt16>(buff, STANDAREDHEADSIZE);
		int number = 0;
		number |= lowNumber;
		//int heighNumber = (int)ToolClass::GetFixData<char>(buff, 13);
		int heighNumber = (int)ToolClass::GetFixData<char>(buff, STANDAREDHEADSIZE + 2);
		heighNumber <<= 16;
		number |= heighNumber;
		return number;
	}

	void FilePack::FillHeader(int i, int packLenth)//共11个字节
	{
		//根据帧格式 创建文件报头
		int begin = 0;
		//ToolClass::SetPackFramType(m_data, 0);
		ToolClass::SetPackFlag(m_data, i);
		int uu = ToolClass::GetPackFlag(m_data);
		// 		ToolClass::SetPackProperity(m_data, 2);
		//设置包的长度
		begin = +1;
		ToolClass::SetFixData<UInt16>(m_data, begin, UInt16(packLenth));
		begin += 2;
		//设置包的主题号
		ToolClass::SetFixData<UInt16>(m_data, begin, EPackType::FileTranse);
		begin += 2;
		ToolClass::SetFixData<char>(m_data, begin, (char)ResourceManager::GetInstance().GetCurrentNode()->GetNodeID());
		begin += 1;
		ToolClass::SetFixData<char>(m_data, begin, (char)255);
		begin += 1;
		ToolClass::SetFixData<UInt32>(m_data, begin, (UInt32)time(0));
		begin += 4;
	}

	void FilePack::SetString(void* data, int begin, std::string str)
	{
		memcpy(((char*)data) + begin, str.c_str(), str.size());
	}

	int FilePack::GetReserveNumber(std::string fileName, int checkedleth)
	{
		int reserveNuber = MAXPACKAGESIZE;
		//包的大小减于包头11，文件帧头3,文件校验码长度占的一个字节
		//reserveNuber -= 15;
		reserveNuber -= STANDAREDHEADSIZE + FILETOPICIDSIZE + FILECHECKLENTHSIZE;
		int nameSize = fileName.size();
		//根据校验方法减于校验码
		reserveNuber -= checkedleth;
		ToolClass::SetFixData<char>(m_data, 14, (char)checkedleth);
		//ToolClass::SetFixData<char>(m_data, STANDAREDHEADSIZE + FILETOPICIDSIZE, (char)checkedleth);
		//设置校验码

		//包的大小减于文件长度的字节1
		reserveNuber -= 1;
		//设置文件名长度
		ToolClass::SetFixData<char>(m_data, 14 + 1 + checkedleth, (char)fileName.size());
		//ToolClass::SetFixData<char>(m_data, STANDAREDHEADSIZE + FILETOPICIDSIZE + FILECHECKLENTHSIZE
		//+ checkedleth, (char)fileName.size());
		////包的大小减于文件名占位
		reserveNuber -= (nameSize);


		//设置文件名
		SetString(m_data, 14 + 1 + checkedleth + 1, fileName);
		//SetString(m_data, STANDAREDHEADSIZE + FILETOPICIDSIZE + FILECHECKLENTHSIZE + 
		//	checkedleth +FILECHECKLENTHSIZE, fileName);
		reserveNuber -= 3;
		return reserveNuber;
	}

	void FilePack::SetFrameID(int framID)
	{
		char heightchar = framID >> 16;
		UInt16 lowData = (UInt16)(framID & 65535);

		ToolClass::SetFixData<UInt16>(m_data, 11, lowData);
		ToolClass::SetFixData<char>(m_data, 13, heightchar);
		//ToolClass::SetFixData<UInt16>(m_data, STANDAREDHEADSIZE, lowData);
		//ToolClass::SetFixData<char>(m_data, STANDAREDHEADSIZE+2, heightchar);
	}

	void FilePack::FillFilePack(void * data, int begin, int lenth)
	{
		memcpy(((char*)m_data) + begin, data, lenth);
	}

}

