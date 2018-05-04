#ifndef CUSTOMTREEWIDGETBASE_H
#define CUSTOMTREEWIDGETBASE_H

#include <QTreeWidget>
#include <QMouseEvent>
class CustomTreeWidgetBase : public QTreeWidget
{
	Q_OBJECT

public:
	CustomTreeWidgetBase(QWidget*	parent=nullptr);
	~CustomTreeWidgetBase();
protected:
	virtual void mousePressEvent(QMouseEvent *);

	virtual void mouseReleaseEvent(QMouseEvent *);

	virtual void mouseMoveEvent(QMouseEvent *);

	virtual void dragEnterEvent(QDragEnterEvent *);

	virtual void dragMoveEvent(QDragMoveEvent *);

	virtual void dropEvent(QDropEvent *);

	
	virtual void performDrag();
QPoint m_startDragPoint;
private:

	

	
};

#endif // CUSTOMTREEWIDGETBASE_H
