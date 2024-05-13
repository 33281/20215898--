/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "calendarwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widgetDatetime;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelCurrentTime;
    CalendarWidget *widgetCalendar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(387, 492);
        MainWindow->setStyleSheet(QLatin1String("*{font-family : \"Microsoft YaHei\" ;}\n"
"\n"
"QWidget#widgetPan {\n"
"	border-top: 1px solid #616161;\n"
"}\n"
"#widgetDatetime {\n"
"	border-bottom: 1px solid #616161;\n"
"}\n"
"QLabel {\n"
"	color: #ffffff;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QLatin1String("QWidget {\n"
"	background-color: #3d3d3d;\n"
"}"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        widgetDatetime = new QWidget(centralwidget);
        widgetDatetime->setObjectName(QStringLiteral("widgetDatetime"));
        widgetDatetime->setMinimumSize(QSize(0, 100));
        widgetDatetime->setMaximumSize(QSize(16777215, 100));
        verticalLayout_2 = new QVBoxLayout(widgetDatetime);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 20, -1, 20);
        labelCurrentTime = new QLabel(widgetDatetime);
        labelCurrentTime->setObjectName(QStringLiteral("labelCurrentTime"));
        labelCurrentTime->setStyleSheet(QStringLiteral("font: 30px;"));
        labelCurrentTime->setTextFormat(Qt::PlainText);

        verticalLayout_2->addWidget(labelCurrentTime);


        verticalLayout->addWidget(widgetDatetime);

        widgetCalendar = new CalendarWidget(centralwidget);
        widgetCalendar->setObjectName(QStringLiteral("widgetCalendar"));
        widgetCalendar->setMinimumSize(QSize(0, 340));

        verticalLayout->addWidget(widgetCalendar);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        labelCurrentTime->setText(QApplication::translate("MainWindow", "18:13:11", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
