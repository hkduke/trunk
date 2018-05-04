/********************************************************************************
** Form generated from reading UI file 'NodeDiscoverTest.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NODEDISCOVERTEST_H
#define UI_NODEDISCOVERTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NodeDiscoverTestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *cbCycle;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *edtStep;
    QPushButton *btnSend;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QTextBrowser *tbSend;
    QLabel *label_6;
    QTextBrowser *tbRecv;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QPushButton *btnSelectFile;
    QLineEdit *edtPath;
    QPushButton *btnSendFile;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *tableWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NodeDiscoverTestClass)
    {
        if (NodeDiscoverTestClass->objectName().isEmpty())
            NodeDiscoverTestClass->setObjectName(QStringLiteral("NodeDiscoverTestClass"));
        NodeDiscoverTestClass->resize(842, 510);
        centralWidget = new QWidget(NodeDiscoverTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        cbCycle = new QCheckBox(widget);
        cbCycle->setObjectName(QStringLiteral("cbCycle"));

        horizontalLayout_2->addWidget(cbCycle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        edtStep = new QLineEdit(widget);
        edtStep->setObjectName(QStringLiteral("edtStep"));
        edtStep->setMaxLength(32767);

        horizontalLayout->addWidget(edtStep);


        horizontalLayout_2->addLayout(horizontalLayout);

        btnSend = new QPushButton(widget);
        btnSend->setObjectName(QStringLiteral("btnSend"));
        btnSend->setMinimumSize(QSize(100, 0));
        btnSend->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_2->addWidget(btnSend);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        tbSend = new QTextBrowser(widget);
        tbSend->setObjectName(QStringLiteral("tbSend"));

        verticalLayout->addWidget(tbSend);

        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);

        tbRecv = new QTextBrowser(widget);
        tbRecv->setObjectName(QStringLiteral("tbRecv"));

        verticalLayout->addWidget(tbRecv);


        verticalLayout_3->addLayout(verticalLayout);


        gridLayout_3->addWidget(widget, 0, 1, 2, 1);

        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        btnSelectFile = new QPushButton(frame);
        btnSelectFile->setObjectName(QStringLiteral("btnSelectFile"));

        gridLayout_2->addWidget(btnSelectFile, 4, 0, 1, 1);

        edtPath = new QLineEdit(frame);
        edtPath->setObjectName(QStringLiteral("edtPath"));

        gridLayout_2->addWidget(edtPath, 4, 2, 1, 1);

        btnSendFile = new QPushButton(frame);
        btnSendFile->setObjectName(QStringLiteral("btnSendFile"));

        gridLayout_2->addWidget(btnSendFile, 5, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(255, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 5, 2, 1, 1);

        tableWidget = new QTableWidget(frame);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout_2->addWidget(tableWidget, 0, 0, 2, 5);


        gridLayout_3->addWidget(frame, 0, 0, 2, 1);

        NodeDiscoverTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(NodeDiscoverTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        NodeDiscoverTestClass->setStatusBar(statusBar);

        retranslateUi(NodeDiscoverTestClass);

        QMetaObject::connectSlotsByName(NodeDiscoverTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *NodeDiscoverTestClass)
    {
        NodeDiscoverTestClass->setWindowTitle(QApplication::translate("NodeDiscoverTestClass", "NodeDiscoverTest", Q_NULLPTR));
        cbCycle->setText(QApplication::translate("NodeDiscoverTestClass", "\345\276\252\347\216\257\345\217\221\351\200\201", Q_NULLPTR));
        label->setText(QApplication::translate("NodeDiscoverTestClass", "\346\255\245\351\225\277", Q_NULLPTR));
        edtStep->setInputMask(QString());
        edtStep->setText(QApplication::translate("NodeDiscoverTestClass", "5000", Q_NULLPTR));
        edtStep->setPlaceholderText(QApplication::translate("NodeDiscoverTestClass", "ms", Q_NULLPTR));
        btnSend->setText(QApplication::translate("NodeDiscoverTestClass", "\345\217\221\351\200\201", Q_NULLPTR));
        label_5->setText(QApplication::translate("NodeDiscoverTestClass", "\345\217\221\351\200\201\346\225\260\346\215\256", Q_NULLPTR));
        label_6->setText(QApplication::translate("NodeDiscoverTestClass", "\346\216\245\346\224\266\346\225\260\346\215\256", Q_NULLPTR));
        btnSelectFile->setText(QApplication::translate("NodeDiscoverTestClass", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        btnSendFile->setText(QApplication::translate("NodeDiscoverTestClass", "\345\217\221\351\200\201\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NodeDiscoverTestClass: public Ui_NodeDiscoverTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEDISCOVERTEST_H
