#pragma once
#include "customtreewidgetbase.h"
class ReceiveTreeWidget :
	public CustomTreeWidgetBase
{
public:
	ReceiveTreeWidget(QWidget*);
	~ReceiveTreeWidget(void);

	void dragEnterEvent(QDragEnterEvent *);

	void dragMoveEvent(QDragMoveEvent *);

	void dropEvent(QDropEvent *);
};

