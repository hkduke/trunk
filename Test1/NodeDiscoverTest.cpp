#include <iostream>
#include <vector>
#include <QtWidgets/QFileDialog>
#include "NodeDiscoverTest.h"
#include "../NetCommunication/Core/Framework.h"
#include "../NetCommunication/TCPTransport/TCPTransport.h"
#include "../NetCommunication/Core/MessageTransePack.h"
#include "../Core/UserInterface.h"
#include "../Core/LogManager.h"
#include "SendData.h"
#include"../Core/FilePack.h"
#include <QSettings>
#include <QDebug>
#include <QFileInfo>
#include "../Communication/BlendModeNet.h"
std::vector<NetCom::Any> vec;
NetCom::SendData m_pSendData(&vec);
using namespace NetCom;
TCPTransport tcp;
bool m_isEnableStart = /*false*/ true;

QString g_contents;

namespace NetCom
{

	void NodeJion(void*)
	{
		tcp.Init();

		TCPTransport::IpaddressSet& ipset = tcp.GetIpaddressSet();
		m_pSendData.m_ipset = &ipset;
	}
}

using namespace NetCom;

QString getValue(const QString &ftype, Any value)
{
	QString valueStr;
	if (!value.empty())
	{
		if (ftype == "uint16")
		{
			valueStr.setNum(AnyCast<UInt16>(value));
		}
		else if (ftype == "uint32")
		{
			valueStr.setNum(AnyCast<UInt32>(value));
		}
		else if (ftype == "uint8")
		{
			valueStr.setNum(AnyCast<UInt8>(value));
		}
		else if (ftype == "int32")
		{
			valueStr.setNum(AnyCast<Int32>(value));
		}
		else if (ftype == "int16")
		{
			valueStr.setNum(AnyCast<Int16>(value));
		}
		else if (ftype == "int8")
		{
			valueStr.setNum(AnyCast<Int8>(value));
		}
		else if (ftype == "int64")
		{
			valueStr.setNum(AnyCast<Int64>(value));
		}
		else if (ftype == "uint64")
		{
			valueStr.setNum(AnyCast<UInt64>(value));
		}
		else if (ftype == "bool")
		{
			valueStr.setNum(AnyCast<bool>(value));
		}
		else
		{
			valueStr = "";
		}
	}
	return valueStr;
}

NodeDiscoverTest::NodeDiscoverTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	resize(1000, 600);
	Framework::GetInstance().Init();
	Framework::GetInstance().GetNodeDiscover()->RegisterHandle(NetCom::NodeJion);
	if (!m_isEnableStart)
	{
		m_isEnableStart = true;
		Thread* t1 = new Thread;
		RunnableAdapter<SendData> *m_runnable = new RunnableAdapter<SendData>(m_pSendData, &SendData::run);
		LogManager::GetInstance().WriteMessage("开启发送数据线程:线程Id=%d", t1->id());
		t1->start(*m_runnable);
	}

	m_packManager = new PackManager;
	m_packManager->m_currentPackage;
	m_packManager->RegisterFunction(&NodeDiscoverTest::recv);
	int topicID = Framework::GetInstance().ConfigInt("TopicID");
	m_packManager->Fill(topicID);

	m_timer = new QTimer(this);
	m_timer->setInterval(500);
	m_timer->start();
	connect(m_timer, &QTimer::timeout, [&]() {
		ui.tbRecv->clear();
		ui.tbRecv->append(g_contents);
	});

	m_cycalTimer = new QTimer(this);
	connect(m_cycalTimer, &QTimer::timeout, this, &NodeDiscoverTest::on_btnSend_clicked);

	initTableWidget();

	connect(ui.tableWidget, &QTableWidget::itemChanged, this, &NodeDiscoverTest::onItemChenged);
}

void NodeDiscoverTest::recv(BasePackage* parement)
{
	static int cnt = 0;
	//ui.tbRecv->clear();
	//获取所有字段
	g_contents.append(QString("====================%1=================\n").arg(cnt++));
	g_contents.append(QString("%1	%2	%3").arg("field").arg("type").arg("size"));
	std::vector<std::string> vecstr = parement->getAllFieldName();
	LogManager::GetInstance().WriteMessage("PackManager::Parse ParsePackID:%d\n", (int)parement->getID());
	for (int i = 0; i < vecstr.size(); i++)
	{
		NetCom::Any value = parement->getValue(vecstr[i]);
		std::string fieldtype = parement->getType(vecstr[i]);
		QString ftype = QString::fromLocal8Bit(fieldtype.c_str());
		g_contents.append(QStringLiteral("%1	%2\n").arg(QString::fromLocal8Bit(vecstr[i].c_str())).arg(getValue(ftype, value)));
	}
}

void NodeDiscoverTest::on_btnSend_clicked()
{

	static int cnt = 0;
	ui.tbSend->append(QString("=====================%1======================\n").arg(cnt++));
	ui.tbSend->append(QString("%1	%2	%3").arg("field").arg("type").arg("size"));
	int length = 1000;
	UInt8 * data = (UInt8*)m_packManager->GetData();
	int ret = Framework::GetInstance().GetTransportStratagy()->Send((UInt8*)m_packManager->GetData(), m_packManager->GetPackLenth());
	BlendModeNet * ptr = Framework::GetInstance().GetBlendModeNet();
	if (ptr)
	{
		ptr->Send(data, length);
	}

	if (ret == -1)
	{
		ui.tbSend->append("发送失败");
	}
	int row = 0;
	auto vecstr = m_packManager->m_currentPackage.getAllFieldName();

	for (int i = 0; i < vecstr.size(); i++)
	{
		QString field = QStringLiteral("%1").arg(QString::fromLocal8Bit(vecstr[i].c_str()));
		std::string fieldtype = m_packManager->m_currentPackage.getType(vecstr[i]);
		QString ftype = QString::fromStdString(fieldtype);
		Any value = m_packManager->GetFiledValue(vecstr[i]);
		QString printStr = QString("%1	%2	%3").arg(field).arg(ftype).arg(getValue(ftype, value));
		ui.tbSend->append(printStr);
	}
}

void NodeDiscoverTest::on_btnSelectFile_clicked()
{
	QSettings settings;
	QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("选择文件"), settings.value("LastPath", "/home").toString());
	if (fileName.isEmpty()) return;
	settings.setValue("LastPath", fileName);
	m_file = fileName;
	ui.edtPath->setText(fileName);
}

void NodeDiscoverTest::on_btnSendFile_clicked()
{
	QFile file(m_file);
	file.open(QIODevice::ReadOnly);
	QByteArray array = file.readAll();Timestamp stemp1;
	QFileInfo info(file.fileName());
	std::vector<FilePack*> vecpack = FilePack::GetFilePackages((void*)array.constData(), file.size(), info.fileName().toStdString().c_str(), 0);
	int stdi = 0;
		std::cout << __FUNCTION__ << ":::" << (int)stemp1.elapsed() << std::endl;
	for (int i = 0; i < vecpack.size(); i++)
	{
		//Timestamp stemp;
		//Thread::trySleep(200);
		FilePack* pack = vecpack[i];
		void  * data = pack->GetData();
		//std::cout << data << std::endl;
		int len = pack->GetLenth();
		//std::cout << ToolClass::GetPacketSize(data) << std::endl;

		Framework::GetInstance().GetTransportStratagy()->Send((UINT8*)pack->GetData(), len, TransactionType_File);
		//std::cout << __FUNCTION__<<":::"<<(int)stemp.elapsed() << std::endl;
		//FilePack pack1;
		//pack1.ParseFile(data);
		//file->PushFrameObj(pack1.GetData(), pack1.GetLenth(), pack1.GetFileSerial(data), map);
		//stdi += pack1.GetLenth();
		//LogManager::GetInstance().WriteMessage("SendData::run 发送的包序号为%d",(int)pack->GetFileSerial(data));
	}

	file.close();
}

void NodeDiscoverTest::on_cbCycle_stateChanged(int state)
{
	switch (state)
	{
	case Qt::Checked:
		m_cycalTimer->setInterval(ui.edtStep->text().toInt());
		m_cycalTimer->start();
		break;
	case Qt::Unchecked:
		m_cycalTimer->stop();
		break;
	default:
		break;
	}
}

void NodeDiscoverTest::OnSendFile()
{
	m_file = QFileDialog::getOpenFileName(this,
		tr("Open File"), "", tr("All File (*.*)"));
	if (!m_file.isEmpty())
	{
		m_pSendData.m_file = m_file.toStdString();
	}
}
#include "../Communication/NodeDirectoryWriteHandle.h"
void NodeDiscoverTest::OnTest()
{
	QFile file("css.chm");
	file.open(QIODevice::ReadOnly);
	QByteArray array = file.readAll();
	FilePack::GetFilePackages((void*)array.constData(), file.size(), file.fileName().toStdString().c_str(), 0);
	file.close();
}

void NodeDiscoverTest::onItemChenged(QTableWidgetItem * item)
{
	int row = item->row();
	QString feild = ui.tableWidget->item(row, 0)->text();
	QString ftype = ui.tableWidget->item(row, 1)->text();
	int value = item->text().toInt();
	int size = 0;

	QString valStr;
	if (ftype == "uint32")
	{
		size = sizeof(UInt32);
		m_packManager->SetFiledValue(feild.toLocal8Bit().data(), UInt32(value));
		Any val = m_packManager->GetFiledValue(feild.toLocal8Bit().data());
		if (!val.empty())
		{
			valStr = QString::number(AnyCast<UInt32>(val));
		}
	}
	else if (ftype == "uint16")
	{
		size = sizeof(UInt16);
		m_packManager->SetFiledValue(feild.toLocal8Bit().data(), UInt16(value));
		Any val = m_packManager->GetFiledValue(feild.toLocal8Bit().data());
		if (!val.empty())
		{
			valStr = QString::number(AnyCast<UInt16>(val));
		}
	}
	else if (ftype == "uint8")
	{
		size = sizeof(UInt8);
		m_packManager->SetFiledValue(feild.toLocal8Bit().data(), UInt8(value));
		std::string feildStr = feild.toLocal8Bit().data();
		Any val = m_packManager->GetFiledValue(feildStr);
		if (!val.empty())
		{
			valStr = QString::number(AnyCast<UInt8>(val));
		}
	}
	else if (ftype == "int32")
	{
		size = sizeof(Int32);
		m_packManager->SetFiledValue(feild.toLocal8Bit().data(), Int32(value));
		std::string feildStr = feild.toLocal8Bit().data();
		Any val = m_packManager->GetFiledValue(feildStr);
		if (!val.empty())
		{
			valStr = QString::number(AnyCast<Int32>(val));
		}
	}
	else if (ftype == "uint64")
	{
		size = sizeof(UInt64);
		m_packManager->SetFiledValue(feild.toLocal8Bit().data(), UInt64(value));
		std::string feildStr = feild.toLocal8Bit().data();
		Any val = m_packManager->GetFiledValue(feildStr);
		if (!val.empty())
		{
			valStr = QString::number(AnyCast<UInt64>(val));
		}
	}
	else if (ftype == "int64")
	{
		size = sizeof(Int64);
		m_packManager->SetFiledValue(feild.toLocal8Bit().data(), Int64(value));
		std::string feildStr = feild.toLocal8Bit().data();
		Any val = m_packManager->GetFiledValue(feildStr);
		if (!val.empty())
		{
			valStr = QString::number(AnyCast<Int64>(val));
		}
	}
	QByteArray ba;
	memcpy(ba.data(), &value, size);
	qDebug() << valStr;

}

void NodeDiscoverTest::initTableWidget()
{
	QStringList labels;
	labels << "field" << "type" << "value";
	ui.tableWidget->setHorizontalHeaderLabels(labels);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget->verticalHeader()->setDefaultSectionSize(30);
	ui.tableWidget->verticalHeader()->setCascadingSectionResizes(true);
	ui.tableWidget->verticalHeader()->setHighlightSections(true);
	ui.tableWidget->setColumnCount(labels.count());
	ui.tableWidget->setHorizontalHeaderLabels(labels);
	ui.tableWidget->setAlternatingRowColors(true);


	int row = 0;
	auto vecstr = m_packManager->m_currentPackage.getAllFieldName();

	for (int i = 0; i < vecstr.size(); i++)
	{
		std::string fieldtype = m_packManager->m_currentPackage.getType(vecstr[i]);
		QString ftype = QString::fromStdString(fieldtype);
		ui.tableWidget->insertRow(row);
		QTableWidgetItem * item = new QTableWidgetItem(QStringLiteral("%1").arg(QString::fromLocal8Bit(vecstr[i].c_str())));
		ui.tableWidget->setItem(row, 0, item);
		item = new QTableWidgetItem(QString::fromStdString(fieldtype));
		ui.tableWidget->setItem(row, 1, item);

		Any value = m_packManager->GetFiledValue(vecstr[i]);
		QString val = getValue(ftype, value);
		item = new QTableWidgetItem(val);
		item->setData(Qt::UserRole, QVariant(0));
		ui.tableWidget->setItem(row, 2, item);
		if (ftype.isEmpty())
		{
			continue;
		}
	}
}
