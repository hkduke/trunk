#pragma once
#include "customtreewidgetbase.h"
#include <xlDataManager.h>
class DeviceReceiveTreeWidget :
	public CustomTreeWidgetBase
{
	Q_OBJECT
public:
	DeviceReceiveTreeWidget(QWidget*);
	~DeviceReceiveTreeWidget(void);

	void dragEnterEvent(QDragEnterEvent *);

	void dragMoveEvent(QDragMoveEvent *);

	void dropEvent(QDropEvent *);

	void setDataManager(xlDataManager* dataManager);
private:

	xlDataManager* m_dataManager;


};

