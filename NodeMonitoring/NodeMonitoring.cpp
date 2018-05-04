#include "NodeMonitoring.h"
#include "../Core/Framework.h"
#include "../Core/ResourceManager.h"
extern  NodeMonitoring *g_w;
using namespace  NetCom;
NodeMonitoring::NodeMonitoring(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_QVBoxLayout = new QVBoxLayout;
	ui.widget2->setLayout(m_QVBoxLayout);
}

void NodeMonitoring::addItem(QString id)
{
	NodeItem * node = new NodeItem;

	node->addItem(id,true);
	m_nodeManager.insert(id, node);
	m_QVBoxLayout->addWidget(node);
}

void NodeMonitoring::writeMessage(QString msg)
{
	ui.textEdit->append(msg + "\n");
}
namespace NetCom
{
	void NodeTest(int id, bool b)
	{
		if (b)
		{
			g_w->addItem(QString::number(id));
		}
		else
		{
			QMap<QString, NodeItem*>::const_iterator i = g_w->m_nodeManager.find(QString::number(id));
			if (i != g_w->m_nodeManager.end())
			{
				NodeItem* node = i.value();
				node->change(false);
			}
		}
	}
}

void NodeMonitoring::init()
{
	Framework::GetInstance().Init();
	Framework::GetInstance().GetResourceManager()->RegisterFunction(NetCom::NodeTest);
}
