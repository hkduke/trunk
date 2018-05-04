#include "spinnerdelegate.h"
#include <QSpinBox>
SpinnerDelegate::SpinnerDelegate(QObject *parent)
	: QItemDelegate(parent)
{

}

SpinnerDelegate::~SpinnerDelegate()
{

}

QWidget * SpinnerDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	QSpinBox* editor=new QSpinBox(parent);
	editor->setMaximum(20000000);
	QString typeStr=index.model()->index(index.row(), 1).data().toString();
	if (typeStr == "int" || typeStr == "long" || typeStr == "double" || typeStr == "float")
	{
		editor->setEnabled(false);
	}
	else
	{
		editor->setEnabled(true);
	}
	return editor;
}
