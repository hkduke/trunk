#include "treeitemminedata.h"


TreeItemMineData::TreeItemMineData():QMimeData()
{
	m_pDragItem=NULL;
}

TreeItemMineData::~TreeItemMineData()
{

}

QStringList TreeItemMineData::formats() const
{
	return m_format;
}

QVariant TreeItemMineData::retrieveData(const QString &mimetype, QVariant::Type preferredType) const
{
	if(mimetype=="ItemMimeData")
	{
		return m_pDragItem;
	}
	else
	{
		return QMimeData::retrieveData(mimetype,preferredType);
	}
}

void TreeItemMineData::setDragData(QString mimeType,QTreeWidgetItem* pItem)
{
	m_format<<mimeType;
	m_pDragItem=pItem;
}

const QTreeWidgetItem* TreeItemMineData::DragItemData() const
{
	return m_pDragItem;
}
