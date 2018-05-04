#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
class NodeItem : public QWidget
{
	Q_OBJECT

public:
	NodeItem(QWidget *parent = Q_NULLPTR);
	~NodeItem();
	void addItem(QString id, bool isactive);
	void change(bool b);
	QString m_nodeid;
	bool m_isactive;
	QHBoxLayout * m_QHBoxLayout;
	QLabel * m_rigicon;
};
