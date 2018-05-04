#ifndef XLREADER_H
#define XLREADER_H
//xml���ݽ���������
#include <QXmlStreamReader>
#include <QList>
#include <QTreeWidget>
#include <QMap>
#include <QStringList>
#include "xlDataManager.h"
class xlReader
{
public:
	xlReader();

	bool read(QIODevice* device);

	bool ReadNextXml();

	QString errorString()const;

	void setxlDataManager(xlDataManager * manager);

private:

	void readXml();


	void readProt();

	void readMessage(xlDataManager::ProtStruct* prot);

	void readMessagePro(xlDataManager::MessageStruct* protStruct);

	
private:
	QXmlStreamReader xml;
	QIcon folderIcon;
	QIcon bookMarkIcon;
	xlDataManager* xlmManager;

};

#endif // XLREADER_H
