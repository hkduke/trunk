#include <iostream>
#include <vector>
#include <QFileDialog>
#include "NodeDiscoverTest.h"
#include "../NetCommunication/Core/Framework.h"
#include "../NetCommunication/TCPTransport/TCPTransport.h"
#include "../NetCommunication/Core/MessageTransePack.h"
#include "../Core/UserInterface.h"
#include "../Core/LogManager.h"
#include "SendData.h"
#include"../Core/FilePack.h"
std::vector<NetCom::Any> vec;
NetCom::SendData m_pSendData(&vec);
using namespace NetCom;
TCPTransport tcp;
bool m_isEnableStart = false;
namespace NetCom
{

void NodeJion(void*)
{
	tcp.Init();

	TCPTransport::IpaddressSet& ipset = tcp.GetIpaddressSet();
	m_pSendData.m_ipset = &ipset;
}
}

NodeDiscoverTest::NodeDiscoverTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Framework::GetInstance().Init();
	Framework::GetInstance().GetNodeDiscover()->RegisterHandle(NetCom::NodeJion);
	connect(ui.m_pushButton, SIGNAL(clicked()), this, SLOT(OnPushButtonDown()));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(OnSendFile()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(OnTest()));
	if (!m_isEnableStart)
	{
		m_isEnableStart = true;
		Thread* t1 = new Thread;
		RunnableAdapter<SendData> *m_runnable = new RunnableAdapter<SendData>(m_pSendData, &SendData::run);
		LogManager::GetInstance().WriteMessage("开启发送数据线程:线程Id=%d", t1->id());
		t1->start(*m_runnable);
	}

}

void NodeDiscoverTest::OnPushButtonDown()
{
	int x=ui.lineEdit_X->text().toInt();
	int Y = ui.lineEdit_Y->text().toInt();
	int z = ui.lineEdit_Z->text().toInt();
	vec.clear();
	vec.push_back(x);
	vec.push_back(Y);
	vec.push_back(z);
	m_pSendData.m_isStop = false;
// 	std::string str("hellofdfad");
// 	Framework::GetInstance().GetTransportStratagy()->Send((UInt8*)str.data(), str.length());
	
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
	QByteArray array= file.readAll();
	FilePack::GetFilePackages((void*)array.constData(), file.size(), file.fileName().toStdString().c_str(), 0);
	file.close();
}
