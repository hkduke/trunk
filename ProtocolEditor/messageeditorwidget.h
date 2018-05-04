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
	//���캯��
	MessageEditorWidget(QWidget *parent = 0);

	~MessageEditorWidget();
	//�������ݹ�����
	void setDataManager(xlDataManager* pManager);
	//�������ؼ�
	void upDateTreeView(QString messageName);	
	//������ĵ�����
	bool on_saveModel();
	//��ȡ��ǰ�༭�ı��ĵ�����
	QString GetCurrentMessageName();
	//��ʼ�����ؼ�
	void clear();
	//�����豸��Ϣ���ݹ�����
	void SetDevManager(DevicDataManager* devManager);
	//����Ƿ����޸��豸��Ϣ
	bool IsDeviceData();

private:
	Ui::MessageEditorWidget ui;
	//���ݹ�����
	xlDataManager* manager;

	QStandardItemModel* model;
	//�ɱ�������
	QString oldMessageName;
	//�±�������
	QString NewMessageName;
	//�ɵı���ע��
	QString oldMessageExt;
	//�±���ע��
	QString NewMessageExt;
	//�����˵�
	QMenu* m_popMenu;
	//��������Action
	QAction* m_action_addNewProp;
	//ɾ������Action
	QAction* m_action_deleteProp;
	//�豸���ݹ�����
	DevicDataManager* m_deviceDataManager;
	//�ɵ��豸����
	QString m_oldDevName;

	//��Э������
	QString m_oldProtName;
	//�˿�����
	QString m_portName;
	//�Ƿ��ڱ༭�豸����
	bool m_isDeviceData;

private:
	//�����źŲۺ���
	void setSLot();
	//���õ����˵�
	void setAction();
	//����źŲۺ���
	void UnSetAction();
	//�����豸������زۺ���
	void SetDevSlot();
	//����豸������زۺ���
	void UnSetDevSlot();
public slots:
	//���������޸ĺ󴥷��Ĳ�
	void OnMessagNameLineEditorFinished();
	//����ע���޸ĺ󴥷��Ĳ�
	void onMessageLineEditorChange();
	//�Ҽ������˵������Ĳ�
	void OnContextMenu(QPoint);
	//ѡ�����Ӵ����Ĳ�
	void on_addNewProp();
	//ѡ��ɾ�������Ĳ�
	void on_delProp();
	//�����豸���ݴ����Ĳ�
	void UpdateDevDate(QString devName, QString portName, QString protName,QString msgName);


signals:
	//���������޸ĵ��ź�
	void MessageNameChange(QString,QString);

	void MessageExtChange(QString,QString);


};

#endif // MESSAGEEDITORWIDGET_H
