#ifndef MESSAGEEDITORWIDGET_H
#define MESSAGEEDITORWIDGET_H

#include <QWidget>
#include "ui_messageeditorwidget.h"
#include "xlDataManager.h"
#include <QStandardItemModel>
#include <QMenu>
#include "devicdatamanager.h"

class MessageEditorWidget : public QWidget
{
	Q_OBJECT

public:
	MessageEditorWidget(QWidget *parent = 0);

	~MessageEditorWidget();

	void setDataManager(xlDataManager* pManager);

	void upDateTreeView(QString messageName);	
	
	bool on_saveModel();

	QString GetCurrentMessageName();

	void clear();

	void SetDevManager(DevicDataManager* devManager);

	bool IsDeviceData();

private:
	Ui::MessageEditorWidget ui;

	xlDataManager* manager;

	QStandardItemModel* model;

	QString oldMessageName;

	QString NewMessageName;

	QString oldMessageExt;

	QString NewMessageExt;

	QMenu* m_popMenu;

	QAction* m_action_addNewProp;

	QAction* m_action_deleteProp;
	
	DevicDataManager* m_deviceDataManager;

	QString m_oldDevName;


	QString m_oldProtName;

	bool m_isDeviceData;

private:

	void setSLot();

	void setAction();

	void UnSetAction();

	void SetDevSlot();

	void UnSetDevSlot();
public slots:

	void OnMessagNameLineEditorFinished();

	void onMessageLineEditorChange();
	
	void OnContextMenu(QPoint);

	void on_addNewProp();

	void on_delProp();

	void UpdateDevDate(QString devName,QString protName,QString msgName);


signals:

	void MessageNameChange(QString,QString);

	void MessageExtChange(QString,QString);


};

#endif // MESSAGEEDITORWIDGET_H
