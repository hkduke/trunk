#pragma once
#include "customtreewidgetbase.h"
#include "devicdatamanager.h"
#include "xlDataManager.h"
class ProtocolReceiveTreeWidget :
	public CustomTreeWidgetBase
{
	Q_OBJECT
public:
	ProtocolReceiveTreeWidget(QWidget*);
	~ProtocolReceiveTreeWidget(void);

	void dragEnterEvent(QDragEnterEvent *);

	void dragMoveEvent(QDragMoveEvent *);

	void dropEvent(QDropEvent *);

public:

	void SetDataManager(DevicDataManager* devManager);

	void SetModeManager(xlDataManager* dataManager);

private:
	
	DevicDataManager* m_devManager;
	xlDataManager* m_dataManager;

signals:
	//�϶��¼�������ϣ����ʹ��ź�
	void DragMoveFinished();
};

