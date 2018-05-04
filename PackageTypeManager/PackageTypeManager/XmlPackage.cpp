#include "XmlPackage.h"
#include <QFile>
#include <QDebug>

XmlPackage::XmlPackage()
{
	deviceName = "All Device";
	dataVersion = "";
}


XmlPackage::~XmlPackage()
{
}

bool XmlPackage::writeXml(QString fileName)
{
	if (fileName.isEmpty())
		return false;
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		qDebug() << "Open Error";
		return false;
	}
	writer.setDevice(&file);
	writer.setAutoFormatting(true);
	writer.writeStartDocument("1.0", true);
	writer.writeStartElement("BUSDATA");
	if (!dataVersion.isEmpty())
		writer.writeAttribute("version", dataVersion);
	if (!deviceName.isEmpty())
	{
		writer.writeStartElement("device");
		writer.writeAttribute("name", deviceName);
		writer.writeAttribute("id", QString::number(id));
		if(!byteOrder.isEmpty())
			writer.writeAttribute("byteOrder", byteOrder);
		writer.writeCharacters("");
		writer.writeEndElement();
	}
	QMapIterator<QString, int> it(types);
	while (it.hasNext()) {
		it.next();
		writer.writeStartElement("type");
		writer.writeAttribute("name", it.key());
		writer.writeAttribute("len", QString::number(it.value()));
		writer.writeCharacters("");
		writer.writeEndElement();
	}

	QVector<QString> vec;
	foreach(Package p, packages)
	{
		if (!p.head.name.isEmpty())
		{
			if (!vec.contains(p.headName))
			{
				writer.writeStartElement("head");
				writer.writeAttribute("name", p.head.name);
				foreach(Field f, p.head.field)
					writeField(f);
				writer.writeEndElement();
			}
		}

		if (p.id == -1)
		{
			writer.writeStartElement("subpackage");
			writer.writeAttribute("name", p.name);
			writer.writeAttribute("type", p.type);
			writer.writeAttribute("head", p.headName);
		}
		else
		{
			writer.writeStartElement("package");
			writer.writeAttribute("name", p.name);
			writer.writeAttribute("head", p.headName);
			writer.writeAttribute("id", QString::number(p.id));
		}
		foreach(Field f, p.field)
			writeField(f);
		if (!p.algorithm.isEmpty())
		{
			writer.writeStartElement("check");
			writer.writeAttribute("algorithm", p.algorithm);
			writer.writeCharacters("");
			writer.writeEndElement();
		}
		writer.writeEndElement();
		vec.push_back(p.headName);
	}
	writer.writeEndDocument();
	file.close();
	return true;
}

bool XmlPackage::readXml(const QString& fileName)
{
	if (fileName.isEmpty())
		return false;

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug() << "Open Error";
		return false;
	}


	xml.setDevice(&file);
	if (xml.readNextStartElement())
	{
		if (xml.attributes().value("version") == "1.0")
			beginRead();
		else
			xml.raiseError(QObject::tr("This file is not an xml version 1.0 file"));
	}
	file.close();
	set();
	return true;
}

void XmlPackage::beginRead()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "BUSDATA");
	QXmlStreamAttributes attributes = xml.attributes();
	if (attributes.hasAttribute("version"))
	{
		dataVersion = attributes.value("version").toString();
	}
	while (xml.readNextStartElement())
	{
		if (xml.name() == "device")
		{
			readDevice();
		}
		else if (xml.name() == "type")
		{
			readType();
		}
		else if (xml.name() == "head")
		{
			readHead();
		}
		else if (xml.name() == "subpackage")
		{
			readSubPackage();
		}
		else if (xml.name() == "package")
		{
			readPackage();
		}
		else
		{
			xml.skipCurrentElement();
		}
	}

}

void XmlPackage::readDevice()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "device");
	QXmlStreamAttributes attributes = xml.attributes();
	if (attributes.hasAttribute("name"))
	{
		deviceName = attributes.value("name").toString();
	}
	if (attributes.hasAttribute("id"))
	{
		id = attributes.value("id").toString().toInt();
	}
	if (attributes.hasAttribute("byteOrder"))
	{
		byteOrder = attributes.value("byteOrder").toString();
	}
	xml.skipCurrentElement();
}

void XmlPackage::readType()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "type");
	QString name;
	int len;
	QXmlStreamAttributes attributes = xml.attributes();
	if (attributes.hasAttribute("name"))
	{
		name = attributes.value("name").toString();
	}
	if (attributes.hasAttribute("len"))
	{
		len = attributes.value("len").toString().toInt();
	}
	types.insert(name, len);
	xml.skipCurrentElement();
}

void XmlPackage::readHead()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "head");
	PackageHead pHead;
	QXmlStreamAttributes attributes = xml.attributes();
	if (attributes.hasAttribute("name"))
	{
		pHead.name = attributes.value("name").toString();
	}
	while (xml.readNextStartElement())
	{
		if (xml.name() == "field")
		{
			pHead.field.append(readField());
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	headers.append(pHead);
}

void XmlPackage::readSubPackage()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "subpackage");
	Package s;
	QXmlStreamAttributes attributes = xml.attributes();
	if (attributes.hasAttribute("name"))
	{
		s.name = attributes.value("name").toString();
	}
	if (attributes.hasAttribute("type"))
	{
		s.type = attributes.value("type").toString();
	}
	if (attributes.hasAttribute("head"))
	{
		s.headName = attributes.value("head").toString();
	}
	while (xml.readNextStartElement())
	{
		if (xml.name() == "field")
		{
			s.field.append(readField());
		}
		else if (xml.name() == "checksum")
		{
			QXmlStreamAttributes a = xml.attributes();
			if (a.hasAttribute("algorithm"))
			{
				s.algorithm = a.value("algorithm").toString();
				xml.skipCurrentElement();
			}
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	packages.append(s);
}

void XmlPackage::readPackage()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "package");
	Package s;
	QXmlStreamAttributes attributes = xml.attributes();
	if (attributes.hasAttribute("head"))
	{
		s.headName = attributes.value("head").toString();
	}
	if (attributes.hasAttribute("name"))
	{
		s.name = attributes.value("name").toString();
	}
	if (attributes.hasAttribute("id"))
	{
		s.id = attributes.value("id").toString().toInt();
	}

	while (xml.readNextStartElement())
	{
		if (xml.name() == "field")
		{
			s.field.append(readField());
		}
		else if (xml.name() == "checksum")
		{
			QXmlStreamAttributes a = xml.attributes();
			if (a.hasAttribute("algorithm"))
			{
				s.algorithm = a.value("algorithm").toString();
				xml.skipCurrentElement();
			}
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	packages.append(s);
}

void XmlPackage::writeField(Field f)
{
	writer.writeStartElement("field");
	writer.writeAttribute("name", f.name);
	if(f.type != "uint8")
		writer.writeAttribute("type", f.type);
	if(f.array != "")
		writer.writeAttribute("array", f.array);
	if (f.subField.size() > 0)
		foreach(SubField sub, f.subField)
		writeSubField(sub);
	else
		writer.writeCharacters("");
	writer.writeEndElement();
}

void XmlPackage::writeSubField(SubField sub)
{
	writer.writeStartElement("subfield");
	writer.writeAttribute("name", sub.name);
	writer.writeAttribute("index", QString::number(sub.index));
	writer.writeAttribute("len", QString::number(sub.len));
	writer.writeCharacters("");
	writer.writeEndElement();
}

Field XmlPackage::readField()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "field");
	Field f;
	QXmlStreamAttributes attributes = xml.attributes();
	if (attributes.hasAttribute("name"))
	{
		f.name = attributes.value("name").toString();
	}
	if (attributes.hasAttribute("type"))
	{
		f.type = attributes.value("type").toString();
	}
	if (attributes.hasAttribute("array"))
	{
		f.array = attributes.value("array").toString();
	}
	if (attributes.hasAttribute("value"))
	{
		f.value = attributes.value("array").toString().toDouble();
	}
	while (xml.readNextStartElement())
	{
		if (xml.name() == "subfield")
		{
			f.subField.append(readSubField());
		}
		else
		{
			xml.skipCurrentElement();
		}
	}
	return f;
}

SubField XmlPackage::readSubField()
{
	Q_ASSERT(xml.isStartElement() && xml.name() == "subfield");
	SubField sub;
	QXmlStreamAttributes attributes = xml.attributes();
	if (attributes.hasAttribute("name"))
	{
		sub.name = attributes.value("name").toString();
	}
	if (attributes.hasAttribute("index"))
	{
		sub.index = attributes.value("index").toString().toInt();
	}
	if (attributes.hasAttribute("len"))
	{
		sub.len = attributes.value("len").toString().toInt();
	}
	xml.skipCurrentElement();
	return sub;
}

void XmlPackage::test()
{
	qDebug() << deviceName << "," << id << "," << byteOrder;

	foreach(Package p, packages)
	{
		PackageHead h = p.head;
		qDebug() << h.name;
		foreach(Field f, h.field)
		{
			qDebug() << f.name << "," << f.array << "," << f.type << "," << f.value;
		}

		qDebug() << p.name << "," << p.headName << "," << p.id << p.type;
		foreach(Field f, p.field)
		{
			qDebug() << f.name << "," << f.array << "," << f.type << "," << f.value;
			if (f.subField.size() > 0)
			{
				foreach(SubField sub, f.subField)
				{
					qDebug() << sub.name << "," << sub.index << "," << sub.len;
				}
			}
		}
		qDebug() << p.algorithm;
	}
}

void XmlPackage::set()
{
	for (int i = 0; i < packages.size(); i++)
	{
		for (int j = 0; j < headers.size(); j++)
		{
			if (packages.at(i).headName == headers.at(j).name)
				packages[i].head = headers[j];
		}
	}
}
