#include "devicemanagerwidget.h"
#include <QMessageBox>
#include <QDebug>
//���캯������ʼ�����ؼ�
DeviceManagerWidget::DeviceManagerWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_popMenu = new QMenu(ui.treeWidget);
	ui.treeWidget->setHeaderHidden(true);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	this->SetAction();
	connect(ui.treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnCustomContextMenu(QPoint)));
	connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(OnItemDoubleClick()));
}

DeviceManagerWidget::~DeviceManagerWidget()
{

}
//��տؼ����ź�
void DeviceManagerWidget::clear()
{
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.treeWidget->clear();
	disconnect(ui.lineEdit, SIGNAL(editingFinished()), this, SLOT(OnNameChanged()));
	disconnect(ui.lineEdit_2, SIGNAL(editingFinished()), this, SLOT(OnExtChanged()));
}

//�����豸�ͱ������ݹ�����
void DeviceManagerWidget::SetDataManger(DevicDataManager* dev, xlDataManager* datManger)
{
	m_deviceDataManager = dev;
	m_dataManager = datManger;
	ui.treeWidget->SetDataManager(m_deviceDataManager);
	ui.treeWidget->SetModeManager(m_dataManager);
	connect(ui.lineEdit, SIGNAL(editingFinished()), this, SLOT(OnNameChanged()));
	connect(ui.lineEdit_2, SIGNAL(editingFinished()), this, SLOT(OnExtChanged()));
}
//��ȡ��ǰ�༭���豸��Ϣ����
QString DeviceManagerWidget::GetCurrentDevName()
{
	return m_oldDevName;
}

//�������ؼ�
void DeviceManagerWidget::SetTreeWidget(QString devName)
{
	if (!devName.isEmpty())
	{
		m_newDevName = devName;
		m_oldDevName = devName;
		UpDateWidget();
	}

}
//�������ؼ�����
void DeviceManagerWidget::UpDateWidget()
{
	if (m_newDevName.isEmpty())
	{
		return;
	}
	if (!m_deviceDataManager->DevIsExsit(m_oldDevName))
	{
		ui.lineEdit->clear();
		ui.lineEdit_2->clear();
		ui.treeWidget->clear();
		return;
	}
	qDebug() << m_deviceDataManager->m_deviceList.keys();
	ui.treeWidget->clear();
	QTreeWidgetItem* rootitem = new QTreeWidgetItem(ui.treeWidget);
	rootitem->setExpanded(true);
	rootitem->setText(0, m_oldDevName);
	ui.lineEdit->setText(m_oldDevName);
	ui.lineEdit_2->setText(m_deviceDataManager->m_deviceList.value(m_oldDevName).deviceExt.c_str());
	ui.treeWidget->addTopLevelItem(rootitem);

	QList<DevicDataManager::PortStruct> portList = m_deviceDataManager->m_deviceList.value(m_oldDevName).portList;
	for(int m=0;m<portList.size();m++)
	{

		QList<DevicDataManager::ProtStruct> protList = m_deviceDataManager->m_deviceList.value(m_oldDevName).portList.at(m).protList;
		QTreeWidgetItem* firstItem = new QTreeWidgetItem(rootitem);
		firstItem->setExpanded(true);
		firstItem->setText(0, portList.at(m).portName.c_str());
		firstItem->setData(0, Qt::UserRole, "port");
		for (int i = 0; i < protList.size(); i++)
		{
			QTreeWidgetItem* secondItem;
			DevicDataManager::ProtStruct tempProtStruct = protList.at(i);
			secondItem = new QTreeWidgetItem(firstItem);
			secondItem->setExpanded(true);
			secondItem->setText(0, tempProtStruct.protocolName.c_str());
			secondItem->setData(0, Qt::UserRole, "protocolName");
			for (int j = 0; j < tempProtStruct.messgeList.size(); j++)
			{
				QTreeWidgetItem* thirdItem;
				DevicDataManager::MessageStruct tempMsgStruct = tempProtStruct.messgeList.at(j);
				thirdItem = new QTreeWidgetItem(secondItem);
				thirdItem->setExpanded(true);
				thirdItem->setText(0, QString(tempMsgStruct.messageName.c_str()) + "  " + tempMsgStruct.messageP.c_str());
				thirdItem->setData(0, Qt::UserRole, "messageName");
				QStringList tempPropList = m_deviceDataManager->GetMessagePropStringFormat(tempMsgStruct);
				for (int i = 0; i < tempPropList.size(); i++)
				{
					QTreeWidgetItem* fourthItem;
					fourthItem = new QTreeWidgetItem(thirdItem);
					fourthItem->setExpanded(true);
					fourthItem->setText(0, tempPropList.at(i));
					fourthItem->setData(0, Qt::UserRole, "messageProp");
				}
			}
		}
	}

	
}
//������ؼ�
void DeviceManagerWidget::Clear()
{
	ui.treeWidget->clear();
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	disconnect(ui.lineEdit, SIGNAL(editingFinished()), this, SLOT(OnNameChanged()));
	disconnect(ui.lineEdit_2, SIGNAL(editingFinished()), this, SLOT(OnExtChanged()));
}
//�豸���Ƹı䴥���ۺ���
void DeviceManagerWidget::OnNameChanged()
{
	if (m_oldDevName.isEmpty())
	{
		return;
	}
	QString tempMessageName = ui.lineEdit->text().trimmed();
	if (tempMessageName == m_oldDevName)
	{
		return;
	}
	else if (m_deviceDataManager->DevIsExsit(tempMessageName) || tempMessageName.isEmpty())
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("������ʾ"),
			QString::fromLocal8Bit("�������Ʋ���Ϊ�ջ��ظ�������������"));
		ui.lineEdit->setText(m_oldDevName);
		return;
	}
	else
	{
		m_newDevName = tempMessageName;
		m_deviceDataManager->UpdateDevName(m_oldDevName, tempMessageName);
		m_deviceDataManager->m_deviceList.take(m_oldDevName);
		m_oldDevName = m_newDevName;
		UpDateWidget();
	}
}
//˵���ı�ʱ����
void DeviceManagerWidget::OnExtChanged()
{
	m_newDevExt = ui.lineEdit_2->text();
	if (m_newDevExt == m_oldDevExt)
	{
		return;
	}
	else
	{
		m_deviceDataManager->UpdateExt(m_oldDevName, m_newDevExt);
		m_oldDevExt = m_newDevExt;
		UpDateWidget();
	}
}
//�Ҽ�����ʱ����
void DeviceManagerWidget::OnCustomContextMenu(QPoint)
{
	if (ui.treeWidget->currentIndex().row() == -1)
		return;


	if (ui.treeWidget->currentItem()->data(0, Qt::UserRole) == "messageName")
	{
		m_popMenu->clear();
		m_popMenu->addAction(m_publish);
		m_popMenu->addAction(m_subscript);
		m_popMenu->exec(QCursor::pos());
	}
}
//�Ҽ�ѡ�񷢲�ʱ�����ۺ���
void DeviceManagerWidget::OnPublish()
{
	//��ȡ�����˵��ж˿ڵ�����
	int portCount = m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
		.portList.size();
	//�ָ������ַ���
	QStringList strList = ui.treeWidget->currentItem()->text(0).split(" ");
	for (int i = 0; i < portCount; i++)
	{
		if (m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
			.portList.at(i).portName.c_str() == ui.treeWidget->currentItem()->parent()->parent()->text(0))
		{
			int protCount = m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
				.portList.at(i).protList.size();
			for (int m = 0; m < protCount; m++)
			{
				if (m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
					.portList.at(i).protList.at(m).protocolName.c_str() == ui.treeWidget->currentItem()->parent()->text(0))
				{
					int msgCount = m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
						.portList.at(i).protList.at(m).messgeList.size();
					for (int j = 0; j < msgCount; j++)
					{
						if (m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
							.portList.at(i).protList.at(m).messgeList.at(j).messageName.c_str() == strList.at(0)
							&& ui.treeWidget->currentItem()->parent()->child(j) == ui.treeWidget->currentItem())
						{
							m_deviceDataManager->m_deviceList[ui.treeWidget->topLevelItem(0)->text(0)]
								.portList[i].protList[m].messgeList[j].messageP = QString::fromLocal8Bit("����").toStdString();
							m_deviceDataManager->UpdateAll();
							return;
						}

					}
				}
			}

		}
	}
}
//�Ҽ�ѡ����ʱ�����Ĳۺ���
void DeviceManagerWidget::OnSubscript()
{
	//��ȡ�����˵��ж˿ڵ�����
	int portCount = m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
		.portList.size();
	//�ָ������ַ���
	QStringList strList = ui.treeWidget->currentItem()->text(0).split(" ");
	for (int i = 0; i < portCount; i++)
	{
		if (m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
			.portList.at(i).portName.c_str() == ui.treeWidget->currentItem()->parent()->parent()->text(0))
		{
			int protCount = m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
				.portList.at(i).protList.size();
			for (int m = 0; m < protCount; m++)
			{
				if (m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
					.portList.at(i).protList.at(m).protocolName.c_str() == ui.treeWidget->currentItem()->parent()->text(0))
				{
					int msgCount = m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
						.portList.at(i).protList.at(m).messgeList.size();
					for (int j = 0; j < msgCount; j++)
					{
						if (m_deviceDataManager->m_deviceList.value(ui.treeWidget->topLevelItem(0)->text(0))
							.portList.at(i).protList.at(m).messgeList.at(j).messageName.c_str() == strList.at(0)
							&& ui.treeWidget->currentItem()->parent()->child(j) == ui.treeWidget->currentItem())
						{
							m_deviceDataManager->m_deviceList[ui.treeWidget->topLevelItem(0)->text(0)]
								.portList[i].protList[m].messgeList[j].messageP = QString::fromLocal8Bit("����").toStdString();
							m_deviceDataManager->UpdateAll();
							return;
						}
					}
				}
			}

		}
	}
}
//˫�����ؼ������Ĳۺ���
void DeviceManagerWidget::OnItemDoubleClick()
{
	if (ui.treeWidget->currentIndex().row() != -1)
	{

		if (ui.treeWidget->currentItem()->data(0, Qt::UserRole).toString() == "messageName")
		{
			emit DoubleClicked(m_oldDevName, ui.treeWidget->currentItem()->parent()->text(0), ui.treeWidget->currentItem()->text(0));
		}
		else if (ui.treeWidget->currentItem()->data(0, Qt::UserRole).toString() == "messageProp")
		{
			emit DoubleClicked(m_oldDevName, ui.treeWidget->currentItem()->parent()->parent()->text(0), ui.treeWidget->currentItem()->parent()->text(0));
		}
		else
		{
			return;
		}

	}

}

//���÷������Ĳۺ���
void DeviceManagerWidget::SetAction()
{
	m_publish = new QAction(QString::fromLocal8Bit("����"), this);
	connect(m_publish, SIGNAL(triggered()), this, SLOT(OnPublish()));
	m_subscript = new QAction(QString::fromLocal8Bit("����"), this);
	connect(m_subscript, SIGNAL(triggered()), this, SLOT(OnSubscript()));
}
