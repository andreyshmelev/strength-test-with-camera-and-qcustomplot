/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QCustomPlot *customPlot;
    QCustomPlot *customPlot_2;
    QLabel *message;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QSpinBox *unit;
    QSpinBox *command;
    QSpinBox *data;
    QSpinBox *DataLenght;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(567, 574);
        MainWindow->setStyleSheet(QLatin1String("/*border: 1px solid gray;*/\n"
"/*border-radius: 10px;*/\n"
"/*background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(103,158,210, 255), stop:1 rgba(103,158,255, 255));*/\n"
"background-color: rgb(192,231,230);\n"
"\n"
"   color: white;\n"
"\n"
"QCheckBox::indicator {\n"
"    width: 30px;\n"
"    height: 30px;\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(customPlot, 1, 0, 1, 2);

        customPlot_2 = new QCustomPlot(centralWidget);
        customPlot_2->setObjectName(QStringLiteral("customPlot_2"));
        sizePolicy.setHeightForWidth(customPlot_2->sizePolicy().hasHeightForWidth());
        customPlot_2->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(customPlot_2, 1, 2, 1, 1);

        message = new QLabel(centralWidget);
        message->setObjectName(QStringLiteral("message"));

        gridLayout_2->addWidget(message, 2, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 0, 0, 1, 1);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 0, 1, 1, 1);

        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 0, 2, 1, 1);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 0, 3, 1, 1);

        unit = new QSpinBox(centralWidget);
        unit->setObjectName(QStringLiteral("unit"));
        unit->setMinimumSize(QSize(100, 50));
        unit->setStyleSheet(QLatin1String("QSpinBox::up-button { width: 32px; }\n"
"QSpinBox::down-button { width: 32px; }\n"
"QComboBox::drop-down \n"
"{ width: 32px; }"));
        unit->setMaximum(2222);
        unit->setValue(127);

        gridLayout->addWidget(unit, 1, 0, 1, 1);

        command = new QSpinBox(centralWidget);
        command->setObjectName(QStringLiteral("command"));
        command->setMinimumSize(QSize(100, 50));
        command->setStyleSheet(QLatin1String("QSpinBox::up-button { width: 32px; }\n"
"QSpinBox::down-button { width: 32px; }\n"
"QComboBox::drop-down \n"
"{ width: 32px; }"));
        command->setMaximum(2222);
        command->setValue(0);

        gridLayout->addWidget(command, 1, 1, 1, 1);

        data = new QSpinBox(centralWidget);
        data->setObjectName(QStringLiteral("data"));
        data->setMinimumSize(QSize(100, 50));
        data->setStyleSheet(QLatin1String("QSpinBox::up-button { width: 32px; }\n"
"QSpinBox::down-button { width: 32px; }\n"
"QComboBox::drop-down \n"
"{ width: 32px; }"));
        data->setMaximum(42000000);
        data->setValue(255);

        gridLayout->addWidget(data, 1, 2, 1, 1);

        DataLenght = new QSpinBox(centralWidget);
        DataLenght->setObjectName(QStringLiteral("DataLenght"));
        DataLenght->setMinimumSize(QSize(100, 50));
        DataLenght->setStyleSheet(QLatin1String("QSpinBox::up-button { width: 32px; }\n"
"QSpinBox::down-button { width: 32px; }\n"
"QComboBox::drop-down \n"
"{ width: 32px; }"));
        DataLenght->setMaximum(65000);
        DataLenght->setSingleStep(1);
        DataLenght->setValue(2);

        gridLayout->addWidget(DataLenght, 1, 3, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 1, 1, 2);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 543, 197));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 567, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        message->setText(QApplication::translate("MainWindow", "Unit", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Unit", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Command", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Data", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "DataLenght", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
