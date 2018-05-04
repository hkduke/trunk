#ifndef QTENVTEST_H
#define QTENVTEST_H
//本文件为主窗口界面的头文件
#include <QMainWindow>
#include "ui_qtenvtest.h"
#include <QXmlStreamWriter>
#include "xlWriter.h"
#include "xlreader.h"
#include "xlDataManager.h"
#include "messageeditorwidget.h"
#include "devicemanagerwidget.h"
#include "protocolmanagerwidget.h"
#include "devicdatamanager.h"
class QtEnvTest : public QMainWindow
{
	Q_OBJECT

public:
	QtEnvTest(QWidget *parent = 0);

	~QtEnvTest();

private:
	Ui::QtEnvTestClass ui;
	xlDataManager* m_dataManager;//xml的左侧数据管理器
	QMenu* m_popMenu;//弹出菜单

	QAction* m_action_addDevice;//设备增加action
	QAction* m_action_editDevice;//设备编辑action
	QAction* m_action_deleteDevice;//设备删除action

	QAction* m_action_addNewMessage;//报文增加action

	QAction* m_action_editMessage;//报文编辑action

	QAction* m_action_deleteMessage;//报文删除action

	MessageEditorWidget* messageEditor;//报文编辑界面

	ProtocolManagerWidget* protocolManager;//协议编辑界面

	DeviceManagerWidget* deviceManager;//设备编辑界面

	QAction* m_action_addNewProtocol;//协议增加action

	QAction* m_action_editProtocol;//协议编辑action

	QAction* m_action_deleteProtocol;//协议删除action

	QAction* m_actin_saveSignal;//保存设备节点

	bool isMsgFirst;//是否是第一次打开xml

	bool isNewOpen;//是否是新建

	QString currentFilePath;//当前打开文件路径

	DevicDataManager* m_deviceDataManager;//设备管理界面

	QAction* m_action_portAdd;//增加端口

	QAction* m_action_portEditor;//修改端口

	QAction* m_action_portDel;//删除端口

	QAction* m_action_devProtDel;//删除设备树中的协议


public slots:

	void on_trigger_open();//打开菜单槽函数

	void on_trigger_save();//保存菜单槽函数

	void on_trigger_deviceOpen();//设备相关xml协议打开槽函数

	void on_trigger_deviceSave();//保存设备数据

	bool on_slot_messageManager(QPoint);////在报文treeWdiget点右键时弹出此菜单

	bool on_slot_Device(QPoint point);////在设备treeWdiget点右键时弹出此菜单

	void on_addNewMessage();//增加新报文

	void on_delMessage();//删除报文

	void on_editMessage();//编辑报文

	void on_addDevice();//增加设备节点

	void on_editDevice();//编辑设备节点

	void on_deleteDevice();//删除设备节点

	void on_trigger_saveWord();//保存Word格式协议

	void setProtList();//显示协议列表

	void setMessageList();//显示报文列表

	void setDeviceList();//显示设备节点列表

	void on_addNewProtocol();//增加新协议

	void on_delProtocol();//删除新协议

	void on_editProtocol();//编辑协议

	void on_slot_ProtocolManager(QPoint);//在协议树控件上弹出右键菜单

	void OnTabChanged(int rowNumber);//Tab页切换时动作

	void OnGotoMessageEditor(QString);//点击设备控件和协议控件进行编辑报文

	void OnEditDevMsg(QString,QString,QString);//编辑设备报文

	void OnSaveSignalDev();//有选择保存节点协议

	void OnPortNew();//增加端口

	void OnPortEditor();//编辑端口

	void OnPortDel();//删除端口
private:
	void creatContexMenuAction();//创建actions

	void SetSlot();//设置槽函数连接

	void OpenEmptyManager();//新建空协议

	void clearWidget();//清空控件

protected:
	virtual void closeEvent(QCloseEvent *event) override;//关闭事件处理程序

};

#endif // QTENVTEST_H
