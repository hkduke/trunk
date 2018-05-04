#include "ItemFollowOther.h"
#include <QSpinBox>
#include <QStandardItemModel>
#include <QLineEdit>
#include <limits> 
ItemFollowOther::ItemFollowOther(QObject *parent)
	: QItemDelegate(parent)
{
}

ItemFollowOther::~ItemFollowOther()
{
}

QWidget * ItemFollowOther::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (index.model()->index(index.row(), 1).data() == "int")
	{
		QSpinBox* editor = new QSpinBox(parent);
		editor->setMaximum(std::numeric_limits<int>::max());
		((QStandardItemModel*)index.model())->setData(index,0);
		return editor;
	}
	else if (index.model()->index(index.row(), 1).data() == "double")
	{
			QDoubleSpinBox* editor = new QDoubleSpinBox(parent);
			editor->setMaximum(std::numeric_limits<double>::max());
			((QStandardItemModel*)index.model())->setData(index,0.0);
			return editor;
	}
	else if (index.model()->index(index.row(), 1).data() == "float")
	{
		QDoubleSpinBox* editor = new QDoubleSpinBox(parent);
		editor->setMaximum(std::numeric_limits<float>::max());
		((QStandardItemModel*)index.model())->setData(index, 0.0);
		return editor;
	}
	else
	{
		return new QLineEdit(parent);
	}
}
