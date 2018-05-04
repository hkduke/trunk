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
	void initUI(); //��ʼ�����Դ���

	public slots:
		//item slots
		void slot_valuechanged(QtProperty * property, const QVariant &val);
		void slot_updateproperty(CPropertyList list);
		//void slot_updateproperty(CRenderModelBase * renderBase); //��������

		//scene slots
		//void slot_scene_valuechanged(QtProperty *property, const QVariant &val);
		//void slot_scene_updateproperty();

private:
	void addSubProp(QtVariantProperty *varitem, CShapeProperty* prop);
	
	
	//item���Կ�
	QtVariantPropertyManager *shape_Variant_property_manager; //item���Թ�����
	QList<QtProperty*> m_propertyList; //item �����б�
	QtTreePropertyBrowser *shape_property_editor; //item���Ա༭��
	QtVariantEditorFactory *shape_property_factory; //item���Թ���

	//QMap<QtVariantProperty*, ModelPara *> m_propertyMap;

	//�������Կ�
// 	QtVariantPropertyManager *scene_property_manager; //�������Թ�����
// 	QList<QtProperty*> m_scencepropertyList;//���������б�
// 	QtTreePropertyBrowser *scene_property_editor; //�������Թ�����
// 	QtVariantEditorFactory *scene_property_factory;//�������Թ���
};

#endif // DOCKPROPERTY_H
