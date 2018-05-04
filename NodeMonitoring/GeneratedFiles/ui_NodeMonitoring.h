/********************************************************************************
** Form generated from reading UI file 'NodeMonitoring.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEMONITORING_H
#define UI_NODEMONITORING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NodeMonitoringClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTextEdit *textEdit;
    QWidget *widget2;
    QLabel *label_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NodeMonitoringClass)
    {
        if (NodeMonitoringClass->objectName().isEmpty())
            NodeMonitoringClass->setObjectName(QStringLiteral("NodeMonitoringClass"));
        NodeMonitoringClass->resize(790, 644);
        centralWidget = new QWidget(NodeMonitoringClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout_2->addWidget(textEdit);


        horizontalLayout->addLayout(verticalLayout_2);

        widget2 = new QWidget(centralWidget);
        widget2->setObjectName(QStringLiteral("widget2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget2->sizePolicy().hasHeightForWidth());
        widget2->setSizePolicy(sizePolicy);
        label_2 = new QLabel(widget2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 72, 15));

        horizontalLayout->addWidget(widget2);


        horizontalLayout_2->addLayout(horizontalLayout);

        NodeMonitoringClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(NodeMonitoringClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        NodeMonitoringClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(NodeMonitoringClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        NodeMonitoringClass->setStatusBar(statusBar);

        retranslateUi(NodeMonitoringClass);

        QMetaObject::connectSlotsByName(NodeMonitoringClass);
    } // setupUi

    void retranslateUi(QMainWindow *NodeMonitoringClass)
    {
        NodeMonitoringClass->setWindowTitle(QApplication::translate("NodeMonitoringClass", "NodeMonitoring", Q_NULLPTR));
        label->setText(QApplication::translate("NodeMonitoringClass", "\350\212\202\347\202\271\344\277\241\346\201\257", Q_NULLPTR));
        label_2->setText(QApplication::translate("NodeMonitoringClass", "\350\212\202\347\202\271\347\212\266\346\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NodeMonitoringClass: public Ui_NodeMonitoringClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEMONITORING_H
