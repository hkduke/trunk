#pragma once
#include "customtreewidgetbase.h"
class ProtocolTreeWidget :
	public CustomTreeWidgetBase
{
public:
	ProtocolTreeWidget(QWidget*);
	~ProtocolTreeWidget(void);

	void dragEnterEvent(QDragEnterEvent *);

	void dragMoveEvent(QDragMoveEvent *);

	void dropEvent(QDropEvent *);
};

