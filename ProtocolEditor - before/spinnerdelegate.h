#ifndef SPINNERDELEGATE_H
#define SPINNERDELEGATE_H

#include <QItemDelegate>
//������Ҫ�Ǹ�����������Ĭ��ֵ�Ŀؼ�����
class SpinnerDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	SpinnerDelegate(QObject *parent);
	~SpinnerDelegate();
	//��д�ؼ���������
	virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
	
};

#endif // SPINNERDELEGATE_H
