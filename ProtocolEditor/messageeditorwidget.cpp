#include "messageeditorwidget.h"
#include "xlDataManager.h"
#include <QDebug>
#include <QMessageBox>
#include <QTableView>
#include <QDebug>
#include "itemselectdelegate.h"
#include "spinnerdelegate.h"
#include "ItemFollowOther.h"
#include <assert.h>
MessageEditorWidget::MessageEditorWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	manager = NULL;
	model = new QStandardItemModel(this);
	model->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("属性名称")
		<< QString::fromLocal8Bit("数据类型")
		<< QString::fromLocal8Bit("数据长度")
		<< QString::fromLocal8Bit("初始值")
		<< QString::fromLocal8Bit("说明"));
	ui.m_lineEdit_MessageName->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z_$][a-zA-Z0-9_$]*"), this));
	ui.tableView->setModel(model);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
	m_popMenu = new QMenu(this);
	setAction();
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	connect(ui.tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnContextMenu(QPoint)));
	m_isDeviceData = false;
}

MessageEditorWidget::~MessageEditorWidget()
{

}

void MessageEditorWidget::setDataManager(xlDataManager* pManager)
{
	this->manager = pManager;
	m_isDeviceData = false;
	setSLot();
}

void MessageEditorWidget::upDateTreeView(QString messageName)
{
	if (messageName.isEmpty())
	{
		return;
	}
	clear();
	this->setSLot();
	model->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("属性名称")
		<< QString::fromLocal8Bit("数据类型")
		<< QString::fromLocal8Bit("数据长度")
		<< QString::fromLocal8Bit("初始值")
		<< QString::fromLocal8Bit("说明"));
	ui.tableView->setItemDelegateForColumn(1, new ItemSelectDelegate(this));
	ui.tableView->setItemDelegateForColumn(2, new SpinnerDelegate(this));
	ui.tableView->setItemDelegateForColumn(3, new ItemFollowOther(this));
	if (manager)
	{
		oldMessageName = messageName;
		NewMessageName = messageName;
		oldMessageExt = manager->messageList[messageName].messageExt.c_str();
		NewMessageExt = oldMessageExt;
		QMap<QString, xlDataManager::MessageStruct>::const_iterator itor = manager->messageList.find(messageName);
		ui.m_lineEdit_MessageName->setText(itor->messageName.c_str());
		ui.m_lineEdit_Ext->setText(itor->messageExt.c_str());
		if (itor != manager->messageList.constEnd())
		{
			for (int i = 0; i < itor->propList.size(); i++)
			{
				int rowcount = model->rowCount();
				model->insertRow(rowcount);
				model->setData(model->index(rowcount, 0), itor->propList.at(i).propName.c_str());
				model->setData(model->index(rowcount, 1), itor->propList.at(i).propStyle.c_str());
				model->setData(model->index(rowcount, 2), itor->propList.at(i).propSize);
				model->setData(model->index(rowcount, 3), itor->propList.at(i).propHint.c_str());
				model->setData(model->index(rowcount, 4), itor->propList.at(i).propExt.c_str());
			}
		}

	}
}

void MessageEditorWidget::setSLot()
{
	connect(ui.m_lineEdit_MessageName, SIGNAL(editingFinished()), this, SLOT(OnMessagNameLineEditorFinished()));
	connect(ui.m_lineEdit_Ext, SIGNAL(editingFinished()), this, SLOT(onMessageLineEditorChange()));
	connect(m_action_addNewProp, SIGNAL(triggered()), this, SLOT(on_addNewProp()));
	connect(m_action_deleteProp, SIGNAL(triggered()), this, SLOT(on_delProp()));
}

void MessageEditorWidget::setAction()
{
	m_action_addNewProp = new QAction(QString::fromLocal8Bit("新建属性"), this);
	m_action_deleteProp = new QAction(QString::fromLocal8Bit("删除属性"), this);
}

void MessageEditorWidget::UnSetAction()
{
	disconnect(ui.m_lineEdit_MessageName, SIGNAL(editingFinished()), this, SLOT(OnMessagNameLineEditorFinished()));
	disconnect(ui.m_lineEdit_Ext, SIGNAL(editingFinished()), this, SLOT(onMessageLineEditorChange()));
	disconnect(m_action_addNewProp, SIGNAL(triggered()), this, SLOT(on_addNewProp()));
	disconnect(m_action_deleteProp, SIGNAL(triggered()), this, SLOT(on_delProp()));
}

void MessageEditorWidget::SetDevSlot()
{
	connect(ui.m_lineEdit_MessageName, SIGNAL(editingFinished()), this, SLOT(OnMessagNameLineEditorFinished()));
	connect(ui.m_lineEdit_Ext, SIGNAL(editingFinished()), this, SLOT(onMessageLineEditorChange()));
	connect(m_action_addNewProp, SIGNAL(triggered()), this, SLOT(on_addNewProp()));
	connect(m_action_deleteProp, SIGNAL(triggered()), this, SLOT(on_delProp()));
}

void MessageEditorWidget::UnSetDevSlot()
{
	disconnect(ui.m_lineEdit_MessageName, SIGNAL(editingFinished()), this, SLOT(OnMessagNameLineEditorFinished()));
	disconnect(ui.m_lineEdit_Ext, SIGNAL(editingFinished()), this, SLOT(onMessageLineEditorChange()));

	disconnect(m_action_addNewProp, SIGNAL(triggered()), this, SLOT(on_addNewProp()));
	disconnect(m_action_deleteProp, SIGNAL(triggered()), this, SLOT(on_delProp()));
}

void MessageEditorWidget::OnMessagNameLineEditorFinished()
{
	if (ui.m_lineEdit_MessageName->isModified())
	{
		if (oldMessageName.isEmpty())
		{
			return;
		}
		QString tempMessageName = ui.m_lineEdit_MessageName->text().trimmed();
		if (tempMessageName == oldMessageName)
		{
			return;
		}
		else if ((manager->MessageIsExsit(tempMessageName) || tempMessageName.isEmpty()) && !IsDeviceData())
		{
			QMessageBox::critical(this, QString::fromLocal8Bit("错误提示"), QString::fromLocal8Bit("报文名称不能为空或重复，请重新命名"));
			ui.m_lineEdit_MessageName->setText(oldMessageName);
			return;
		}
		else if (IsDeviceData() && (m_deviceDataManager->IsExitMessage(m_oldDevName, m_portName, m_oldProtName, tempMessageName) || tempMessageName.isEmpty()))
		{
			QMessageBox::critical(this, QString::fromLocal8Bit("错误提示"), QString::fromLocal8Bit("报文名称不能为空或重复，请重新命名"));
			ui.m_lineEdit_MessageName->setText(oldMessageName);
			return;
		}
		else
		{
			NewMessageName = tempMessageName;
			if (!IsDeviceData())
			{
				manager->updataMessage_messageName(oldMessageName, NewMessageName);
			}
			else
			{
				for (int i = 0; i < m_deviceDataManager->m_deviceList.value(m_oldDevName).portList.size(); i++)
				{
					if (m_deviceDataManager->m_deviceList.value(m_oldDevName).portList[i].portName.c_str() == m_portName)
					{
						for (int m = 0; m < m_deviceDataManager->m_deviceList.value(m_oldDevName).portList[i].protList.size(); m++)
						{
							if (m_deviceDataManager->m_deviceList.value(m_oldDevName).portList[i].protList[m].protocolName.c_str() == m_oldProtName)
							{
								for (int j = 0; j < m_deviceDataManager->m_deviceList.value(m_oldDevName).portList[i].protList[i].messgeList.size(); j++)
								{
									if (m_deviceDataManager->m_deviceList.value(m_oldDevName).portList[i].protList[i].messgeList[j].messageName.c_str() == oldMessageName)
									{
										m_deviceDataManager->m_deviceList[m_oldDevName].portList[i].protList[i].messgeList[j].messageName = NewMessageName.toStdString();
									}
								}
							}
						}

					}
				}
			}
			oldMessageName = NewMessageName;
			//m_deviceDataManager->UpdateAll();
		}
	}

}
//报文注释改变时，响应的槽函数
void MessageEditorWidget::onMessageLineEditorChange()
{
	//如果报文注释没改变，返回
	NewMessageExt = ui.m_lineEdit_Ext->text();
	if (NewMessageExt == oldMessageExt)
	{
		return;
	}
	else
	{
		//如果不是设备信息改变，直接更报文的数据，否则改变设备信息的相关数据
		if (!IsDeviceData())
		{
			manager->updateMessageTreeOnly(oldMessageName, NewMessageExt);
		}
		else
		{
		//循环遍历找到相关信息后更改
			if (m_deviceDataManager->m_deviceList.value(m_oldDevName) == DevicDataManager::DevStruct())
			{
				return;
			}
			for (auto m = m_deviceDataManager->m_deviceList[m_oldDevName].portList.begin();
				m != m_deviceDataManager->m_deviceList[m_oldDevName].portList.end(); ++m)
			{
				if (m->portName.c_str() == m_portName)
				{
				for (auto i = m->protList.begin(); i != m->protList.begin(); i++)
				{
					if (i->protocolName.c_str() == m_oldProtName)
					{
						for (auto j = i->messgeList.begin(); j !=  i->messgeList.end(); j++)
						{
							if (j->messageName.c_str() == oldMessageName)
							{
								j->messageExt = ui.m_lineEdit_Ext->text().toStdString();
							}
						}


					}
				}
				}

			}
		}

		oldMessageExt = NewMessageExt;
		//	m_deviceDataManager->UpdateAll();
	}
}

void MessageEditorWidget::OnContextMenu(QPoint)
{
	m_popMenu->clear();
	m_popMenu->addAction(m_action_addNewProp);
	m_popMenu->addAction(m_action_deleteProp);
	m_popMenu->exec(QCursor::pos());
}

void MessageEditorWidget::on_addNewProp()
{
	if (oldMessageName.isEmpty())
	{
		return;
	}
	int row = ui.tableView->currentIndex().row();
	if (row != -1)
	{
		model->insertRow(row + 1);
	}
	else
	{
		model->insertRow(model->rowCount());
	}

}

void MessageEditorWidget::on_delProp()
{
	if (oldMessageName.isEmpty())
	{
		return;
	}
	int row = ui.tableView->currentIndex().row();
	qDebug() << row;
	if (row != -1)
	{
		model->removeRow(row);
	}
}
//更新设备数据
void MessageEditorWidget::UpdateDevDate(QString devName, QString portName, QString protName, QString msgName)
{
	assert(!devName.isEmpty() && !portName.isEmpty() && !protName.isEmpty() && !msgName.isEmpty());
	this->clear();
	SetDevSlot();
	model->setHorizontalHeaderLabels(QStringList() << QString::fromLocal8Bit("属性名称")
		<< QString::fromLocal8Bit("数据类型")
		<< QString::fromLocal8Bit("数据长度")
		<< QString::fromLocal8Bit("初始值")
		<< QString::fromLocal8Bit("说明"));
	ui.tableView->setItemDelegateForColumn(1, new ItemSelectDelegate(this));
	ui.tableView->setItemDelegateForColumn(2, new SpinnerDelegate(this));
	ui.tableView->setItemDelegateForColumn(3, new ItemFollowOther(this));
	m_oldDevName = devName;
	oldMessageName = msgName.split(" ").at(0);
	m_oldProtName = protName;
	m_portName = portName;
	ui.m_lineEdit_MessageName->setText(oldMessageName);

	//遍历查找并把报文相关的数据加入到Model中
	for (auto i = m_deviceDataManager->m_deviceList.value(devName).portList.begin();
		i != m_deviceDataManager->m_deviceList.value(devName).portList.end(); ++i)
	{
		if (i->portName.c_str() == portName)
		{
			for (auto j = i->protList.begin(); j != i->protList.end();++j)
			{
				if (j->protocolName.c_str() == m_oldProtName)
				{
					for (auto k = j->messgeList.begin(); k!= j->messgeList.begin(); ++k)
					{
						if (k->messageName.c_str() == oldMessageName)
						{
							ui.m_lineEdit_Ext->setText(k->messageExt.c_str());

							if (m_deviceDataManager)
							{
								for (auto l=k->propList.begin();l!=k->propList.end();l++)
								{
									int rowcount = model->rowCount();
									model->insertRow(rowcount);
									model->setData(model->index(rowcount, 0), l->propName.c_str());
									model->setData(model->index(rowcount, 1), l->propStyle.c_str());
									model->setData(model->index(rowcount, 2), l->propSize);
									model->setData(model->index(rowcount, 3), l->propHint.c_str());
									model->setData(model->index(rowcount, 4), l->propExt.c_str());
								}
							}

							return;
						}
					}
				}
			}
		}
	}
}

bool MessageEditorWidget::on_saveModel()
{

	if (manager || m_deviceDataManager)
	{

		QList<QString> messageTestList;
		for (int i = 0; i < model->rowCount(); i++)
		{
			QString str = model->index(i, 0).data().toString();
			if (messageTestList.indexOf(str) != -1)
			{
				QMessageBox::critical(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("第%1行/n属性名称字段重复，请修改").arg(i));
				return false;
			}
			messageTestList.push_back(str);
			for (int j = 0; j < 4; j++)
			{
				QString str = model->index(i, j).data().toString().trimmed();
				if (str.isEmpty())
				{
					QMessageBox::critical(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("第%1行%2列/n为空项，请修改").arg(i).arg(j));
					return false;
				}
			}
		}
		if (!IsDeviceData())
		{
			manager->messageList[oldMessageName].propList.clear();
			for (int i = 0; i < model->rowCount(); i++)
			{

				xlDataManager::PropStruct tempMsg;
				tempMsg.propName = model->index(i, 0).data().toString().trimmed().toStdString();

				tempMsg.propStyle = model->index(i, 1).data().toString().trimmed().toStdString();

				tempMsg.propSize = model->index(i, 2).data().toInt();

				tempMsg.propHint = model->index(i, 3).data().toString().trimmed().toStdString();

				tempMsg.propExt = model->index(i, 4).data().toString().trimmed().toStdString();
				manager->messageList[oldMessageName].propList.append(tempMsg);

			}
		}
		else
		{
			for (int i = 0; i < m_deviceDataManager->m_deviceList.value(m_oldDevName).portList.size(); i++)
			{
				if (m_deviceDataManager->m_deviceList.value(m_oldDevName).portList[i].portName.c_str() == m_portName)
				{
					for (int j = 0; j < m_deviceDataManager->m_deviceList[m_oldDevName].portList[i].protList.size(); j++)
					{
						if (m_deviceDataManager->m_deviceList.value(m_oldDevName).portList[i].protList[j].protocolName.c_str() == m_oldProtName)
						{
							for (int m = 0; m < m_deviceDataManager->m_deviceList[m_oldDevName].portList[i].protList[j].messgeList.size(); m++)
							{
								if (m_deviceDataManager->m_deviceList.value(m_oldDevName).portList[i].protList[m].messgeList.at(j).messageName == oldMessageName.toStdString())
								{
									m_deviceDataManager->m_deviceList[m_oldDevName].portList[i].protList[m].messgeList[j].propList.clear();
									for (int k = 0; k < model->rowCount(); k++)
									{

										DevicDataManager::PropStruct tempMsg;
										tempMsg.propName = model->index(k, 0).data().toString().trimmed().toStdString();

										tempMsg.propStyle = model->index(k, 1).data().toString().trimmed().toStdString();

										tempMsg.propSize = model->index(k, 2).data().toInt();

										tempMsg.propHint = model->index(k, 3).data().toString().trimmed().toStdString();

										tempMsg.propExt = model->index(k, 4).data().toString().trimmed().toStdString();

										m_deviceDataManager->m_deviceList[m_oldDevName].portList[i].protList[m].messgeList[j].propList.append(tempMsg);
									}
								}
							}

						}


					}
				}
			}
		}
	}
	manager->SetDirty();
	return true;
}


QString MessageEditorWidget::GetCurrentMessageName()
{
	return oldMessageName;
}

void MessageEditorWidget::clear()
{
	ui.m_lineEdit_Ext->clear();
	ui.m_lineEdit_MessageName->clear();
	UnSetAction();
	UnSetDevSlot();
	model->clear();
}

void MessageEditorWidget::SetDevManager(DevicDataManager* devManager)
{
	this->m_deviceDataManager = devManager;
	m_isDeviceData = true;
	SetDevSlot();
}

bool MessageEditorWidget::IsDeviceData()
{
	return m_isDeviceData;
}
