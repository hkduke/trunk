#include "xmlwriter.h"
#include <QFileDialog>

xmlWriter::xmlWriter()
{
	xml.setAutoFormatting(true);
}

xmlWriter::~xmlWriter()
{

}
//设置设备管理数据对象
void xmlWriter::setDataManager(DevicDataManager* dataManager)
{
	this->manager = dataManager;

}
//保存设备节点为XML文件
void xmlWriter::saveData(QString Name)
{
	QString fileName = QFileDialog::getSaveFileName(0, tr("Save File"), ".", tr(".xml"));

	QFile file(fileName);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		xml.setDevice(&file);
		xml.writeStartDocument();

		xml.writeDTD("<!DOCTYPE xml>");
		xml.writeStartElement("xml");
		xml.writeAttribute("version", "1.0");

		QMapIterator<QString, DevicDataManager::DevStruct> dev(manager->m_deviceList);
		if (Name.isEmpty())
		{
			while (dev.hasNext())
			{
				dev.next();
				xml.writeStartElement("device");
				xml.writeTextElement("deviceName", dev.value().deviceName.c_str());
				xml.writeTextElement("deviceExt", dev.value().deviceExt.c_str());
				for (int m = 0; m < dev.value().portList.size(); m++)
				{
					xml.writeStartElement("port");
					xml.writeTextElement("portName", dev.value().portList.at(m).portName.c_str());
					for (int i = 0; i < dev.value().portList.at(m).protList.size(); i++)
					{
						DevicDataManager::ProtStruct prot = dev.value().portList.at(m).protList.at(i);
						xml.writeStartElement("protocol");
						xml.writeTextElement("protocolName", prot.protocolName.c_str());
						xml.writeTextElement("protocolExt", prot.protocolExt.c_str());

						for (int j = 0; j < prot.messgeList.size(); j++)
						{
							DevicDataManager::MessageStruct mess = prot.messgeList.at(j);

							xml.writeStartElement("message");
							xml.writeTextElement("messageName", mess.messageName.c_str());
							xml.writeTextElement("messageP", mess.messageP.c_str());
							xml.writeTextElement("messageExt", mess.messageExt.c_str());

							for (int k = 0; k < mess.propList.size(); k++)
							{
								DevicDataManager::PropStruct prop = mess.propList.at(k);
								xml.writeStartElement("messageProp");
								xml.writeTextElement("propName", prop.propName.c_str());
								xml.writeTextElement("propStyle", prop.propStyle.c_str());
								xml.writeTextElement("propSize", QString::number(prop.propSize));
								xml.writeTextElement("propHint", prop.propHint.c_str());
								xml.writeTextElement("propExt", prop.propExt.c_str());
								xml.writeEndElement();
							}
							xml.writeEndElement();
						}
						xml.writeEndElement();
					}
				}
				
				xml.writeEndElement();
			}
			xml.writeEndDocument();
		}
		else
		{
			while (dev.hasNext())
			{
				dev.next();
				xml.writeStartElement("device");
				xml.writeTextElement("deviceName", dev.value().deviceName.c_str());
				xml.writeTextElement("deviceExt", dev.value().deviceExt.c_str());
				for (int m = 0; m < dev.value().portList.size(); m++)
				{
					xml.writeStartElement("port");
					xml.writeTextElement("portName", dev.value().portList.at(m).portName.c_str());
					for (int i = 0; i < dev.value().portList.at(m).protList.size(); i++)
					{
						for (int i = 0; i < dev.value().portList.at(m).protList.size(); i++)
						{
							DevicDataManager::ProtStruct prot = dev.value().portList.at(m).protList.at(i);
							xml.writeStartElement("protocol");
							xml.writeTextElement("protocolName", prot.protocolName.c_str());
							xml.writeTextElement("protocolExt", prot.protocolExt.c_str());

							for (int j = 0; j < prot.messgeList.size(); j++)
							{
								DevicDataManager::MessageStruct mess = prot.messgeList.at(j);

								xml.writeStartElement("message");
								xml.writeTextElement("messageName", mess.messageName.c_str());
								xml.writeTextElement("messageP", mess.messageP.c_str());
								xml.writeTextElement("messageExt", mess.messageExt.c_str());

								for (int k = 0; k < mess.propList.size(); k++)
								{
									DevicDataManager::PropStruct prop = mess.propList.at(k);
									xml.writeStartElement("messageProp");
									xml.writeTextElement("propName", prop.propName.c_str());
									xml.writeTextElement("propStyle", prop.propStyle.c_str());
									xml.writeTextElement("propSize", QString::number(prop.propSize));
									xml.writeTextElement("propHint", prop.propHint.c_str());
									xml.writeTextElement("propExt", prop.propExt.c_str());
									xml.writeEndElement();
								}
								xml.writeEndElement();
							}
							xml.writeEndElement();
						}
						xml.writeEndElement();
						xml.writeEndDocument();
						break;
					}
				}
			}
		}
		file.close();
	}
}