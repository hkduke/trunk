#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_NodeMonitoring.h"
#include "NodeItem.h"
#include <QVBoxLayout>
class NodeMonitoring : public QMainWindow
{
	Q_OBJECT

public:
	NodeMonitoring(QWidget *parent = Q_NULLPTR);

	void addItem(QString id);
	void writeMessage(QString msg);
	void init();

	Ui::NodeMonitoringClass ui;
	QMap< QString, NodeItem*> m_nodeManager;
	QVBoxLayout * m_QVBoxLayout;
};

