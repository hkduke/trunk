#ifndef XLWRITER_H
#define XLWRITER_H
//xmlÊý¾Ý½âÎöÐ´
#include <QTreeWidget>
#include <QXmlStreamWriter>
#include <QTreewidgetItem>
#include "xlDataManager.h"
#include <QAxObject>
#include <QAxWidget>

class xlWriter:public QObject
{
	Q_OBJECT
public:

public:
	xlWriter();

	bool writeFile(QIODevice* dev);

	void setDataManager(xlDataManager* dataManager);

	void saveData();

	void saveWord();

	void insertTable(xlDataManager::PropStruct prop);
private:
	void writeItem(QTreeWidgetItem* item);
	void writeMessage(QTreeWidgetItem * item);
	void writeMessageContent(QString messageName);
	QTreeWidget* treeWidget;
	QXmlStreamWriter xml;
	xlDataManager* manager;

	QAxWidget* word;
	QAxObject* documents;
	QAxObject* document;
	
};

#endif // XLWRITER_H
