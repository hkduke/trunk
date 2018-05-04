#pragma once

#include <QItemDelegate>

class ItemFollowOther : public QItemDelegate
{
	Q_OBJECT

public:
	ItemFollowOther(QObject *parent);
	~ItemFollowOther();

	virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index) const override;

};
