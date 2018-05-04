#ifndef DEVICDATAMANAGER_H
#define DEVICDATAMANAGER_H

#include <QObject>
#include <QMap>
#include <QStringList>
class DevicDataManager : public QObject
{
	Q_OBJECT

public:
	DevicDataManager(QObject *parent);
	~DevicDataManager();
	class PropStruct{
	public:

		std::string propName;
		std::string propStyle;
		int propSize;
		std::string propHint;
		std::string propExt;
		bool operator==(const PropStruct& that)const;
	};
	class MessageStruct{
	public:
		std::string messageName;
		std::string messageP;
		std::string messageExt;
		QList<PropStruct> propList;
		bool operator==(const MessageStruct& that)const;
	};
	class ProtStruct{
	public:
		std::string protocolName;
		std::string port;
		std::string protocolExt;
		QList<MessageStruct>messgeList;
		bool operator==(const ProtStruct& that)const;
	};
	class DevStruct{
	public:
		std::string deviceName;
		std::string deviceExt;
		QList<ProtStruct> protList;
	};

public:
	QMap<QString,DevStruct> m_deviceList;

	QStringList m_devNameList;

	bool DevIsExsit(QString devName);

	QStringList GetMessagePropStringFormat(const MessageStruct msgStruct);

	void AddDev(QString devName);

	bool IsExitProt(QString devName,QString protName);

	bool IsExitMessage(QString devName,QString protName,QString messageName);

public slots:
	void UpdateAll();

	void UpdateDevName(QString oldDevName,QString newDevName);

	void UpdateExt(QString oldDevice,QString devExt);

	void UpdateMsgName(QString devName,QString protName,QString oldName,QString newName);

signals:
	void DataChanged();
};

#endif // DEVICDATAMANAGER_H
