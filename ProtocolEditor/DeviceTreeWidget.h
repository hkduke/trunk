#pragma once
#include "customtreewidgetbase.h"
class DeviceTreeWidget :
	public CustomTreeWidgetBase
{
public:
	DeviceTreeWidget(QWidget*);
	~DeviceTreeWidget(void);

	void dragEnterEvent(QDragEnterEvent *);

	void dragMoveEvent(QDragMoveEvent *);

	void dropEvent(QDropEvent *);
};

