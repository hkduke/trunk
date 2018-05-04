#ifndef XMLWRITER_H
#define XMLWRITER_H
#include <QXmlStreamWriter>
#include "devicdatamanager.h"

#include <QObject>

class xmlWriter : public QObject
{
	Q_OBJECT

public:
	xmlWriter();
	~xmlWriter();

	//bool writeFile(QIODevice* dev);
	void setDataManager(DevicDataManager* dataManager);

	void saveData(QString Name="");
private:
	QXmlStreamWriter xml;
	DevicDataManager* manager;
};

#endif // XMLWRITER_H
