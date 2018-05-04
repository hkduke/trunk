/*
	此文件为主窗口文件，窗口中主要有：
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
	功能：构造函数
	主要用途：对各成员变量初始化，设置初始化参数及UI相关的显示工作，信号槽的连接
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
	this->setWindowTitle(QString::fromLocal8Bit("软件协议设计工具"));
	
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
	功能：析构函数
*/
QtEnvTest::~QtEnvTest()
{
}
/*
	功能：打开Action槽函数
	描述：首次打开软件时，默认打开模板文件"./elCD.XML"，如果模板不存在或打开错误，则新建一个空模板
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
			QMessageBox::warning(this, QString::fromLocal8Bit("文件打开提示"),
				QString::fromLocal8Bit("默认模版协议文件%1不能打开\n%2").
				arg(fileName).arg(file.errorString()));
			OpenEmptyManager();
		}
		else
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("文件打开提示"),
				QString::fromLocal8Bit("不能打开%1:\n%2").
				arg(fileName).arg(file.errorString()));
		}
		return;
	}
	if(!m_dataManager->protList.isEmpty())
	{
		if(QMessageBox::Yes==QMessageBox::question(this, QString::fromLocal8Bit("文件打开提示"), 
			QString::fromLocal8Bit("是否保存已修改的文件"),QMessageBox::Yes,QMessageBox::No))
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
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开提示"),
			QString::fromLocal8Bit("不能打开%1:\n%2").
			arg(fileName).arg(reader.errorString()));
		return;
	}
	else
	{
		statusBar()->showMessage(QString::fromLocal8Bit("文件打开成功"),2000);
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
	功能：协议保存槽函数

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
	功能：设备打开槽函数
*/
void QtEnvTest::on_trigger_deviceOpen()
{
	//打开打开文件对话框，如果名称为空，则退出
	QString fileName =  QFileDialog::getOpenFileName(this,tr("Open File"), ".", tr("xml Files (*.xml)"));
	if(fileName.isEmpty())
	{
		return;
	}
	//清理设备树控件
	ui.m_treeWidget_devManager->clear();
	//如果打开失败，则返回
	QFile file(fileName);
	if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开提示"),
			QString::fromLocal8Bit("不能打开%1:\n%2").
			arg(fileName).arg(file.errorString()));
		return;
	}
	//设置设备数据管理器，读入设备信息
	m_deviceDataManager = new DevicDataManager(this);

	readDeviceXml reader;
	reader.setxlDataManager(m_deviceDataManager);
	if(!reader.read(&file))
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("文件打开提示"),
			QString::fromLocal8Bit("不能打开%1:\n%2").
			arg(fileName).arg(reader.errorString()));
		return;
	}
	else
	{
		statusBar()->showMessage(QString::fromLocal8Bit("文件打开成功"),2000);
	}
	file.close();
	setDeviceList();
	ui.tabWidget->setCurrentIndex(1);
	connect(m_deviceDataManager,SIGNAL(DataChanged()),this,SLOT(setDeviceList()));
	connect(m_deviceDataManager,SIGNAL(DataChanged()),deviceManager,SLOT(UpDateWidget()));

}
/*
功能：设备节点协议保存槽函数

*/
void QtEnvTest::on_trigger_deviceSave()
{
	if (m_deviceDataManager == NULL)
	{
		QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("没有数据保存"), QMessageBox::Ok);
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


//信号槽管理
void QtEnvTest::SetSlot()
{
	connect(ui.m_action_save,SIGNAL(triggered()),this,SLOT(on_trigger_save()));
	connect(ui.m_action_open,SIGNAL(triggered()),this,SLOT(on_trigger_open()));
	connect(ui.m_action_deviceOpen,SIGNAL(triggered()),this,SLOT(on_trigger_deviceOpen()));
	connect(ui.m_action_deviceSave,SIGNAL(triggered()),this,SLOT(on_trigger_deviceSave()));
	connect(ui.m_treeWidget_messageManager,SIGNAL(customContextMenuRequested(QPoint)),
		this,SLOT(on_slot_messageManager(QPoint)));
	//以下信号和槽为拖动协议树后更改标签页，以方便插入内容
	connect(ui.m_treeWidget_protManager, &ProtocolNoReceiveTreeWidget::ItemMoving, [&]() {
		ui.tabWidget->setCurrentIndex(1);
		//ui.horizontalLayout_ProtManager->addWidget(deviceManager);
	});
	//以下信号和槽为更换版本号的功能
	connect(ui.m_lineEdit_VersionInfor, &QLineEdit::editingFinished, [&] {
		if (ui.m_lineEdit_VersionInfor->text().isEmpty())
		{
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("版本信息不能为空"));
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
//打开空模板
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
//隐藏控件
void QtEnvTest::clearWidget()
{
	protocolManager->setHidden(true);
	messageEditor->setHidden(true);
}
/*
	此函数为程序关闭的事件重写
*/
void QtEnvTest::closeEvent(QCloseEvent *event)
{
	messageEditor->on_saveModel();
	if (m_dataManager)
	{
		if (QMessageBox::critical(this, QString::fromLocal8Bit("提示")
			, QString::fromLocal8Bit("协议未保存，是否保存"),QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
		{
			on_trigger_save();
		}
	}
	if (m_deviceDataManager)
	{
		if (QMessageBox::critical(this, QString::fromLocal8Bit("提示")
			, QString::fromLocal8Bit("设备协议未保存，是否保存"), QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
		{
				on_trigger_deviceSave();
		}
	}
	return QMainWindow::closeEvent(event);
}

//报文信息修改后调用此槽函数
void QtEnvTest::OnGotoMessageEditor(QString str)
{
	clearWidget();
	ui.horizontalLayout_ProtManager->addWidget(messageEditor);
	messageEditor->show();
	messageEditor->upDateTreeView(str);
	//protocolManager->upDateTreeView();
}
//双击设备树，或右键点击编辑，调用此槽函数
void QtEnvTest::OnEditDevMsg(QString devName,QString protName,QString msgName)
{
	ui.tabWidget->setCurrentIndex(0);

	if(!messageEditor->on_saveModel())
	{
		return;
	}
	messageEditor->SetDevManager(m_deviceDataManager);
	//等待修改
	messageEditor->UpdateDevDate(devName,"",protName,msgName);
}

//保存设备相关信息至文件
void QtEnvTest::OnSaveSignalDev()
{
	//如果Item 不存在或是协议 ，则返回
	if (ui.m_treeWidget_devManager->currentIndex().row() == -1
		|| ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "protocolName")
	{
		return;
	}
	//如果是设备名称，则保存单个设备的数据
	else if (ui.m_treeWidget_devManager->currentItem()->data(0,Qt::UserRole).toString()=="deviceName")
	{
		if (m_deviceDataManager == NULL)
		{
			QMessageBox::warning(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("没有数据保存"), QMessageBox::Ok);
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
	//如果是根目录，则保存全部设备目录
	else if (ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "")
	{
		on_trigger_deviceSave();
	}
}
//增加新端口
void QtEnvTest::OnPortNew()
{
	//检测当前选择的是不是设备,如果是进行下一步处理
	if (ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "deviceName")
	{
		QString deviceName = ui.m_treeWidget_devManager->currentItem()->text(0);
		//如果设备名称为空则不处理
		if (deviceName.isEmpty())
		{
			return;
		}
		//创建一个端口对象，加入至指定设备中，端口加入前先检查是否端口已经存在，如果存在，则提示
		assert(m_deviceDataManager->DevIsExsit(deviceName));
		if (m_deviceDataManager->IsExitPort(deviceName, "default"))
		{
			QMessageBox::critical(this, QString::fromLocal8Bit("提示"), 
				QString::fromLocal8Bit("请编辑修改前个新增端口的名称后再加入新条目"));
			return;
		}
		DevicDataManager::PortStruct tempPortStruct;
		tempPortStruct.portName = "default";
		tempPortStruct.protList.clear();
		m_deviceDataManager->m_deviceList[deviceName].portList << tempPortStruct;
		m_deviceDataManager->UpdateAll();
	}

}
//编辑端口名称
void QtEnvTest::OnPortEditor()
{

}
//删除端口
void QtEnvTest::OnPortDel()
{

}
//在报文treeWdiget点右键时弹出此菜单
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
//在设备treeWidget右键点击时弹出菜单
bool QtEnvTest::on_slot_Device(QPoint point)
{
	//如果没有Item
	if (!ui.m_treeWidget_devManager->itemAt(point))
	{
		return false;
	}	
	//清空弹出菜单
	m_popMenu->clear();
	//如果Item是端口
	if (ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "port")
	{

		m_popMenu->addAction(m_action_portEditor);
		m_popMenu->addAction(m_action_portDel);
	}
	//如果ITem是设备名
	else if (ui.m_treeWidget_devManager->currentItem()->data(0, Qt::UserRole).toString() == "deviceName")
	{

		m_popMenu->addAction(m_action_editDevice);
		m_popMenu->addAction(m_action_deleteDevice);
		m_popMenu->addAction(m_action_portAdd);
		m_popMenu->addAction(m_actin_saveSignal);
	}
	//其它
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
//设置右键弹出菜单
void QtEnvTest::creatContexMenuAction()
{
	m_action_addNewMessage = new QAction(QString::fromLocal8Bit("新建报文"),this);

	m_action_editMessage = new QAction(QString::fromLocal8Bit("编辑报文"),this);

	m_action_deleteMessage = new QAction(QString::fromLocal8Bit("删除报文"),this);

	m_action_addNewProtocol=new QAction(QString::fromLocal8Bit("新建协议"),this);

	m_action_editProtocol=new QAction(QString::fromLocal8Bit("编辑协议"),this);

	m_action_deleteProtocol=new QAction(QString::fromLocal8Bit("删除协议"),this);

	m_action_addDevice = new QAction(QString::fromLocal8Bit("新建设备"),this);

	m_action_editDevice = new QAction(QString::fromLocal8Bit("编辑设备"),this);

	m_action_deleteDevice = new QAction(QString::fromLocal8Bit("删除设备"),this);

	m_actin_saveSignal = new QAction(QString::fromLocal8Bit("保存记录"), this);

	 m_action_portAdd = new QAction(QString::fromLocal8Bit("增加端口"), this);;//增加端口

	m_action_portEditor = new QAction(QString::fromLocal8Bit("修改端口"), this);;//修改端口

	 m_action_portDel = new QAction(QString::fromLocal8Bit("删除端口"), this);//删除端口

	 m_action_devProtDel = new QAction(QString::fromLocal8Bit("删除协议"), this);
}
//显示更新设备列表
void QtEnvTest::setDeviceList()
{
	//加入顶级Item，并设置为展开模式
	ui.m_treeWidget_devManager->clear();
	QTreeWidgetItem* rootItem = new QTreeWidgetItem();
	ui.m_treeWidget_devManager->addTopLevelItem(rootItem);
	rootItem->setText(0,QString::fromLocal8Bit("设备列表"));
	rootItem->setExpanded(true);

	//遍历设备数据管理器，分层按控件显示数据
	for(int i=0;i<m_deviceDataManager->m_devNameList.size();i++)
	{
		//加入设备至树控件
		QTreeWidgetItem *secondItem=new QTreeWidgetItem(rootItem);
		QString devName=m_deviceDataManager->m_devNameList.at(i);
		secondItem->setText(0,devName);

		secondItem->setData(0,Qt::UserRole,"deviceName");
		secondItem->setExpanded(true);



		for(auto j = m_deviceDataManager->m_deviceList.value(devName).portList.begin();
			j != m_deviceDataManager->m_deviceList.value(devName).portList.end();j++)
		{
			//加入端口至树控件
				QTreeWidgetItem *thirdItem=new QTreeWidgetItem(secondItem);
				thirdItem->setText(0, j->portName.c_str());
				thirdItem->setData(0, Qt::UserRole, "port");
				thirdItem->setExpanded(true);

				for (auto k = j->protList.begin(); k != j->protList.end(); k++)
				{
					//加入协议名称至树控件
					QTreeWidgetItem* fourthItem = new QTreeWidgetItem(thirdItem);
					fourthItem->setText(0, k->protocolName.c_str());
					fourthItem->setData(0, Qt::UserRole, "protocolName");
					fourthItem->setExpanded(true);
				}
		}
	}
}
//显示更新报文列表
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
//添加协议记录
void QtEnvTest::on_addNewProtocol()
{
	QTreeWidgetItem* item = new QTreeWidgetItem(ui.m_treeWidget_protManager->topLevelItem(0));
	item->setData(0,Qt::UserRole,"protocolName");
	item->setText(0,"default");
	m_dataManager->addProtocol();
}
//删除协议记录
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
//双击右键或右键点击编辑协议调用此槽
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
	功能：此函数为TableView标签更换时调用的槽函数。
	实现:保存全部更改的信息，检测当前页的标签index，视情形切换各列新其它相关的页面
*/

void QtEnvTest::OnTabChanged(int rowNumber)
{
	if(rowNumber!=0)
	{
		if(!isMsgFirst)
		{
			if(!messageEditor->on_saveModel())
			{
				if(QMessageBox::critical(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("是否放弃对当前报文修改"))==QMessageBox::Ok)
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
	功能：此功能设置协议树的列表
*/
void QtEnvTest::setProtList()
{
	ui.m_treeWidget_protManager->clear();
	QTreeWidgetItem* rootItem;
	rootItem=new QTreeWidgetItem();
	ui.m_treeWidget_protManager->addTopLevelItem(rootItem);
	rootItem->setText(0,QString::fromLocal8Bit("协议列表"));
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
//增加新报文功能
void QtEnvTest::on_addNewMessage()
{
	//如果已经存在一条名称相同，提示修改
	if(!m_dataManager->MessageIsExsit("default"))
	{
		QTreeWidgetItem* item = new QTreeWidgetItem(ui.m_treeWidget_messageManager);
		item->setText(0,"default");
		item->setText(1,"default");
		m_dataManager->addMessage();
	}
	else
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请编辑完上个新添加行后添加新行"));
		return;
	}
}
//删除报文功能
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
//双击或右键菜单编辑时运行的槽函数
void QtEnvTest::on_editMessage()
{

	if(ui.m_treeWidget_messageManager->currentItem())
	{
		qDebug()<<isMsgFirst;
		if(!isMsgFirst)
		{
			if(!messageEditor->on_saveModel())
			{
				if(QMessageBox::critical(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("是否放弃对当前报文修改"))==QMessageBox::Ok)
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
//添加设备节点记录
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
		QMessageBox::critical(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("请编辑完上个新添加行后添加新行"));
		return;
	}
}
//修改设备节点记录
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
//删除设备节点记录
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
//储存word格式协议文件
//在数据管理器中读出数据，保存在指定文件中
void QtEnvTest::on_trigger_saveWord()
{
	xlWriter writer;
	writer.setDataManager(m_dataManager);
	writer.saveWord();
}
