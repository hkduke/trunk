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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NodeDiscoverTestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *m_pushButton;
    QLineEdit *lineEdit_Z;
    QLabel *label;
    QLineEdit *lineEdit_Y;
    QLineEdit *lineEdit_Z_2;
    QLineEdit *lineEdit_X;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label_2;
    QTextEdit *textEdit;
    QLabel *label_5;
    QPushButton *pushButton_2;
    QWidget *widget;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *NodeDiscoverTestClass)
    {
        if (NodeDiscoverTestClass->objectName().isEmpty())
            NodeDiscoverTestClass->setObjectName(QStringLiteral("NodeDiscoverTestClass"));
        NodeDiscoverTestClass->resize(650, 510);
        centralWidget = new QWidget(NodeDiscoverTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_pushButton = new QPushButton(centralWidget);
        m_pushButton->setObjectName(QStringLiteral("m_pushButton"));

        gridLayout->addWidget(m_pushButton, 0, 2, 1, 1);

        lineEdit_Z = new QLineEdit(centralWidget);
        lineEdit_Z->setObjectName(QStringLiteral("lineEdit_Z"));

        gridLayout->addWidget(lineEdit_Z, 2, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit_Y = new QLineEdit(centralWidget);
        lineEdit_Y->setObjectName(QStringLiteral("lineEdit_Y"));

        gridLayout->addWidget(lineEdit_Y, 1, 1, 1, 1);

        lineEdit_Z_2 = new QLineEdit(centralWidget);
        lineEdit_Z_2->setObjectName(QStringLiteral("lineEdit_Z_2"));

        gridLayout->addWidget(lineEdit_Z_2, 3, 1, 1, 1);

        lineEdit_X = new QLineEdit(centralWidget);
        lineEdit_X->setObjectName(QStringLiteral("lineEdit_X"));

        gridLayout->addWidget(lineEdit_X, 0, 1, 1, 1);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        gridLayout->addWidget(textEdit, 5, 1, 1, 1);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 1, 1, 1);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 7, 2, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));

        gridLayout->addWidget(widget, 5, 2, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 7, 1, 1, 1);

        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 4, 2, 1, 1);

        NodeDiscoverTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(NodeDiscoverTestClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 650, 26));
        NodeDiscoverTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(NodeDiscoverTestClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        NodeDiscoverTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(NodeDiscoverTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        NodeDiscoverTestClass->setStatusBar(statusBar);

        retranslateUi(NodeDiscoverTestClass);

        QMetaObject::connectSlotsByName(NodeDiscoverTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *NodeDiscoverTestClass)
    {
        NodeDiscoverTestClass->setWindowTitle(QApplication::translate("NodeDiscoverTestClass", "NodeDiscoverTest", Q_NULLPTR));
        m_pushButton->setText(QApplication::translate("NodeDiscoverTestClass", "\345\217\221\351\200\201", Q_NULLPTR));
        label->setText(QApplication::translate("NodeDiscoverTestClass", "\344\270\273\351\242\230\345\217\267:", Q_NULLPTR));
        lineEdit_Z_2->setText(QString());
        label_4->setText(QApplication::translate("NodeDiscoverTestClass", "Z\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("NodeDiscoverTestClass", "Z\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("NodeDiscoverTestClass", "Y\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("NodeDiscoverTestClass", "\346\225\260\346\215\256\345\206\205\345\256\271\346\230\276\347\244\272", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("NodeDiscoverTestClass", "\345\217\221\351\200\201\346\226\207\344\273\266", Q_NULLPTR));
        pushButton->setText(QApplication::translate("NodeDiscoverTestClass", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("NodeDiscoverTestClass", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NodeDiscoverTestClass: public Ui_NodeDiscoverTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NODEDISCOVERTEST_H
