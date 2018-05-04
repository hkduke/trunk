#ifndef ITEMSELECTDELEGATE_H
#define ITEMSELECTDELEGATE_H

#include <QItemDelegate>
//����������ѡ��ί����
class ItemSelectDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	ItemSelectDelegate(QObject *parent=nullptr);
	~ItemSelectDelegate();
	//��д�ؼ���������
	virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	//�ؼ�ֵ����ģ�͵ĺ���
	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;
	//ģ�͵�ֵ����ؼ��ĺ���
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;


private:
	
};

#endif // ITEMSELECTDELEGATE_H
