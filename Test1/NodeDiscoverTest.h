#pragma once
#include <iostream>
#include <vector>
#include <QtWidgets/QMainWindow>
#include "ui_NodeDiscoverTest.h"
#include "../PackageTypeManager/PackManager.h"
#include "../Core/Any.h"
#include <QTimer>
//#include "WgtProperty.h"
class WgtProperty;
class BasePackage;
class NodeDiscoverTest : public QMainWindow
{
	Q_OBJECT

public:
	NodeDiscoverTest(QWidget *parent = Q_NULLPTR);

	static void recv(BasePackage* parement);

signals:
	void sigRecv(const QString &);
	//std::vector<NetCom::Any> m_vector;
public slots:
	void on_btnSend_clicked();
	void on_btnSelectFile_clicked();
	void on_btnSendFile_clicked();
	void on_cbCycle_stateChanged(int);
	void OnSendFile();
	void OnTest();

	void onItemChenged(QTableWidgetItem * item);
private:

	void initTableWidget();

	Ui::NodeDiscoverTestClass ui;
	QString m_file;

	PackManager *m_packManager;

	WgtProperty * m_wgtProperty;

	QTimer * m_timer;
	QTimer * m_cycalTimer;
};
