#ifndef ITEMSELECTDELEGATE_H
#define ITEMSELECTDELEGATE_H

#include <QItemDelegate>
//此类是类型选择委派器
class ItemSelectDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	ItemSelectDelegate(QObject *parent=nullptr);
	~ItemSelectDelegate();
	//重写控件创建函数
	virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	//控件值传入模型的函数
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	//模型的值传入控件的函数
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;


private:
	
};

#endif // ITEMSELECTDELEGATE_H
