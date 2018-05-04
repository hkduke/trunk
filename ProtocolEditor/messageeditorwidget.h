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
	//构造函数
	MessageEditorWidget(QWidget *parent = 0);

	~MessageEditorWidget();
	//设置数据管理器
	void setDataManager(xlDataManager* pManager);
	//更新树控件
	void upDateTreeView(QString messageName);	
	//保存更改的内容
	bool on_saveModel();
	//获取当前编辑的报文的名称
	QString GetCurrentMessageName();
	//初始化树控件
	void clear();
	//设置设备信息数据管理器
	void SetDevManager(DevicDataManager* devManager);
	//检查是否是修改设备信息
	bool IsDeviceData();

private:
	Ui::MessageEditorWidget ui;
	//数据管理器
	xlDataManager* manager;

	QStandardItemModel* model;
	//旧报文名称
	QString oldMessageName;
	//新报文名称
	QString NewMessageName;
	//旧的报文注释
	QString oldMessageExt;
	//新报文注释
	QString NewMessageExt;
	//弹出菜单
	QMenu* m_popMenu;
	//增加属性Action
	QAction* m_action_addNewProp;
	//删除属性Action
	QAction* m_action_deleteProp;
	//设备数据管理器
	DevicDataManager* m_deviceDataManager;
	//旧的设备名称
	QString m_oldDevName;

	//旧协议名称
	QString m_oldProtName;
	//端口名称
	QString m_portName;
	//是否在编辑设备数据
	bool m_isDeviceData;

private:
	//设置信号槽函数
	void setSLot();
	//设置弹出菜单
	void setAction();
	//解除信号槽函数
	void UnSetAction();
	//设置设备数据相关槽函数
	void SetDevSlot();
	//解除设备数据相关槽函数
	void UnSetDevSlot();
public slots:
	//报文名称修改后触发的槽
	void OnMessagNameLineEditorFinished();
	//报文注释修改后触发的槽
	void onMessageLineEditorChange();
	//右键弹出菜单触发的槽
	void OnContextMenu(QPoint);
	//选择增加触发的槽
	void on_addNewProp();
	//选择删除触发的槽
	void on_delProp();
	//更新设备数据触发的槽
	void UpdateDevDate(QString devName, QString portName, QString protName,QString msgName);


signals:
	//报文名称修改的信号
	void MessageNameChange(QString,QString);

	void MessageExtChange(QString,QString);


};

#endif // MESSAGEEDITORWIDGET_H
