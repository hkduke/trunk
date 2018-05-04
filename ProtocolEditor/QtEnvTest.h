#ifndef QTENVTEST_H
#define QTENVTEST_H
//���ļ�Ϊ�����ڽ����ͷ�ļ�
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
	xlDataManager* m_dataManager;//xml��������ݹ�����
	QMenu* m_popMenu;//�����˵�

	QAction* m_action_addDevice;//�豸����action
	QAction* m_action_editDevice;//�豸�༭action
	QAction* m_action_deleteDevice;//�豸ɾ��action

	QAction* m_action_addNewMessage;//��������action

	QAction* m_action_editMessage;//���ı༭action

	QAction* m_action_deleteMessage;//����ɾ��action

	MessageEditorWidget* messageEditor;//���ı༭����

	ProtocolManagerWidget* protocolManager;//Э��༭����

	DeviceManagerWidget* deviceManager;//�豸�༭����

	QAction* m_action_addNewProtocol;//Э������action

	QAction* m_action_editProtocol;//Э��༭action

	QAction* m_action_deleteProtocol;//Э��ɾ��action

	QAction* m_actin_saveSignal;//�����豸�ڵ�

	bool isMsgFirst;//�Ƿ��ǵ�һ�δ�xml

	bool isNewOpen;//�Ƿ����½�

	QString currentFilePath;//��ǰ���ļ�·��

	DevicDataManager* m_deviceDataManager;//�豸�������

	QAction* m_action_portAdd;//���Ӷ˿�

	QAction* m_action_portEditor;//�޸Ķ˿�

	QAction* m_action_portDel;//ɾ���˿�

	QAction* m_action_devProtDel;//ɾ���豸���е�Э��


public slots:

	void on_trigger_open();//�򿪲˵��ۺ���

	void on_trigger_save();//����˵��ۺ���

	void on_trigger_deviceOpen();//�豸���xmlЭ��򿪲ۺ���

	void on_trigger_deviceSave();//�����豸����

	bool on_slot_messageManager(QPoint);////�ڱ���treeWdiget���Ҽ�ʱ�����˲˵�

	bool on_slot_Device(QPoint point);////���豸treeWdiget���Ҽ�ʱ�����˲˵�

	void on_addNewMessage();//�����±���

	void on_delMessage();//ɾ������

	void on_editMessage();//�༭����

	void on_addDevice();//�����豸�ڵ�

	void on_editDevice();//�༭�豸�ڵ�

	void on_deleteDevice();//ɾ���豸�ڵ�

	void on_trigger_saveWord();//����Word��ʽЭ��

	void setProtList();//��ʾЭ���б�

	void setMessageList();//��ʾ�����б�

	void setDeviceList();//��ʾ�豸�ڵ��б�

	void on_addNewProtocol();//������Э��

	void on_delProtocol();//ɾ����Э��

	void on_editProtocol();//�༭Э��

	void on_slot_ProtocolManager(QPoint);//��Э�����ؼ��ϵ����Ҽ��˵�

	void OnTabChanged(int rowNumber);//Tabҳ�л�ʱ����

	void OnGotoMessageEditor(QString);//����豸�ؼ���Э��ؼ����б༭����

	void OnEditDevMsg(QString,QString,QString);//�༭�豸����

	void OnSaveSignalDev();//��ѡ�񱣴�ڵ�Э��

	void OnPortNew();//���Ӷ˿�

	void OnPortEditor();//�༭�˿�

	void OnPortDel();//ɾ���˿�
private:
	void creatContexMenuAction();//����actions

	void SetSlot();//���òۺ�������

	void OpenEmptyManager();//�½���Э��

	void clearWidget();//��տؼ�

protected:
	virtual void closeEvent(QCloseEvent *event) override;//�ر��¼��������

};

#endif // QTENVTEST_H
