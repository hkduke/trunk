#ifndef TREEITEMMINEDATA_H
#define TREEITEMMINEDATA_H
//mimetype∂®“Â
#include <QMimeData>
#include <QTreeWidgetItem>
#include <QString>
class TreeItemMineData : public QMimeData
{
	Q_OBJECT

public:
	TreeItemMineData();
	~TreeItemMineData();

	virtual QStringList formats() const;

	virtual QVariant retrieveData(const QString &mimetype, QVariant::Type preferredType) const;

	void setDragData(QString mimeType,QTreeWidgetItem* pItem);

	const QTreeWidgetItem* DragItemData()const;
private:
	const QTreeWidgetItem* m_pDragItem;
	QStringList m_format;
};

#endif // TREEITEMMINEDATA_H
