#include "WgtProperty.h"

#include <QGridLayout>
#include <QDebug>
//#include "CRenderModelBase.h"

#include "qtpropertybrowser\qtpropertymanager.h"
#include "qtpropertybrowser\qttreepropertybrowser.h"
#include "qtpropertybrowser\qtvariantproperty.h"
#include "qtpropertybrowser\qteditorfactory.h"
#include "qtpropertybrowser\shapeproperty.h"

//#include "CMapCanvas.h"
//#include "CMapManager.h"

WgtProperty::WgtProperty(QWidget * parent)
	: QWidget(parent)
{
	initUI();
}

WgtProperty::~WgtProperty()
{
	
}

void WgtProperty::initUI()
{
	setObjectName("WgtProperty");
	resize(300, 400);	
	//item 属性框初始化
	shape_property_editor = new QtTreePropertyBrowser(this);
	shape_property_editor->setAlternatingRowColors(false);
	shape_property_editor->setPropertiesWithoutValueMarked(true);
	shape_Variant_property_manager = new QtVariantPropertyManager(this);
	shape_property_factory = new QtVariantEditorFactory(this);
	shape_property_editor->setFactoryForManager(shape_Variant_property_manager, shape_property_factory);
	connect(shape_Variant_property_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(slot_valuechanged(QtProperty *, const QVariant &)));

	//场景属性框初始化
// 	scene_property_editor = new QtTreePropertyBrowser(this);
// 	scene_property_editor->setAlternatingRowColors(false);
// 	scene_property_manager = new QtVariantPropertyManager(this);
// 	scene_property_factory = new QtVariantEditorFactory(this);
// 	scene_property_editor->setFactoryForManager(scene_property_manager, scene_property_factory);
// 	connect(scene_property_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(slot_scene_valuechanged(QtProperty *, const QVariant &)));

	QVBoxLayout * layout = new QVBoxLayout(this);
	layout->addWidget(shape_property_editor);
}

//propertys
void WgtProperty::slot_valuechanged(QtProperty * prop, const QVariant &val)
{
	QtVariantPropertyManager *manager = dynamic_cast<QtVariantPropertyManager *>(sender());
	if (shape_Variant_property_manager == manager)
	{
// 		QList<QGraphicsItem *> selectItem = CMapManager::instance()->mapCanvas()->scene()->selectedItems();;
// 		int num = selectItem.count();
// 		if(num == 0) return;
// 		CRenderModelBase *renderBase = dynamic_cast<CRenderModelBase *>(selectItem[0]);
// 		if (!renderBase) return;
// 		QString propName = prop->propertyName();
// 
// 		QtVariantProperty * varProp = dynamic_cast<QtVariantProperty*>(prop);
// 		if (m_propertyMap.contains(varProp))
// 		{
// 			ModelPara * para = m_propertyMap.value(varProp);
// 			if (para)
// 			{
// 				para->attrValue = val;
// 			}
// 		}
// 		renderBase->updateProperty(propName, val);
// 		CMapManager::instance()->mapCanvas()->centerOn(renderBase);
	}
}	

void WgtProperty::slot_updateproperty(CPropertyList list)
{
	disconnect(shape_Variant_property_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), 
		this, SLOT(slot_valuechanged(QtProperty *, const QVariant &)));

	qDeleteAll(m_propertyList);
	m_propertyList.clear();

	foreach (CShapeProperty *prop, list)
	{
		QtVariantProperty *varitem = shape_Variant_property_manager->addProperty(prop->type(), prop->propertyName());
		varitem->setValue(prop->value() , &prop->names());
		if (prop->type() == QVariant::Double)
		{
			varitem->setAttribute("minimum", prop->mimimum());
			varitem->setAttribute("maximum", prop->maxmum());
			varitem->setAttribute("singleStep", prop->singleStep());
			varitem->setAttribute("decimals", prop->decimals());
		}
		else if (prop->type() == QVariant::Int)
		{
			varitem->setAttribute("minimum", prop->mimimum());
			varitem->setAttribute("maximum", prop->maxmum());
			varitem->setAttribute("singleStep", prop->singleStep());
		}
		if (!prop->names().isEmpty())
		{
			varitem->setAttribute("enumNames", prop->names());
			varitem->setValue(prop->value());
		}
		if (prop->type() == QtVariantPropertyManager::groupTypeId())
		{
			addSubProp(varitem, prop);
		}
		shape_property_editor->addProperty(varitem);
		m_propertyList << varitem;
	}

	qDeleteAll(list);
	list.clear();

	connect(shape_Variant_property_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), 
		this, SLOT(slot_valuechanged(QtProperty *, const QVariant &)));

}

// void WgtProperty::slot_updateproperty()
// {
// 	disconnect(shape_Variant_property_manager, SIGNAL(valueChanged(QtProperty *, const QVariant &)), 
// 		this, SLOT(slot_valuechanged(QtProperty *, const QVariant &)));
// 
// 	qDeleteAll(m_propertyList);
// 	m_propertyList.clear();
// 
// }

void WgtProperty::addSubProp(QtVariantProperty *varitem, CShapeProperty* prop)
{
	QList<CShapeProperty*> subPropertys = prop->subPropertys();
	foreach(CShapeProperty * prop, subPropertys)
	{
		QtVariantProperty *subProp = shape_Variant_property_manager->addProperty(prop->type(), prop->propertyName());

		//if (prop->para())
		//{
			//m_propertyMap.insert(subProp, prop->para());
		//}
		
		if(!subProp) 
		{
			qDebug() << "属性生成失败：" << prop->propertyName();
			continue;
		}
		subProp->setValue(prop->value() , &prop->names());

		m_propertyList << subProp;

		if (prop->type() == QtVariantPropertyManager::groupTypeId())
		{
			addSubProp(subProp, prop);
		}
		if (prop->type() == QVariant::Double)
		{
 			varitem->setAttribute("minimum", prop->mimimum());
 			varitem->setAttribute("maximum", prop->maxmum());
 			varitem->setAttribute("singleStep", prop->singleStep());
 			varitem->setAttribute("decimals", prop->decimals());
		}
		else if (prop->type() == QVariant::Int)
		{
			varitem->setAttribute("minimum", prop->mimimum());
			varitem->setAttribute("maximum", prop->maxmum());
			varitem->setAttribute("singleStep", prop->singleStep());
		}
		varitem->addSubProperty(subProp);
	}
}

// void WgtProperty::slot_scene_valuechanged( QtProperty *property, const QVariant &val )
// {
// 	QtVariantPropertyManager *manager = dynamic_cast<QtVariantPropertyManager *>(sender());
// 
// 	if (scene_property_manager == manager)
// 	{
// 		if (gMainWindow->getMainScene())
// 		{
// 			QString pn = property->propertyName();
// 			gMainWindow->getMainScene()->updateProperty(pn , val);
// 			return ;
// 		}
// 	}
// }
// 
// void WgtProperty::slot_scene_updateproperty()
// {
// 	shape_property_editor->setVisible(false);
// 	scene_property_editor->setVisible(true);
// 	qDeleteAll(m_scencepropertyList);
// 	m_scencepropertyList.clear();
// 
// 	CPropertyList list;
// 	gMainWindow->getMainScene()->propertys(list);
// 
// 	foreach (CShapeProperty *prop, list)
// 	{
// 		QtVariantProperty *varitem = scene_property_manager->addProperty(prop->type(), prop->propertyName());
// 		scene_property_manager->setValue(varitem, prop->value());
// 		//varitem->setValue(prop->value() , &prop->names());
// 		scene_property_editor->addProperty(varitem);
// 		m_scencepropertyList << varitem;
// 	}
// 
// 	qDeleteAll(list);
// 	list.clear();
// }
