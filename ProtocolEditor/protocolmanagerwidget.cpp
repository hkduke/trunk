#include "protocolmanagerwidget.h"
#include <QDebug>
#include <QTreeWidgetItem>
#include <QMessageBox>
/*
	���ܣ����캯������ʼ��Э������ڵ�����
	��Ҫ���������ı��������������Ĳ˵�ѡ�������źţ��۵�����
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
	���ܣ���������
*/
ProtocolManagerWidget::~ProtocolManagerWidget()
{

}
/*
	���ܣ��������ݹ��������洢�޸ĵ��ļ�
*/

void ProtocolManagerWidget::SetDataManager(xlDataManager* manager)
{
	this->m_manager = manager;
	ui.treeWidget->setDataManager(manager);
	setSLot();
}

/*
	���ܣ����ص�ǰ�༭��Э�����ƣ����ⲿ��ʹ��
*/

QString ProtocolManagerWidget::GetCurrentProtName()
{
	return oldProtocolName;
}
//��ո��ؼ�����
void ProtocolManagerWidget::clear()
{
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.treeWidget->clear();
}
//������زۺ���
//Э�����޸ģ�Э��ע�ͣ����ؼ�˫���ۺ���
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
			QMessageBox::critical(this, QString::fromLocal8Bit("������ʾ"), QString::fromLocal8Bit("�������Ʋ���Ϊ�ջ��ظ�������������"));
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
