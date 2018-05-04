#include "protocolmanagerwidget.h"
#include <QDebug>
#include <QTreeWidgetItem>
#include <QMessageBox>
/*
	功能：构造函数，初始化协议管理窗口的数据
	主要负责设置文本过滤器，上下文菜单选项和相关信号，槽的连接
*/
ProtocolManagerWidget::ProtocolManagerWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z_$][a-zA-Z0-9_$]*"), this));
	ui.treeWidget->setHeaderHidden(true);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(OnContextMenu(QPoint)));
}
/*
	功能：析构函数
*/
ProtocolManagerWidget::~ProtocolManagerWidget()
{

}
/*
	功能：设置数据管理器，存储修改的文件
*/

void ProtocolManagerWidget::SetDataManager(xlDataManager* manager)
{
	this->m_manager = manager;
	ui.treeWidget->setDataManager(manager);
	setSLot();
}

/*
	功能：返回当前编辑的协议名称，供外部类使用
*/

QString ProtocolManagerWidget::GetCurrentProtName()
{
	return oldProtocolName;
}
//清空各控件内容
void ProtocolManagerWidget::clear()
{
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.treeWidget->clear();
}
//设置相关槽函数
//协议名修改，协议注释，树控件双击槽函数
void ProtocolManagerWidget::setSLot()
{
	connect(ui.lineEdit, SIGNAL(editingFinished()), this, SLOT(OnProtocolNameChanged()));
	connect(ui.lineEdit_2, SIGNAL(editingFinished()), this, SLOT(OnProtocolExtChanged()));
	connect(ui.treeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)),
		this, SLOT(OnItemDouble(QTreeWidgetItem *, int)));
}

void ProtocolManagerWidget::OnProtocolNameChanged()
{
	qDebug() << "enter";
	if (ui.lineEdit->isModified())
	{
		if (oldProtocolName.isEmpty())
		{
			return;
		}
		QString tempProtocolName = ui.lineEdit->text().trimmed();
		if (tempProtocolName == oldProtocolName)
		{
			return;
		}
		else if (m_manager->ProtocolIsExsit(tempProtocolName) || tempProtocolName.isEmpty())
		{
			QMessageBox::critical(this, QString::fromLocal8Bit("错误提示"), QString::fromLocal8Bit("报文名称不能为空或重复，请重新命名"));
			ui.lineEdit->setText(oldProtocolName);
			return;
		}
		else
		{
			newProtocolName = tempProtocolName;
			m_manager->updataProtocol_ProtocolName(oldProtocolName, newProtocolName);
			oldProtocolName = newProtocolName;
			upDateTreeView(oldProtocolName);
		}
	}
}



void ProtocolManagerWidget::OnProtocolExtChanged()
{
	m_manager->protList[oldProtocolName].ProtExt = ui.lineEdit_2->text().trimmed().toStdString();
	m_manager->UpDataProtocol();
}

void ProtocolManagerWidget::upDateTreeView(QString protName)
{
	qDebug() << protName;
	if (protName.isEmpty())
	{
		return;
	}
	ui.treeWidget->clear();
	QTreeWidgetItem* rootitem = new QTreeWidgetItem(ui.treeWidget);
	oldProtocolName = protName;
	newProtocolName = protName;
	rootitem->setExpanded(true);
	rootitem->setText(0, protName);
	ui.lineEdit->setText(protName);
	ui.lineEdit_2->setText(m_manager->protList[protName].ProtExt.c_str());
	ui.treeWidget->addTopLevelItem(rootitem);
	QList<std::string> messageStringList = m_manager->protList[protName].messages;
	for (int i = 0; i < m_manager->protList[protName].messages.size(); i++)
	{
		QTreeWidgetItem* secondItem;
		secondItem = new QTreeWidgetItem(rootitem);
		secondItem->setExpanded(true);
		secondItem->setText(0, messageStringList.at(i).c_str());
		secondItem->setData(0, Qt::UserRole, "messageName");
		int propNumber = m_manager->messageList[messageStringList.at(i).c_str()].propList.size();
		QStringList propList = m_manager->GetMessagePropStringFormat(messageStringList.at(i).c_str());
		for (int j = 0; j < propList.size(); j++)
		{
			QTreeWidgetItem* thirdItem;
			thirdItem = new QTreeWidgetItem(secondItem);
			thirdItem->setText(0, propList.at(j));
			thirdItem->setData(0, Qt::UserRole, "propName");
		}
	}

}

void ProtocolManagerWidget::OnItemDouble(QTreeWidgetItem* item, int rowNumber)
{
	if (item->data(0, Qt::UserRole).toString() == "propName")
	{
		emit GotoMessageEditor(item->parent()->text(0));
	}
	else if (item->data(0, Qt::UserRole).toString() == "messageName")
	{
		emit GotoMessageEditor(item->text(0));
	}
	else
	{
		return;
	}
}

void ProtocolManagerWidget::upDateTreeView()
{
	upDateTreeView(oldProtocolName);
}
