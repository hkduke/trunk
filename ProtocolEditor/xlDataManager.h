#pragma once
#include <QList>
#include <QStringList>
#include <QObject>
#include<QMap>
//XML数据管理
class xlDataManager:public QObject
{
	Q_OBJECT
public:
	xlDataManager(QObject* parent=nullptr);
	~xlDataManager(void);
	enum prot
	{protocol,protocolName,message,messageName,messageExt,
	messagePro,propName,propStyle,propSize,propHint,propExt,protEnd
	};
	//属性结构
	class PropStruct{
	public:
		std::string propName;
		std::string propStyle;
		int propSize;
		std::string propHint;
		std::string propExt;
	};
	class ProtStruct
	{
	public:
		std::string ProtName;
		std::string ProtExt;
		QList<std::string> messages; 
	};
	//报文结构
	class MessageStruct{
	public:
		std::string messageName;
		std::string messageExt;
		QList<PropStruct> propList;
	};


	QMap<QString,MessageStruct> messageList;

	QStringList messageNameList;

	QMap<QString,ProtStruct> protList;


	QStringList m_protStrList;
private:

	QString m_versionInfor;

	bool m_isDirty;
public:

	bool MessageIsExsit(QString messageN);

	bool ProtocolIsExsit(QString protN);

	void updateMessageTreeOnly(QString oldMessageName,QString NewMessageExt);

	void updataProtocol_ProtocolName(QString oldProtocolName,QString newProtocolName);

	QStringList GetMessagePropStringFormat(QString messageNamestr);

	void UpDataProtocol();

	void protListChangeds();

	QString GetVersionInfo();

	void SetVersionInfo(QString versionIn);

	bool IsDirty();

	void ResetDirtyState();

	void SetDirty();

	public slots:

		void addMessage();

		void addProtocol();

		void delMessage(QString structName);


		void updataMessage_messageName(QString oldMessageName,QString newMessageName);

signals:

		void messageChanged();

		void ProtChanged();

		void ProtMessageNameChanged();

		void protListChanged();
private:
	void ReplaceProtData(QString oldMessageName, QString newMessageName);

};

