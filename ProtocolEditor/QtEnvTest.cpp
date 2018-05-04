/*
	���ļ�Ϊ�������ļ�����������Ҫ�У�
*/

#include "qtenvtest.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "readDeviceXml.h"
#include "xmlwriter.h"
#include <assert.h>
/*
	���ܣ����캯��
	��Ҫ��;���Ը���Ա������ʼ�������ó�ʼ��������UI��ص���ʾ�������źŲ۵�����
*/
QtEnvTest::QtEnvTest(QWidget *parent)
	: QMainWindow(parent),m_popMenu(new QMenu(this)),
	messageEditor(new MessageEditorWidget(this)),
	deviceManager(new DeviceManagerWidget(this)),
	protocolManager(new ProtocolManagerWidget(this)),
	m_dataManager(new xlDataManager(this))
{
	ui.setupUi(this);
	isNewOpen=true;
	isMsgFirst=true;
	this->clearWidget();
	this->setWindowTitle(QString::fromLocal8Bit("���Э����ƹ���"));
	
	ui.horizontalLayout_ProtManager->addWidget(messageEditor);
	messageEditor->show();
	ui.m_horizontalLayout_dev->addWidget(deviceManager);
	deviceManager->show();

	ui.m_treeWidget_protManager->header()->setHidden(true);
	ui.m_treeWidget_devManager->header()->setHidden(true);
	ui.m_treeWidget_devManager->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	on_trigger_open();
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.m_treeWidget_messageManager->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.m_treeWidget_protManager->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.m_treeWidget_devManager->setContextMenuPolicy(Qt::CustomContextMenu);
	creatContexMenuAction();
	SetSlot();
	m_deviceDataManager = NULL;

}
/*
	���ܣ���������
*/
QtEnvTest::~QtEnvTest()
{
}
/*
	���ܣ���Action�ۺ���
	�������״δ����ʱ��Ĭ�ϴ�ģ���ļ�"./elCD.XML"�����ģ�岻���ڻ�򿪴������½�һ����ģ��
*/
void QtEnvTest::on_trigger_open()
{
	QString fileName;
	if(!isNewOpen)
	{

		fileName =  QFileDialog::getOpenFileName(this,tr("Open File"), ".", tr("xml Files (*.xml)"));
		if(fileName.isEmpty())
		{
			return;
		}
	}
	else
	{
		isNewOpen=false;
		fileName="./elCD.XML";
	}

	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
	{

		if(fileName=="./elCD.XML")
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("�ļ�����ʾ"),
				QString::fromLocal8Bit("Ĭ��ģ��Э���ļ�%1���ܴ�\n%2").
				arg(fileName).arg(file.errorString()));
			OpenEmptyManager();
		}
		else
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("�ļ�����ʾ"),
				QString::fromLocal8Bit("���ܴ�%1:\n%2").
				arg(fileName).arg(file.errorString()));
		}
		return;
	}
	if(!m_dataManager->protList.isEmpty())
	{
		if(QMessageBox::Yes==QMessageBox::question(this, QString::fromLocal8Bit("�ļ�����ʾ"), 
			QString::fromLocal8Bit("�Ƿ񱣴����޸ĵ��ļ�"),QMessageBox::Yes,QMessageBox::No))
		{
			QString msg=messageEditor->GetCurrentMessageName();
			if(!msg.isEmpty())
			{
				messageEditor->on_saveModel();
			}
			on_trigger_save();
		}
		else
		{
			return;
		}
	}
	ui.m_treeWidget_devManager->clear();
	ui.m_treeWidget_protManager->clear();
	ui.m_treeWidget_messageManager->clear();
	messageEditor->clear();
	protocolManager->clear();
	deviceManager->clear();
	m_dataManager = new xlDataManager(this);
	xlReader reader;
	reader.setxlDataManager(m_dataManager);

	if(!reader.read(&file))
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("�ļ�����ʾ"),
			QString::fromLocal8Bit("���ܴ�%1:\n%2").
			arg(fileName).arg(reader.errorString()));
		return;
	}
	else
	{
		statusBar()->showMessage(QString::fromLocal8Bit("�ļ��򿪳ɹ�"),2000);
	}
	file.close();
	setProtList();
	setMessageList();
	messageEditor->setDataManager(m_dataManager);
	protocolManager->SetDataManager(m_dataManager);
	ui.tabWidget->setCurrentIndex(0);
	ui.m_lineEdit_VersionInfor->setText(m_dataManager->GetVersionInfo());
	m_dataManager->ResetDirtyState();
	connect(m_dataManager,SIGNAL(messageChanged()),this,SLOT(setMessageList()));
	connect(m_dataManager,SIGNAL(ProtMessageNameChanged()),this,SLOT(setProtList()));
	connect(m_dataManager,SIGNAL(ProtChanged()),this,SLOT(setProtList()));
	connect(m_dataManager,SIGNAL(protListChanged()),this,SLOT(setProtList()));
	connect(protocolManager,SIGNAL(GotoMessageEditor(QString)),this,SLOT(OnGotoMessageEditor(QString)));

}
/*
	���ܣ�Э�鱣��ۺ���

*/
void QtEnvTest::on_trigger_save()
{
	xlWriter writer;
	if(!messageEditor->IsDeviceData())
	{	
		messageEditor->on_saveModel();
	}
	writer.setDataManager(m_dataManager);
	writer.saveData();
	m_dataManager->ResetDirtyState();
}
/*
	���ܣ��豸�򿪲ۺ���
*/
void QtEnvTest::on_trigger_deviceOpen()
{
	//�򿪴��ļ��Ի����������Ϊ�գ����˳�
	QString fileName =  QFileDialog::getOpenFileName(this,tr("Open File"), ".", tr("xml Files (*.xml)"));
	if(fileName.isEmpty())
	{
		return;
	}
	//�����豸���ؼ�
	ui.m_treeWidget_devManager->clear();
	//�����ʧ�ܣ��򷵻�
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("�ļ�����ʾ"),
			QString::fromLocal8Bit("���ܴ�%1:\n%2").
			arg(fileName).arg(file.errorString()));
		return;
	}
	//�����豸���ݹ������������豸��Ϣ
	m_deviceDataManager = new DevicDataManager(this);

	readDeviceXml reader;
	reader.setxlDataManager(m_deviceDataManager);
	if(!reader.read(&file))
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("�ļ�����ʾ"),
			QString::fromLocal8Bit("���ܴ�%1:\n%2").
			arg(fileName).arg(reader.errorString()));
		return;
	}
	else
	{
		statusBar()->showMessage(QString::fromLocal8Bit("�ļ��򿪳ɹ�"),2000);
	}
	file.close();
	setDeviceList();
	ui.tabWidget->setCurrentIndex(1);
	connect(m_deviceDataManager,SIGNAL(DataChanged()),this,SLOT(setDeviceList()));
	connect(m_deviceDataManager,SIGNAL(DataChanged()),deviceManager,SLOT(UpDateWidget()));

}
/*
���ܣ��豸�ڵ�Э�鱣��ۺ���

*/
void QtEnvTest::on_trigger_deviceSave()
{
	if (m_deviceDataManager == NULL)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("û�����ݱ���"), QMessageBox::Ok);
		return;
	}

	xmlWriter writer;
	writer.setDataManager(m_deviceDataManager);
	if(messageEditor->IsDeviceData())
	{	
		messageEditor->on_saveModel();
	}
	writer.saveData();
}


//�źŲ۹���
void QtEnvTest::SetSlot()
{
	connect(ui.m_action_save,SIGNAL(triggered()),this,SLOT(on_trigger_save()));
	connect(ui.m_action_open,SIGNAL(triggered()),this,SLOT(on_trigger_open()));
	connect(ui.m_action_deviceOpen,SIGNAL(triggered()),this,SLOT(on_trigger_deviceOpen()));
	connect(ui.m_action_deviceSave,SIGNAL(triggered()),this,SLOT(on_trigger_deviceSave()));
	connect(ui.m_treeWidget_messageManager,SIGNAL(customContextMenuRequested(QPoint)),
		this,SLOT(on_slot_messageManager(QPoint)));
	//�����źźͲ�Ϊ�϶�Э��������ı�ǩҳ���Է����������
	connect(ui.m_treeWidget_protManager, &ProtocolNoReceiveTreeWidget::ItemMoving, [&]() {
		ui.tabWidget->setCurrentIndex(1);
		//ui.horizontalLayout_ProtManager->addWidget(deviceManager);
	});
	//�����źźͲ�Ϊ�����汾�ŵĹ���
	connect(ui.m_lineEdit_VersionInfor, &QLineEdit::editingFinished, [&] {
		if (ui.m_lineEdit_VersionInfor->text().isEmpty())
		{
			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�汾��Ϣ����Ϊ��"));
			ui.m_lineEdit_VersionInfor->setFocus();
			return;
		}
		if (m_dataManager)
		{
			m_dataManager->SetVersionInfo(ui.m_lineEdit_VersionInfor->text().trimmed());
		}
	});
	
	connect(m_action_addNewMessage,SIGNAL(triggered()),this,SLOT(on_addNewMessage()));
	connect(m_action_deleteMessage,SIGNAL(triggered()),this,SLOT(on_delMessage()));
	connect(m_action_editMessage,SIGNAL(triggered()),this,SLOT(on_editMessage()));
	connect(m_action_addNewProtocol,SIGNAL(triggered()),this,SLOT(on_addNewProtocol()));
	connect(m_action_deleteProtocol,SIGNAL(triggered()),this,SLOT(on_delProtocol()));
	connect(m_action_editProtocol,SIGNAL(triggered()),this,SLOT(on_editProtocol()));
	connect(ui.m_treeWidget_protManager,SIGNAL(customContextMenuRequested(QPoint)),
		this,SLOT(on_slot_ProtocolManager(QPoint)));
	connect(ui.m_treeWidget_devManager,SIGNAL(customContextMenuRequested(QPoint)),
		this,SLOT(on_slot_Device(QPoint)));
	connect(ui.tabWidget,SIGNAL(currentChanged(int)),this,SLOT(OnTabChanged(int)));
	connect(m_action_addDevice,SIGNAL(triggered()),this,SLOT(on_addDevice()));
	connect(m_action_editDevice,SIGNAL(triggered()),this,SLOT(on_editDevice()));
	connect(m_action_deleteDevice,SIGNAL(triggered()),this,SLOT(on_deleteDevice()));
	connect(m_action_portAdd, SIGNAL(triggered()), this, SLOT(OnPortNew()));
	connect(ui.m_treeWidget_protManager,SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),this,SLOT(on_editProtocol()));
	connect(ui.m_treeWidget_messageManager,SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),this,SLOT(on_editMessage()));
	connect(ui.m_treeWidget_devManager,SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),this,SLOT(on_editDevice()));
	connect(deviceManager,SIGNAL(DoubleClicked(QString,QString,QString)),this,SLOT(OnEditDevMsg(QString,QString,QString)));
	connect(ui.m_actionWord,SIGNAL(triggered()),this,SLOT(on_trigger_saveWord()));
	connect(m_actin_saveSignal, SIGNAL(triggered()), this, SLOT(OnSaveSignalDev()));
	
}
//�򿪿�ģ��
void QtEnvTest::OpenEmptyManager()
{
	m_dataManager = new xlDataManager(this);

	setProtList();
	setMessageList();
	connect(m_dataManager,SIGNAL(messageChanged()),this,SLOT(setMessageList()));
	connect(m_dataManager,SIGNAL(ProtMessageNameChanged()),this,SLOT(setProtList()));
	connect(m_dataManager,SIGNAL(ProtChanged()),this,SLOT(setProtList()));
	connect(m_dataManager,SIGNAL(protListChanged()),this,SLOT(setProtList()));
	connect(protocolManager,SIGNAL(GotoMessageEditor(QString)),this,SLOT(OnGotoMessageEditor(QString)));
}
//���ؿؼ�
void QtEnvTest::clearWidget()
{
	protocolManager->setHidden(true);
	messageEditor->setHidden(true);
}
/*
	�˺���Ϊ����رյ��¼���д
*/
void QtEnvTest::closeEvent(QCloseEvent *event)
{
	messageEditor->on_saveModel();
	if (m_dataManager)
	{
		if (QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ")
			, QString::fromLocal8Bit("Э��δ���棬�Ƿ񱣴�"),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
		{
			on_trigger_save();
		}
	}
	if (m_deviceDataManager)
	{
		if (QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ")
			, QString::fromLocal8Bit("�豸Э��δ���棬�Ƿ񱣴�"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
		{
				on_trigger_deviceSave();
		}
	}
	return QMainWindow::closeEvent(event);
}

//������Ϣ�޸ĺ���ô˲ۺ���
void QtEnvTest::OnGotoMessageEditor(QString str)
{
	clearWidget();
	ui.horizontalLayout_ProtManager->addWidget(messageEditor);
	messageEditor->show();
	messageEditor->upDateTreeView(str);
	//protocolManager->upDateTreeView();
}
//˫���豸�������Ҽ�����༭�����ô˲ۺ���
void QtEnvTest::OnEditDevMsg(QString devName,QString protName,QString msgName)
{
	ui.tabWidget->setCurrentIndex(0);

	if(!messageEditor->on_saveModel())
	{
		return;
	}
	messageEditor->SetDevManager(m_deviceDataManager);
	//�ȴ��޸�
	messageEditor->UpdateDevDate(devName,"",protName,msgName);
}

//�����豸�����Ϣ���ļ�
void QtEnvTest::OnSaveSignalDev()
{
	//���Item �����ڻ���Э�� ���򷵻�
	if (ui.m_treeWidget_devManager->currentIndex().row() == -1
		|| ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "protocolName")
	{
		return;
	}
	//������豸���ƣ��򱣴浥���豸������
	else if (ui.m_treeWidget_devManager->currentItem()->data(0,Qt::UserRole).toString()=="deviceName")
	{
		if (m_deviceDataManager == NULL)
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("û�����ݱ���"), QMessageBox::Ok);
			return;
		}

		xmlWriter writer;
		writer.setDataManager(m_deviceDataManager);
		if (messageEditor->IsDeviceData())
		{
			messageEditor->on_saveModel();
		}
		writer.saveData(ui.m_treeWidget_devManager->currentItem()->text(0));
	}
	//����Ǹ�Ŀ¼���򱣴�ȫ���豸Ŀ¼
	else if (ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "")
	{
		on_trigger_deviceSave();
	}
}
//�����¶˿�
void QtEnvTest::OnPortNew()
{
	//��⵱ǰѡ����ǲ����豸,����ǽ�����һ������
	if (ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "deviceName")
	{
		QString deviceName = ui.m_treeWidget_devManager->currentItem()->text(0);
		//����豸����Ϊ���򲻴���
		if (deviceName.isEmpty())
		{
			return;
		}
		//����һ���˿ڶ��󣬼�����ָ���豸�У��˿ڼ���ǰ�ȼ���Ƿ�˿��Ѿ����ڣ�������ڣ�����ʾ
		assert(m_deviceDataManager->DevIsExsit(deviceName));
		if (m_deviceDataManager->IsExitPort(deviceName, "default"))
		{
			QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), 
				QString::fromLocal8Bit("��༭�޸�ǰ�������˿ڵ����ƺ��ټ�������Ŀ"));
			return;
		}
		DevicDataManager::PortStruct tempPortStruct;
		tempPortStruct.portName = "default";
		tempPortStruct.protList.clear();
		m_deviceDataManager->m_deviceList[deviceName].portList << tempPortStruct;
		m_deviceDataManager->UpdateAll();
	}

}
//�༭�˿�����
void QtEnvTest::OnPortEditor()
{

}
//ɾ���˿�
void QtEnvTest::OnPortDel()
{

}
//�ڱ���treeWdiget���Ҽ�ʱ�����˲˵�
bool QtEnvTest::on_slot_messageManager(QPoint point)
{
	if (!ui.m_treeWidget_messageManager->itemAt(point))
	{
		return false;
	}
	m_popMenu->clear();
	m_popMenu->addAction(m_action_addNewMessage);
	m_popMenu->addAction(m_action_editMessage);
	m_popMenu->addAction(m_action_deleteMessage);
	m_popMenu->exec(QCursor::pos());
	return true;
}
//���豸treeWidget�Ҽ����ʱ�����˵�
bool QtEnvTest::on_slot_Device(QPoint point)
{
	//���û��Item
	if (!ui.m_treeWidget_devManager->itemAt(point))
	{
		return false;
	}	
	//��յ����˵�
	m_popMenu->clear();
	//���Item�Ƕ˿�
	if (ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "port")
	{

		m_popMenu->addAction(m_action_portEditor);
		m_popMenu->addAction(m_action_portDel);
	}
	//���ITem���豸��
	else if (ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "deviceName")
	{

		m_popMenu->addAction(m_action_editDevice);
		m_popMenu->addAction(m_action_deleteDevice);
		m_popMenu->addAction(m_action_portAdd);
		m_popMenu->addAction(m_actin_saveSignal);
	}
	//����
	else if(ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "")
	{
		m_popMenu->addAction(m_action_addDevice);
		m_popMenu->addAction(m_actin_saveSignal);
	}
	else
	{
		m_popMenu->addAction(m_action_devProtDel);
	}
	m_popMenu->exec(QCursor::pos());
	return true;
}
//�����Ҽ������˵�
void QtEnvTest::creatContexMenuAction()
{
	m_action_addNewMessage = new QAction(QString::fromLocal8Bit("�½�����"),this);

	m_action_editMessage = new QAction(QString::fromLocal8Bit("�༭����"),this);

	m_action_deleteMessage = new QAction(QString::fromLocal8Bit("ɾ������"),this);

	m_action_addNewProtocol=new QAction(QString::fromLocal8Bit("�½�Э��"),this);

	m_action_editProtocol=new QAction(QString::fromLocal8Bit("�༭Э��"),this);

	m_action_deleteProtocol=new QAction(QString::fromLocal8Bit("ɾ��Э��"),this);

	m_action_addDevice = new QAction(QString::fromLocal8Bit("�½��豸"),this);

	m_action_editDevice = new QAction(QString::fromLocal8Bit("�༭�豸"),this);

	m_action_deleteDevice = new QAction(QString::fromLocal8Bit("ɾ���豸"),this);

	m_actin_saveSignal = new QAction(QString::fromLocal8Bit("�����¼"), this);

	 m_action_portAdd = new QAction(QString::fromLocal8Bit("���Ӷ˿�"), this);;//���Ӷ˿�

	m_action_portEditor = new QAction(QString::fromLocal8Bit("�޸Ķ˿�"), this);;//�޸Ķ˿�

	 m_action_portDel = new QAction(QString::fromLocal8Bit("ɾ���˿�"), this);//ɾ���˿�

	 m_action_devProtDel = new QAction(QString::fromLocal8Bit("ɾ��Э��"), this);
}
//��ʾ�����豸�б�
void QtEnvTest::setDeviceList()
{
	//���붥��Item��������Ϊչ��ģʽ
	ui.m_treeWidget_devManager->clear();
	QTreeWidgetItem* rootItem = new QTreeWidgetItem();
	ui.m_treeWidget_devManager->addTopLevelItem(rootItem);
	rootItem->setText(0,QString::fromLocal8Bit("�豸�б�"));
	rootItem->setExpanded(true);

	//�����豸���ݹ��������ֲ㰴�ؼ���ʾ����
	for(int i=0;i<m_deviceDataManager->m_devNameList.size();i++)
	{
		//�����豸�����ؼ�
		QTreeWidgetItem *secondItem=new QTreeWidgetItem(rootItem);
		QString devName=m_deviceDataManager->m_devNameList.at(i);
		secondItem->setText(0,devName);

		secondItem->setData(0,Qt::UserRole,"deviceName");
		secondItem->setExpanded(true);



		for(auto j = m_deviceDataManager->m_deviceList.value(devName).portList.begin();
			j != m_deviceDataManager->m_deviceList.value(devName).portList.end();j++)
		{
			//����˿������ؼ�
				QTreeWidgetItem *thirdItem=new QTreeWidgetItem(secondItem);
				thirdItem->setText(0, j->portName.c_str());
				thirdItem->setData(0, Qt::UserRole, "port");
				thirdItem->setExpanded(true);

				for (auto k = j->protList.begin(); k != j->protList.end(); k++)
				{
					//����Э�����������ؼ�
					QTreeWidgetItem* fourthItem = new QTreeWidgetItem(thirdItem);
					fourthItem->setText(0, k->protocolName.c_str());
					fourthItem->setData(0, Qt::UserRole, "protocolName");
					fourthItem->setExpanded(true);
				}
		}
	}
}
//��ʾ���±����б�
void QtEnvTest::setMessageList()
{
	qDebug()<<"update messageList";
	QTreeWidgetItem* item;
	ui.m_treeWidget_messageManager->clear();
	for(int i=0;i<m_dataManager->messageNameList.size();i++)
	{
		QString messageName=m_dataManager->messageNameList.at(i);
		qDebug()<<messageName;
		item=new QTreeWidgetItem(ui.m_treeWidget_messageManager);
		item->setText(0,messageName);
		item->setText(1,m_dataManager->messageList[messageName].messageExt.c_str());
	}
}
//���Э���¼
void QtEnvTest::on_addNewProtocol()
{
	QTreeWidgetItem* item = new QTreeWidgetItem(ui.m_treeWidget_protManager->topLevelItem(0));
	item->setData(0,Qt::UserRole,"protocolName");
	item->setText(0,"default");
	m_dataManager->addProtocol();
}
//ɾ��Э���¼
void QtEnvTest::on_delProtocol()
{
	int rowNumber=ui.m_treeWidget_protManager->currentIndex().row();
	if(rowNumber!=-1)
	{
		QTreeWidgetItem* item=ui.m_treeWidget_protManager->currentItem();
		QString protName;
		if(item->data(0,Qt::UserRole).toString()=="protocolName")
		{
			protName=item->text(0);
			delete item;		
			m_dataManager->protList.take(protName);
			m_dataManager->m_protStrList.takeAt(m_dataManager->m_protStrList.indexOf(protName));
			protocolManager->upDateTreeView(protocolManager->GetCurrentProtName());
		}
		else if(item->data(0,Qt::UserRole).toString()=="MessageName")
		{		
			protName=item->text(0);
			QTreeWidgetItem* itemParent=item->parent();
			delete item;	
			int itemCount=m_dataManager->protList[itemParent->text(0)].messages.indexOf(protName.toStdString());
			m_dataManager->protList[itemParent->text(0)].messages.takeAt(itemCount);
			protocolManager->upDateTreeView(protocolManager->GetCurrentProtName());
		}
		else
		{
			return;
		}

	}
}
//˫���Ҽ����Ҽ�����༭Э����ô˲�
void QtEnvTest::on_editProtocol()
{
	if (!messageEditor->on_saveModel())
	{
		return;
	}
	if(ui.m_treeWidget_protManager->currentIndex().row()!=-1)
	{
		protocolManager->SetDataManager(m_dataManager);
		clearWidget();

		ui.horizontalLayout_ProtManager->addWidget(protocolManager);
		protocolManager->show();
		
	if(ui.m_treeWidget_protManager->currentItem()->data(0,Qt::UserRole).toString()=="protocolName")
	{
		protocolManager->upDateTreeView(ui.m_treeWidget_protManager->currentItem()->text(0));
	}
	else if(ui.m_treeWidget_protManager->currentItem()->data(0,Qt::UserRole).toString()=="MessageName")
	{
		protocolManager->upDateTreeView(ui.m_treeWidget_protManager->currentItem()->parent()->text(0));
	}	
	}
}

void QtEnvTest::on_slot_ProtocolManager(QPoint pos)
{
	if (!ui.m_treeWidget_protManager->itemAt(pos))
	{
		return;
	}
	m_popMenu->clear();
	m_popMenu->addAction(m_action_addNewProtocol);
	m_popMenu->addAction(m_action_editProtocol);
	m_popMenu->addAction(m_action_deleteProtocol);
	m_popMenu->exec(QCursor::pos());
}

/*
	���ܣ��˺���ΪTableView��ǩ����ʱ���õĲۺ�����
	ʵ��:����ȫ�����ĵ���Ϣ����⵱ǰҳ�ı�ǩindex���������л�������������ص�ҳ��
*/

void QtEnvTest::OnTabChanged(int rowNumber)
{
	if(rowNumber!=0)
	{
		if(!isMsgFirst)
		{
			if(!messageEditor->on_saveModel())
			{
				if(QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�Ƿ�����Ե�ǰ�����޸�"))==QMessageBox::Ok)
				{
					ui.tabWidget->setCurrentIndex(0);
					setMessageList();
				}
				return;
			}

		}
		else
		{
			isMsgFirst=false;
		}
		if(!messageEditor->IsDeviceData())
		{
			qDebug()<<messageEditor->IsDeviceData();
			messageEditor->upDateTreeView(messageEditor->GetCurrentMessageName());
			protocolManager->upDateTreeView(protocolManager->GetCurrentProtName());
		}
		else
		{
			deviceManager->UpDateWidget();
		}

	}

}
/*
	���ܣ��˹�������Э�������б�
*/
void QtEnvTest::setProtList()
{
	ui.m_treeWidget_protManager->clear();
	QTreeWidgetItem* rootItem;
	rootItem=new QTreeWidgetItem();
	ui.m_treeWidget_protManager->addTopLevelItem(rootItem);
	rootItem->setText(0,QString::fromLocal8Bit("Э���б�"));
	rootItem->setExpanded(true);
	QStringList tempList=m_dataManager->m_protStrList;
	for(int j=0;j<tempList.size();j++)
	{
		QTreeWidgetItem *secondItem=new QTreeWidgetItem(rootItem);
		secondItem->setText(0,tempList.at(j));
		secondItem->setData(0,Qt::UserRole,"protocolName");
		secondItem->setExpanded(true);
		xlDataManager::ProtStruct tempProt=m_dataManager->protList[tempList.at(j)];
		for(int i=0;i<tempProt.messages.size();i++)
		{
			QTreeWidgetItem *thirdItem=new QTreeWidgetItem(secondItem);
			thirdItem->setText(0,tempProt.messages.at(i).c_str());
			thirdItem->setData(0,Qt::UserRole,"MessageName");
		}
	}

}
//�����±��Ĺ���
void QtEnvTest::on_addNewMessage()
{
	//����Ѿ�����һ��������ͬ����ʾ�޸�
	if(!m_dataManager->MessageIsExsit("default"))
	{
		QTreeWidgetItem* item = new QTreeWidgetItem(ui.m_treeWidget_messageManager);
		item->setText(0,"default");
		item->setText(1,"default");
		m_dataManager->addMessage();
	}
	else
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��༭���ϸ�������к��������"));
		return;
	}
}
//ɾ�����Ĺ���
void QtEnvTest::on_delMessage()
{

	QTreeWidgetItem* selectItem=ui.m_treeWidget_messageManager->currentItem();
	if(selectItem)
	{
		QString itemName=selectItem->text(0);
		delete selectItem;
		m_dataManager->delMessage(itemName);
		protocolManager->upDateTreeView(protocolManager->GetCurrentProtName());
		setProtList();
	}
}
//˫�����Ҽ��˵��༭ʱ���еĲۺ���
void QtEnvTest::on_editMessage()
{

	if(ui.m_treeWidget_messageManager->currentItem())
	{
		qDebug()<<isMsgFirst;
		if(!isMsgFirst)
		{
			if(!messageEditor->on_saveModel())
			{
				if(QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�Ƿ�����Ե�ǰ�����޸�"))==QMessageBox::Ok)
				{
					setMessageList();
				}
				return;
			}

		}
		else
		{
			isMsgFirst=false;
		}
		
		messageEditor->setDataManager(m_dataManager);
		ui.tabWidget->setCurrentIndex(0);
		clearWidget();
		messageEditor->show();
		messageEditor->upDateTreeView(ui.m_treeWidget_messageManager->currentItem()->text(0));
	}

}
//����豸�ڵ��¼
void QtEnvTest::on_addDevice()
{
	if(!m_deviceDataManager->DevIsExsit("default"))
	{
		QTreeWidgetItem* item = new QTreeWidgetItem(ui.m_treeWidget_devManager);
		item->setText(0,"default");
		item->setData(0,Qt::UserRole,"deviceName");
		m_deviceDataManager->AddDev("default");
	}
	else
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��༭���ϸ�������к��������"));
		return;
	}
}
//�޸��豸�ڵ��¼
void QtEnvTest::on_editDevice()
{
	if(ui.m_treeWidget_devManager->currentIndex().row()!=-1)
	{
		deviceManager->SetDataManger(m_deviceDataManager,m_dataManager);
		ui.tabWidget->setCurrentIndex(1);
		if(ui.m_treeWidget_devManager->currentItem()->data(0,Qt::UserRole).toString()=="deviceName")
		{
			deviceManager->SetTreeWidget(ui.m_treeWidget_devManager->currentItem()->text(0));
		}
		else if(ui.m_treeWidget_devManager->currentItem()->data(0,Qt::UserRole).toString()=="protocolName")
		{
			deviceManager->SetTreeWidget(ui.m_treeWidget_devManager->currentItem()->parent()->text(0));
		}		
	}
}
//ɾ���豸�ڵ��¼
void QtEnvTest::on_deleteDevice()
{
	int rowNumber=ui.m_treeWidget_devManager->currentIndex().row();
	if(rowNumber!=-1)
	{
		QTreeWidgetItem* currentItem=ui.m_treeWidget_devManager->currentItem();		
		QString itemStr=ui.m_treeWidget_devManager->currentItem()->text(0);
		if(currentItem->data(0,Qt::UserRole).toString()=="deviceName")
		{
			m_deviceDataManager->m_deviceList.take(itemStr);
			m_deviceDataManager->m_devNameList.removeAll(itemStr);
			setDeviceList();
			if(deviceManager->GetCurrentDevName()== itemStr)
			{
				deviceManager->Clear();
			}
		}
		else if (currentItem->data(0, Qt::UserRole).toString() == "port")
		{
			QTreeWidgetItem* parentItem = currentItem->parent();
			for (int i = 0; i < m_deviceDataManager->m_deviceList.value(parentItem->text(0)).portList.size(); i++)
			{
				DevicDataManager::PortStruct portStruct = m_deviceDataManager->m_deviceList.value(parentItem->text(0))
					.portList.at(i);
				if (QString(portStruct.portName.c_str()) == itemStr)
				{
					int index = m_deviceDataManager->m_deviceList[parentItem->text(0)].portList.indexOf(portStruct);
					m_deviceDataManager->m_deviceList[parentItem->text(0)].portList.takeAt(index);
				}
			}

		}
		else if(currentItem->data(0,Qt::UserRole).toString()=="protocolName")
		{
			QTreeWidgetItem* parentItem = currentItem->parent()->parent();
			for (int i = 0; i < m_deviceDataManager->m_deviceList.value(parentItem->text(0)).portList.size(); i++)
			{
				DevicDataManager::PortStruct portStruct = m_deviceDataManager->m_deviceList.value(parentItem->text(0))
					.portList.at(i);
				if (QString(portStruct.portName.c_str()) == currentItem->parent()->text(0))
				{

					for (int j = 0; j < portStruct.protList.size(); j++)
					{
						DevicDataManager::ProtStruct protStruct = m_deviceDataManager->m_deviceList.value(parentItem->text(0))
							.portList.at(i).protList.at(j);
						if (QString(protStruct.protocolName.c_str()) == itemStr)
						{
							int index = m_deviceDataManager->m_deviceList[parentItem->text(0)].portList.at(j).protList.indexOf(protStruct);
							m_deviceDataManager->m_deviceList[parentItem->text(0)].portList[j].protList.takeAt(index);
						}
					}

					
				}
			}
			
		}
		else
		{
			return;
		}
		m_deviceDataManager->UpdateAll();
	}
}
//����word��ʽЭ���ļ�
//�����ݹ������ж������ݣ�������ָ���ļ���
void QtEnvTest::on_trigger_saveWord()
{
	xlWriter writer;
	writer.setDataManager(m_dataManager);
	writer.saveWord();
}
