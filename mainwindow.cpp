#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->TW_Orders->setRowCount(8);
    ui->TW_Orders->setColumnCount(ColumnTypeMax);

    ui->TW_Orders->setHorizontalHeaderLabels(QStringList() << "Имя" << "Фамилия" << "Номер телефона");
    ui->TW_Orders->setVerticalHeaderLabels(QStringList() << "09:00" << "10:00" << "11:00" << "12:00" << "13:00" << "14:00" << "15:00" << "16:00");
    ui->TW_Orders->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->TW_Orders->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->TW_Orders->verticalHeader()->setDefaultSectionSize(25);
    ui->TW_Orders->horizontalHeader()->setFixedHeight(22);

    ui->TW_Orders->setColumnWidth(Name, 200);
    ui->TW_Orders->setColumnWidth(Surname, 200);
    ui->TW_Orders->setColumnWidth(PhoneNumber, 200);

    //ui->TW_Orders->setItem(0, Name, new QTableWidgetItem("Саня"));

    ui->W_Calendar->showToday();

    LoadData();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *Event)
{
    SaveData();
    QMainWindow::closeEvent(Event);
}

void MainWindow::SaveData()
{
    QSettings Data("Order.ini", QSettings::IniFormat);
    Data.setIniCodec("UTF-8");
}

void MainWindow::LoadData()
{
    QSettings Data("Order.ini", QSettings::IniFormat);
    Data.setIniCodec("UTF-8");
}

