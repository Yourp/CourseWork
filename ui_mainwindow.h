/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QCalendarWidget *W_Calendar;
    QTableWidget *TW_Orders;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *L_Name;
    QLineEdit *LE_Name;
    QLabel *L_Surname;
    QLineEdit *LE_Surname;
    QLabel *L_Phone;
    QLineEdit *LE_Phone;
    QWidget *widget1;
    QVBoxLayout *verticalLayout;
    QPushButton *PB_AddOrder;
    QPushButton *PB_DeleteOrder;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1058, 738);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        W_Calendar = new QCalendarWidget(centralwidget);
        W_Calendar->setObjectName(QString::fromUtf8("W_Calendar"));
        W_Calendar->setGeometry(QRect(10, 410, 251, 221));
        W_Calendar->setMinimumDate(QDate(2020, 9, 14));
        W_Calendar->setMaximumDate(QDate(2100, 12, 31));
        W_Calendar->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        W_Calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
        TW_Orders = new QTableWidget(centralwidget);
        TW_Orders->setObjectName(QString::fromUtf8("TW_Orders"));
        TW_Orders->setGeometry(QRect(280, 410, 641, 222));
        TW_Orders->setFocusPolicy(Qt::WheelFocus);
        TW_Orders->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TW_Orders->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TW_Orders->setAutoScroll(false);
        TW_Orders->setEditTriggers(QAbstractItemView::NoEditTriggers);
        TW_Orders->setSelectionMode(QAbstractItemView::SingleSelection);
        TW_Orders->setSelectionBehavior(QAbstractItemView::SelectRows);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 320, 331, 71));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        L_Name = new QLabel(widget);
        L_Name->setObjectName(QString::fromUtf8("L_Name"));

        formLayout->setWidget(0, QFormLayout::LabelRole, L_Name);

        LE_Name = new QLineEdit(widget);
        LE_Name->setObjectName(QString::fromUtf8("LE_Name"));

        formLayout->setWidget(0, QFormLayout::FieldRole, LE_Name);

        L_Surname = new QLabel(widget);
        L_Surname->setObjectName(QString::fromUtf8("L_Surname"));

        formLayout->setWidget(1, QFormLayout::LabelRole, L_Surname);

        LE_Surname = new QLineEdit(widget);
        LE_Surname->setObjectName(QString::fromUtf8("LE_Surname"));

        formLayout->setWidget(1, QFormLayout::FieldRole, LE_Surname);

        L_Phone = new QLabel(widget);
        L_Phone->setObjectName(QString::fromUtf8("L_Phone"));

        formLayout->setWidget(2, QFormLayout::LabelRole, L_Phone);

        LE_Phone = new QLineEdit(widget);
        LE_Phone->setObjectName(QString::fromUtf8("LE_Phone"));

        formLayout->setWidget(2, QFormLayout::FieldRole, LE_Phone);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(370, 340, 100, 54));
        verticalLayout = new QVBoxLayout(widget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        PB_AddOrder = new QPushButton(widget1);
        PB_AddOrder->setObjectName(QString::fromUtf8("PB_AddOrder"));
        PB_AddOrder->setEnabled(true);

        verticalLayout->addWidget(PB_AddOrder);

        PB_DeleteOrder = new QPushButton(widget1);
        PB_DeleteOrder->setObjectName(QString::fromUtf8("PB_DeleteOrder"));
        PB_DeleteOrder->setEnabled(false);

        verticalLayout->addWidget(PB_DeleteOrder);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1058, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Course Work", nullptr));
        L_Name->setText(QCoreApplication::translate("MainWindow", "\320\230\320\274\321\217 \320\272\320\273\320\270\320\265\320\275\321\202\320\260:", nullptr));
        L_Surname->setText(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217:", nullptr));
        L_Phone->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\321\202\320\260\320\272\321\202\320\275\321\213\320\271 \320\275\320\276\320\274\320\265\321\200:", nullptr));
        PB_AddOrder->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", nullptr));
        PB_DeleteOrder->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
