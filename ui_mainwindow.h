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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *L_Name;
    QLineEdit *LE_Name;
    QLabel *L_Surname;
    QLineEdit *LE_Surname;
    QLabel *L_Phone;
    QLineEdit *LE_Phone;
    QLabel *L_SessionType;
    QComboBox *CB_SessionType;
    QLabel *L_Cost;
    QSpinBox *SB_Cost;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *PB_AddOrder;
    QPushButton *PB_DeleteOrder;
    QCalendarWidget *W_Calendar;
    QTableWidget *TW_Orders;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(684, 475);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(11, 12, 663, 420));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
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
        LE_Phone->setInputMethodHints(Qt::ImhNone);
        LE_Phone->setEchoMode(QLineEdit::Normal);
        LE_Phone->setClearButtonEnabled(true);

        formLayout->setWidget(2, QFormLayout::FieldRole, LE_Phone);

        L_SessionType = new QLabel(widget);
        L_SessionType->setObjectName(QString::fromUtf8("L_SessionType"));

        formLayout->setWidget(3, QFormLayout::LabelRole, L_SessionType);

        CB_SessionType = new QComboBox(widget);
        CB_SessionType->setObjectName(QString::fromUtf8("CB_SessionType"));

        formLayout->setWidget(3, QFormLayout::FieldRole, CB_SessionType);

        L_Cost = new QLabel(widget);
        L_Cost->setObjectName(QString::fromUtf8("L_Cost"));

        formLayout->setWidget(4, QFormLayout::LabelRole, L_Cost);

        SB_Cost = new QSpinBox(widget);
        SB_Cost->setObjectName(QString::fromUtf8("SB_Cost"));
        SB_Cost->setMaximumSize(QSize(50, 16777215));
        QFont font;
        font.setPointSize(8);
        SB_Cost->setFont(font);
        SB_Cost->setMaximum(9999);

        formLayout->setWidget(4, QFormLayout::FieldRole, SB_Cost);


        verticalLayout->addLayout(formLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        PB_AddOrder = new QPushButton(widget);
        PB_AddOrder->setObjectName(QString::fromUtf8("PB_AddOrder"));
        PB_AddOrder->setEnabled(false);

        horizontalLayout->addWidget(PB_AddOrder);

        PB_DeleteOrder = new QPushButton(widget);
        PB_DeleteOrder->setObjectName(QString::fromUtf8("PB_DeleteOrder"));
        PB_DeleteOrder->setEnabled(false);

        horizontalLayout->addWidget(PB_DeleteOrder);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        W_Calendar = new QCalendarWidget(widget);
        W_Calendar->setObjectName(QString::fromUtf8("W_Calendar"));
        W_Calendar->setMinimumSize(QSize(400, 0));
        W_Calendar->setMinimumDate(QDate(2020, 9, 14));
        W_Calendar->setMaximumDate(QDate(2100, 12, 31));
        W_Calendar->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);
        W_Calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

        gridLayout->addWidget(W_Calendar, 0, 1, 1, 1);

        TW_Orders = new QTableWidget(widget);
        TW_Orders->setObjectName(QString::fromUtf8("TW_Orders"));
        TW_Orders->setMinimumSize(QSize(661, 222));
        TW_Orders->setMaximumSize(QSize(661, 222));
        TW_Orders->setFocusPolicy(Qt::WheelFocus);
        TW_Orders->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TW_Orders->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        TW_Orders->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
        TW_Orders->setAutoScroll(false);
        TW_Orders->setEditTriggers(QAbstractItemView::NoEditTriggers);
        TW_Orders->setSelectionMode(QAbstractItemView::SingleSelection);
        TW_Orders->setSelectionBehavior(QAbstractItemView::SelectRows);
        TW_Orders->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        TW_Orders->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

        gridLayout->addWidget(TW_Orders, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 684, 22));
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
        L_Phone->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\273\320\265\321\204\320\276\320\275:", nullptr));
        L_SessionType->setText(QCoreApplication::translate("MainWindow", "\320\242\320\270\320\277 \321\204\320\276\321\202\320\276\321\201\321\212\320\265\320\274\320\272\320\270:", nullptr));
        L_Cost->setText(QCoreApplication::translate("MainWindow", "\320\246\320\265\320\275\320\260:", nullptr));
#if QT_CONFIG(tooltip)
        PB_AddOrder->setToolTip(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\265 \320\262\321\200\320\265\320\274\321\217 \320\262 \321\202\320\260\320\261\320\273\320\270\321\206\320\265 \320\270 \320\267\320\260\320\277\320\276\320\273\320\275\320\265\320\275\320\275\321\213\320\265 \320\277\320\276\320\273\321\217 - \320\262\320\272\320\273\321\216\321\207\320\260\321\216\321\202 \320\272\320\275\320\276\320\277\320\272\321\203.", nullptr));
#endif // QT_CONFIG(tooltip)
        PB_AddOrder->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\320\260\321\202\321\214 \320\272\320\273\320\270\320\265\320\275\321\202\320\260", nullptr));
        PB_DeleteOrder->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\267\320\260\320\277\320\270\321\201\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
