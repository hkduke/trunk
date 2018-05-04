#ifndef DEVICEMANAGERWIDGET_H
#define DEVICEMANAGERWIDGET_H

#include <QWidget>
#include "ui_devicemanagerwidget.h"
#include "devicdatamanager.h"
#include "xlDataManager.h"
#include <QMenu>
class DeviceManagerWidget : public QWidget
{
	Q_OBJECT

public:
	DeviceManagerWidget(QWidget *parent = 0);
	~DeviceManagerWidget();

	void clear();

	void SetDataManger(DevicDataManager* dev,xlDataManager* datManger);

	void SetProtManager();

	QString GetCurrentDevName();	


private:

	void SetAction();

private:
	Ui::DeviceManagerWidget ui;
	QString m_oldDevName;
	QString m_newDevName;
	QString m_oldDevExt;
	QString m_newDevExt;
	DevicDataManager* m_deviceDataManager;
	xlDataManager* m_dataManager;
	QAction* m_publish;
	QAction* m_subscript;
	QMenu* m_popMenu;

public slots:
	void SetTreeWidget(QString devName);

	void UpDateWidget();

	void Clear();

	void OnNameChanged();

	void OnExtChanged();

	void OnCustomContextMenu(QPoint);

	void OnPublish();
	
	void OnSubscript();

	void OnItemDoubleClick();

signals:

	void DoubleClicked(QString devName,QString protName,QString msgName);
};

#endif // DEVICEMANAGERWIDGET_H
