#include "itemselectdelegate.h"
#include <QComboBox>
#include <QStandardItemModel>
ItemSelectDelegate::ItemSelectDelegate(QObject *parent)
	: QItemDelegate(parent)
{

}

ItemSelectDelegate::~ItemSelectDelegate()
{

}
//创建控件函数
QWidget * ItemSelectDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QComboBox* editor = new QComboBox(parent);
	editor->addItems(QStringList() << "string" << "int" << "double" << "float"
		<< QString::fromLocal8Bit("bit(大端)") << QString::fromLocal8Bit("bit(小端)"));
	return editor;
}

void ItemSelectDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QComboBox* currentEditor = qobject_cast<QComboBox*>(editor);
	if (currentEditor)
	{
		if (currentEditor->findText(index.data().toString()) == -1)
		{
			currentEditor->addItem(index.data().toString());
		}
	}
}

void ItemSelectDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
	QComboBox* currentEditor = qobject_cast<QComboBox*>(editor);
	int rowNumber = index.row();
	((QStandardItemModel*)index.model())->setData(index, currentEditor->currentText());
	if (currentEditor->currentText() == "int")
	{
		((QStandardItemModel*)index.model())->setData(index.model()->index(rowNumber, 3), 0);
		((QStandardItemModel*)index.model())->setData(index.model()->index(rowNumber, 2), 4);
	}
	else if (currentEditor->currentText() == "double")
	{
		((QStandardItemModel*)index.model())->setData(index.model()->index(rowNumber, 3), 0.0);
		((QStandardItemModel*)index.model())->setData(index.model()->index(rowNumber, 2), 8);
	}
	else if (currentEditor->currentText() == "float")
	{
		((QStandardItemModel*)index.model())->setData(index.model()->index(rowNumber, 3), 0.0);
		((QStandardItemModel*)index.model())->setData(index.model()->index(rowNumber, 2), 4);
	}
	else if (currentEditor->currentText() == QString::fromLocal8Bit("bit(大端)")
		|| currentEditor->currentText() == QString::fromLocal8Bit("bit(小端)"))
	{
		((QStandardItemModel*)index.model())->setData(index.model()->index(rowNumber, 3), 0);
	}
	else
	{
		((QStandardItemModel*)index.model())->setData(index.model()->index(rowNumber, 3), "empty");
	}

}
