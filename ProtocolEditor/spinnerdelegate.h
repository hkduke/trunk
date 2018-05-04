#ifndef SPINNERDELEGATE_H
#define SPINNERDELEGATE_H

#include <QItemDelegate>
//此类主要是根据类型设置默认值的控件类型
class SpinnerDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	SpinnerDelegate(QObject *parent);
	~SpinnerDelegate();
	//重写控件创建函数
	virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
	
};

#endif // SPINNERDELEGATE_H
