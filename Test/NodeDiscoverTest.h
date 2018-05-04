#pragma once
#include <iostream>
#include <vector>
#include <QtWidgets/QMainWindow>
#include "ui_NodeDiscoverTest.h"
#include "../Core/Any.h"
class NodeDiscoverTest : public QMainWindow
{
	Q_OBJECT

public:
	NodeDiscoverTest(QWidget *parent = Q_NULLPTR);

	//std::vector<NetCom::Any> m_vector;
	public slots:
	void OnPushButtonDown();
	void OnSendFile();
	void OnTest();
	//void Init();
private:
	Ui::NodeDiscoverTestClass ui;
	QString m_file;
};
