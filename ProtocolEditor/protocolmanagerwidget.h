#ifndef PROTOCOLMANAGERWIDGET_H
#define PROTOCOLMANAGERWIDGET_H

#include <QWidget>
#include "ui_protocolmanagerwidget.h"
#include <QMenu>
#include <xlDataManager.h>
class ProtocolManagerWidget : public QWidget
{
	Q_OBJECT

public:
	ProtocolManagerWidget(QWidget *parent = 0);
	~ProtocolManagerWidget();

	void SetDataManager(xlDataManager* manager);

	QString GetCurrentProtName();

	void clear();
private:
	Ui::ProtocolManagerWidget ui;
	xlDataManager* m_manager;
	QString oldProtocolName;
	QString newProtocolName;

private:
	void setSLot();


public slots:

	void OnProtocolNameChanged();

	void OnProtocolExtChanged();

	void upDateTreeView(QString messageName);

	void OnItemDouble(QTreeWidgetItem* item, int rowNumber);

	void upDateTreeView();
signals:

	void GotoMessageEditor(QString);
};

#endif // PROTOCOLMANAGERWIDGET_H
