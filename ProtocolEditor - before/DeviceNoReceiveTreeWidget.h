#pragma once
#include "customtreewidgetbase.h"

class DeviceNoReceiveTreeWidget :
	public CustomTreeWidgetBase
{
	Q_OBJECT
public:
	DeviceNoReceiveTreeWidget(QWidget*);
	~DeviceNoReceiveTreeWidget(void);

	void mouseMoveEvent(QMouseEvent *);

	void dragEnterEvent(QDragEnterEvent *);

	void dragMoveEvent(QDragMoveEvent *);

	void dropEvent(QDropEvent *);
};

