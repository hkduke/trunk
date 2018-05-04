#ifndef DOCKPROPERTY_H
#define DOCKPROPERTY_H

#include <QWidget>
#include "shapeproperty.h"
class QtTreePropertyBrowser;
class QtVariantPropertyManager;
class QtEnumPropertyManager;
class QtVariantEditorFactory;
class QtProperty;
class QtVariantProperty;
class CShapeProperty;

class WgtProperty : public QWidget
{
	Q_OBJECT

public:
	WgtProperty(QWidget * parent = 0);
	~WgtProperty();
	void initUI(); //初始化属性窗口

	public slots:
		//item slots
		void slot_valuechanged(QtProperty * property, const QVariant &val);
		void slot_updateproperty(CPropertyList list);
		//void slot_updateproperty(CRenderModelBase * renderBase); //更新属性

		//scene slots
		//void slot_scene_valuechanged(QtProperty *property, const QVariant &val);
		//void slot_scene_updateproperty();

private:
	void addSubProp(QtVariantProperty *varitem, CShapeProperty* prop);
	
	
	//item属性框
	QtVariantPropertyManager *shape_Variant_property_manager; //item属性管理器
	QList<QtProperty*> m_propertyList; //item 属性列表
	QtTreePropertyBrowser *shape_property_editor; //item属性编辑器
	QtVariantEditorFactory *shape_property_factory; //item属性工厂

	//QMap<QtVariantProperty*, ModelPara *> m_propertyMap;

	//场景属性框
// 	QtVariantPropertyManager *scene_property_manager; //场景属性管理器
// 	QList<QtProperty*> m_scencepropertyList;//场景属性列表
// 	QtTreePropertyBrowser *scene_property_editor; //场景属性管理器
// 	QtVariantEditorFactory *scene_property_factory;//场景属性工厂
};

#endif // DOCKPROPERTY_H
