/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLabel *label;
    QLineEdit *num1Input;
    QLineEdit *num2Input;
    QPushButton *calcButton;
    QLabel *resultLabel;
    QDial *dial_1;
    QDial *dial_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setBaseSize(QSize(0, 0));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(590, 10, 141, 61));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setEnabled(true);
        label->setGeometry(QRect(260, 20, 121, 51));
        label->setBaseSize(QSize(10, 0));
        label->setFrameShape(QFrame::Shape::WinPanel);
        label->setTextFormat(Qt::TextFormat::PlainText);
        label->setScaledContents(false);
        num1Input = new QLineEdit(centralwidget);
        num1Input->setObjectName("num1Input");
        num1Input->setGeometry(QRect(30, 150, 113, 22));
        num2Input = new QLineEdit(centralwidget);
        num2Input->setObjectName("num2Input");
        num2Input->setGeometry(QRect(200, 150, 113, 22));
        calcButton = new QPushButton(centralwidget);
        calcButton->setObjectName("calcButton");
        calcButton->setGeometry(QRect(400, 210, 131, 24));
        resultLabel = new QLabel(centralwidget);
        resultLabel->setObjectName("resultLabel");
        resultLabel->setGeometry(QRect(370, 150, 191, 16));
        dial_1 = new QDial(centralwidget);
        dial_1->setObjectName("dial_1");
        dial_1->setGeometry(QRect(30, 160, 111, 131));
        dial_2 = new QDial(centralwidget);
        dial_2->setObjectName("dial_2");
        dial_2->setGeometry(QRect(200, 170, 111, 111));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "          Calculator", nullptr));
        num1Input->setText(QString());
        num2Input->setText(QString());
        calcButton->setText(QCoreApplication::translate("MainWindow", "calcButton", nullptr));
        resultLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
