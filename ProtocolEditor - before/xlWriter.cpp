#include "xlWriter.h"
#include <qfile.h>
#include <qfiledialog.h>
#include <QVariantList>
#include <QFile>
#include <QTextStream>

//const char* name = "fdfd";
const char* name[xlDataManager::protEnd]={"protocol","protocolName","message"
	,"messageName","messageExt","messageProp","propName","propStyle","propSize","propHint","propExt"};
xlWriter::xlWriter()
{
	xml.setAutoFormatting(true);
}

bool xlWriter::writeFile(QIODevice* dev)
{
	xml.setDevice(dev);
	xml.writeStartDocument();
	xml.writeDTD("<!DOCTYPE xml>");
	xml.writeStartElement("xml");
	xml.writeAttribute("version","1.0");
	xml.writeAttribute("version", manager->GetVersionInfo());
	QTreeWidgetItem* rootItem=treeWidget->topLevelItem(0);
	for(int i=0;i<rootItem->childCount();++i)
	{
		writeItem(rootItem->child(i)); 
	}
	xml.writeEndDocument();
	return true;
}


void xlWriter::setDataManager(xlDataManager* dataManager)
{
	this->manager=dataManager;
}

void xlWriter::writeItem(QTreeWidgetItem* item)
{
	QString tagName	=	item->data(0,Qt::UserRole).toString();

	if(tagName	==	name[xlDataManager::protocolName])
	{
		xml.writeStartElement("protocol");
		xml.writeTextElement(tagName,item->text(0));
		for(int i=0;i<item->childCount();++i)
		{
			writeMessage(item->child(i));
		}

		xml.writeEndElement();
	}	


}
//const char* name[xlDataManager::prot::protEnd]={"protocolList","protListName","protocol"
//,"protName","protExt","protPro","propName","propStyle","propSize","propHint","propExt"};
void xlWriter::writeMessage(QTreeWidgetItem * item)
{
	xml.writeStartElement("message");
	QString tagName = item->data(0,Qt::UserRole).toString();
	xml.writeTextElement(tagName,item->text(0));
	for(int i=0;i<item->childCount();++i)
	{
		writeMessageContent(item->child(i)->text(0));
	}
	xml.writeEndElement();
}

void xlWriter::writeMessageContent(QString messageName)
{
	xlDataManager::MessageStruct tempMessage;
	if(!manager->MessageIsExsit(messageName))
	{
		xml.writeTextElement(name[xlDataManager::messageExt],
			tempMessage.messageExt.c_str());
		for(int i=0;i<tempMessage.propList.size();i++)
		{
			xml.writeStartElement("messageProp");
			xml.writeTextElement(name[xlDataManager::propName],
				tempMessage.propList.at(i).propName.c_str());
			xml.writeTextElement(name[xlDataManager::propStyle],
				tempMessage.propList.at(i).propStyle.c_str());
			xml.writeTextElement(name[xlDataManager::propSize],
				QString::number(tempMessage.propList.at(i).propSize));
			xml.writeTextElement(name[xlDataManager::propHint],
				tempMessage.propList.at(i).propHint.c_str());
			xml.writeTextElement(name[xlDataManager::propExt],
				tempMessage.propList.at(i).propExt.c_str());
			xml.writeEndElement();
		}	
	}
}


void xlWriter::saveData()
{
	 QString fileName = QFileDialog::getSaveFileName(0, tr("Save File"),QString("./elCD%1.XML").arg(manager->GetVersionInfo()),tr(".xml") );

	 QFile file(fileName);
	 if(file.open(QIODevice::WriteOnly | QIODevice::Text))
	 {
		 xml.setDevice(&file);
		 xml.writeStartDocument();

		 xml.writeDTD("<!DOCTYPE xml>");
		 xml.writeStartElement("xml");
		 xml.writeAttribute("version","1.0");
		 xml.writeAttribute("protocolVersion", manager->GetVersionInfo());
		 QMapIterator<QString,xlDataManager::ProtStruct> protIt(manager->protList);
		 while(protIt.hasNext())
		 {
			 protIt.next();

			 xml.writeStartElement("protocol");
			 xml.writeTextElement("protocolName", protIt.key());
			 
			 for(int i = 0; i < protIt.value().messages.size(); i++ )
			 {
			     xml.writeStartElement("message"); 
				 xml.writeTextElement("messageName", manager->messageList.value(protIt.value().messages.at(i).c_str() ).messageName.c_str());
				 xml.writeTextElement("messageExt", manager->messageList.value(protIt.value().messages.at(i).c_str() ).messageExt.c_str());
				 
				 for(int j = 0; j < manager->messageList.value(protIt.value().messages.at(i).c_str()).propList.size(); j++)
				 {
					 xml.writeStartElement("messageProp");
					 xml.writeTextElement("propName", manager->messageList.value(protIt.value().messages.at(i).c_str() ).propList.at(j).propName.c_str());
					 xml.writeTextElement("propStyle", manager->messageList.value(protIt.value().messages.at(i).c_str() ).propList.at(j).propStyle.c_str());
					 xml.writeTextElement("propSize", QString::number(manager->messageList.value(protIt.value().messages.at(i).c_str() ).propList.at(j).propSize) );
					 xml.writeTextElement("propHint", manager->messageList.value(protIt.value().messages.at(i).c_str() ).propList.at(j).propHint.c_str());
					 xml.writeTextElement("propExt", manager->messageList.value(protIt.value().messages.at(i).c_str() ).propList.at(j).propExt.c_str());
					 xml.writeEndElement();
				 }
				 
				 xml.writeEndElement();
			 }
			 xml.writeEndElement();
		 }
		 xml.writeEndDocument();
	 }
	 file.close();
}
#include <QDebug>
void xlWriter::saveWord()
{
	word = new QAxWidget("Word.Application");
	word->setProperty("Visible", false);

	documents = word->querySubObject("Documents");
	documents->dynamicCall("Add(void)");
	qDebug()<<documents->verbs();
	document = word->querySubObject("ActiveDocument");

	QAxObject *selection = word->querySubObject("Selection");
	selection->querySubObject("ParagraphFormat")->dynamicCall("Alignment", "wdAlignParagraphCenter");
	selection->querySubObject("Font")->dynamicCall("Size", "48");
	selection->dynamicCall("TypeText(const QString&)", QString::fromLocal8Bit("协议\n"));
	
	int num = 1;

	QMapIterator<QString,xlDataManager::ProtStruct> protIt(manager->protList);
	while(protIt.hasNext())
	{
		protIt.next();
		QAxObject *selection1= word->querySubObject("Selection");
		selection1->querySubObject("ParagraphFormat")->dynamicCall("Alignment", "wdAlignParagraphLeft");
		selection1->querySubObject("Font")->dynamicCall("Size", "48");
		selection1->dynamicCall("TypeText(const QString&)", QString::fromLocal8Bit("%1    %2\n").arg(num).arg(protIt.value().ProtName.c_str()));
		
		QAxObject *selection2= word->querySubObject("Selection");
		selection2->querySubObject("Font")->dynamicCall("Size", "28");
		selection1->dynamicCall("TypeText(const QString&)", QString::fromLocal8Bit("%1.1 备注:    %2\n").arg(num).arg(protIt.value().ProtExt.c_str()));

		if(protIt.value().messages.size() >= 1)
		{
			
			selection2->dynamicCall("TypeText(const QString&)", QString::fromLocal8Bit("%1.2 Message \n").arg(num));

			for(int i = 0; i < protIt.value().messages.size(); i++)
			{
				xlDataManager::MessageStruct m = manager->messageList.value(protIt.value().messages.at(i).c_str());
				QAxObject *selection3= word->querySubObject("Selection");
				selection3->querySubObject("Font")->dynamicCall("Size", "20");
				selection3->dynamicCall("TypeText(const QString&)", QString::fromLocal8Bit("%1.2.%3 %2\n").arg(num).arg(m.messageName.c_str()).arg(i+1));
				QAxObject *selection4= word->querySubObject("Selection");
				selection4->querySubObject("Font")->dynamicCall("Size", "16");
				selection4->dynamicCall("TypeText(const QString&)", QString::fromLocal8Bit("%1.2.%3.1 message备注:    %2\n").arg(num).arg(m.messageExt.c_str()).arg(i+1));
				for(int j = 0; j < m.propList.size(); j++)
				{
					selection4->dynamicCall("TypeText(const QString&)", QString::fromLocal8Bit("%1.2.%2.%3 详细:    \n").arg(num).arg(i+1).arg(j+2));
					insertTable(m.propList.at(0));
					selection4->dynamicCall("TypeText(const QString&)", QString::fromLocal8Bit("\n"));
				}
			}
		}
		num++;
	}


	QString fileName = QFileDialog::getSaveFileName(0, tr("Save File"),
		".",tr("*.doc *.docx"));
	QVariant newFileName(fileName);
	document->querySubObject("SaveAs(const QVariant&, const QVariant&)", 
		newFileName);

	document->dynamicCall("Close(boolean)", true);
	word->dynamicCall("Quit(void)");

	
}

void xlWriter::insertTable(xlDataManager::PropStruct prop)
{
	/*QAxObject *bookmark = document->querySubObject("Bookmarks(QVariant)", "Table");
	if(bookmark)
	{*/
		//bookmark->dynamicCall("Select(void)");
		QAxObject *selection = word->querySubObject("Selection");
		selection->querySubObject("Font")->dynamicCall("Size", "16");
		selection->dynamicCall("InsertAfter(QString&)", "\n");
		selection->querySubObject("ParagraphFormat")->dynamicCall("Alignment", "wdAlignParagraphCenter");

		QAxObject *range = selection->querySubObject("Range");
		QAxObject *tables = document->querySubObject("Tables");
		QAxObject *table = tables->querySubObject("Add(QVariant, int , int)", range->asVariant(), 2, 5);

		table->setProperty("Style", "网格型");

		QAxObject *borders = table->querySubObject("Borders");
		borders->setProperty("InsideLineStyle", 1);
		borders->setProperty("OutsideLineStyle", 1);

		if(!table)
			return;

		QAxObject *cell = table->querySubObject("Cell(int, int)", 1, 1);
		cell->dynamicCall("Select(void)");
		if(!cell)
			return;
		cell->querySubObject("Range")->setProperty("Text", "propName");
		cell = table->querySubObject("Cell(int, int)", 1, 2);
		if(!cell)
			return;
		cell->querySubObject("Range")->setProperty("Text", "propStyle");
		cell = table->querySubObject("Cell(int, int)", 1, 3);
		if(!cell)
			return;
		cell->querySubObject("Range")->setProperty("Text", "propSize");
		cell = table->querySubObject("Cell(int, int)", 1, 4);
		if(!cell)
			return;
		cell->querySubObject("Range")->setProperty("Text", "propHint");
		cell = table->querySubObject("Cell(int, int)", 1, 5);
		if(!cell)
			return;
		cell->querySubObject("Range")->setProperty("Text", "propExt");
		cell = table->querySubObject("Cell(int, int)", 2, 1);
		if(!cell)
			return;
		cell->querySubObject("Range")->setProperty("Text", prop.propName.c_str());
		cell = table->querySubObject("Cell(int, int)", 2, 2);
		if(!cell)
			return;
		cell->querySubObject("Range")->setProperty("Text", prop.propStyle.c_str());
		cell = table->querySubObject("Cell(int, int)", 2, 3);
		if(!cell)
			return;
		cell->querySubObject("Range")->setProperty("Text", prop.propSize);
		cell = table->querySubObject("Cell(int, int)", 2, 4);
		if(!cell)
			return;
		cell->querySubObject("Range")->setProperty("Text", prop.propHint.c_str());
		cell = table->querySubObject("Cell(int, int)", 2, 5);
		if(!cell)
			return;
		cell->querySubObject("Range")->setProperty("Text", prop.propExt.c_str());


		QVariantList params;
		params.append(5);
		params.append(0);
		selection->dynamicCall("EndOf(QVariant&, QVariant&)", params).toInt();

	//}
}