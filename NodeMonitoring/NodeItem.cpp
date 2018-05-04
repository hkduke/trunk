#include "NodeItem.h"
#include <QLabel>
NodeItem::NodeItem(QWidget *parent)
	: QWidget(parent)
{
	m_isactive = true;
	resize(100, 30);
	m_QHBoxLayout = new QHBoxLayout;
	setLayout(m_QHBoxLayout);
}

NodeItem::~NodeItem()
{
}

void NodeItem::addItem(QString id, bool isactive)
{
	QLabel * labelleft = new QLabel(id);
	m_QHBoxLayout->addWidget(labelleft);
	m_rigicon = new QLabel(id);
	m_QHBoxLayout->addWidget(m_rigicon);
	change(isactive);
}

void NodeItem::change(bool b)
{
	m_isactive = b;
	if (b)
	{
		QPixmap pix;
		
		pix.load("light.PNG");
		pix = pix.scaled(QSize(300, 100), Qt::KeepAspectRatio);
		m_rigicon->setPixmap(pix);
	}
	else
	{
		QPixmap pix;
		pix.load("night.PNG");
		pix = pix.scaled(QSize(300, 100), Qt::KeepAspectRatio);
		m_rigicon->setPixmap(pix);
	}
}
+-