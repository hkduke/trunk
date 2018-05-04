#pragma once
#include "customtreewidgetbase.h"
class ProtocolNoReceiveTreeWidget :
	public CustomTreeWidgetBase
{
	Q_OBJECT
public:
	ProtocolNoReceiveTreeWidget(QWidget*);
	~ProtocolNoReceiveTreeWidget(void);

	void mouseMoveEvent(QMouseEvent *);

	void dragEnterEvent(QDragEnterEvent *);

	void dragMoveEvent(QDragMoveEvent *);

	void dropEvent(QDropEvent *);

	void performDrag();

signals:
	
	void ItemMoving();
};

