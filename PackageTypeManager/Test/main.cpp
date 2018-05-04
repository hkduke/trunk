#include <QtCore/QCoreApplication>
#include <QDebug>
#include "PackageTypeManager.h"
#include <QBitArray>
#include <QtEndian>
#include <QBuffer>
#include <QDataStream>
#include "Poco/Any.h"
#include "BasePackage.h"
#include "Poco/Types.h"
#include <iostream>
#include <QMap>

typedef unsigned char   uint8;         
typedef signed   char   int8;          
typedef unsigned short  uint16;        
typedef signed   short  int16;         
typedef unsigned int    uint32;        
typedef signed   int    int32;            

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	//float v11 = 1111.02;
	//QByteArray b1 = QByteArray::fromRawData(reinterpret_cast<const char*>(&v11), sizeof(v11));
	//qDebug() << b1;
	//qDebug() << b1.data();
	//qDebug() << *reinterpret_cast<float*>(b1.data());


	//int int_head = 15;
	//QByteArray byte_head;
	//byte_head[0] = (uchar)(0x000000ff & int_head);
	//byte_head[1] = (uchar)((0x0000ff00 & int_head) >> 8);
	//byte_head[2] = (uchar)((0x00ff0000 & int_head) >> 16);
	//byte_head[3] = (uchar)((0xff000000 & int_head) >> 24);
	//
	//qDebug() << byte_head.size();

	//int j = byte_head[0] & 0x000000ff;
	//j |= ((byte_head[1] << 8) & 0x0000ff00);
	//j |= ((byte_head[2] << 16) & 0x00ff0000);
	//j |= ((byte_head[3] << 24) & 0xff000000);

	//qDebug() << j;

	//qDebug() << byte_head.toInt();

	//PackageTypeManager p;
	//p.initInterpreter(QString::fromLocal8Bit("C:/Users/陶梦/Desktop/报文.xml"));
	//p.writeXML(QString::fromLocal8Bit("C:/Users/陶梦/Desktop/报文2.xml"));
	//p.setName(QString::fromLocal8Bit("数据指令报文"));
	
	BasePackage b;
	b.readXml("C:/Users/陶梦/Desktop/报文2.xml");
	b.setPackage("1553B通讯检查命令");
	
	//QMap<QString, QByteArray>::const_iterator it = b.package.byteMap.constBegin();
	//while (it != b.package.byteMap.constEnd())
	//{
	//	qDebug() << it.key() << ": " << it.value() << "," << it.value().size();
	//	++it;
	//}

	Poco::UInt8 v1 = 11;
	b.setValue("头字", v1);
	//qDebug() << b.package.byteMap[QString::fromLocal8Bit("头字")];
	//qDebug() << b.package.byteMap[QString::fromLocal8Bit("头字")].data();
	//qDebug() << *reinterpret_cast<Poco::UInt8*>(b.package.byteMap[QString::fromLocal8Bit("头字")].data());
	if(!b.getValue("头字").empty())
		qDebug() << Poco::AnyCast<Poco::UInt8>(b.getValue("头字"));
	getchar();
	return a.exec();
}
