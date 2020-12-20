#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->TW_Orders->setRowCount(WorkingHours);
    ui->TW_Orders->setColumnCount(ColumnTypeMax);

    ui->TW_Orders->setHorizontalHeaderLabels(QStringList() << "Имя" << "Фамилия" << "Контактный телефон");
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

    WorkingDay Day;

    Day.Orders[5][Name] = "Gaa";
    Day.Date = ui->W_Calendar->selectedDate();

    OrdersList.push_back(Day);
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

    int OrderSaveIndex = 0;

    for (auto const& Itr : OrdersList)
    {
        QString PrefixName = "OSI" + QString::number(OrderSaveIndex);

        Data.setValue(PrefixName + "Date", Itr.Date);

        for (int TimeIndex = 0; TimeIndex < WorkingHours; ++TimeIndex)
        {
            if (!Itr.Orders[TimeIndex][Name].isEmpty())
            {
                PrefixName += "_" + QString::number(TimeIndex);

                Data.setValue(PrefixName + "Name", Itr.Orders[TimeIndex][Name]);
                Data.setValue(PrefixName + "Surname", Itr.Orders[TimeIndex][Surname]);
                Data.setValue(PrefixName + "PhoneNumber", Itr.Orders[TimeIndex][PhoneNumber]);

                OrderSaveIndex++;
            }
        }
    }
}

void MainWindow::LoadData()
{
    QSettings Data("Order.ini", QSettings::IniFormat);
    Data.setIniCodec("UTF-8");

    int OrderSaveIndex = 0;
    QString PrefixName = "OSI" + QString::number(OrderSaveIndex);

    while (Data.contains(PrefixName + "Date"))
    {
        WorkingDay Day;

        Day.Date = Data.value(PrefixName + "Date").toDate();

        for (int TimeIndex = 0; TimeIndex < WorkingHours; ++TimeIndex)
        {
            QString CurrentPrefixName = PrefixName + "_" + QString::number(TimeIndex);

            Day.SetOrder
            (
                TimeIndex,
                Data.value(CurrentPrefixName + "Name").toString(),
                Data.value(CurrentPrefixName + "Surname").toString(),
                Data.value(CurrentPrefixName + "PhoneNumber").toString()
            );
        }

        OrdersList.push_back(Day);
        PrefixName = "OSI" + QString::number(++OrderSaveIndex);
    }
}

WorkingDay *MainWindow::FindWorkingDay(QDate const& date)
{
    for (auto& Itr : OrdersList)
    {
        if (Itr.Date == date)
        {
            return &Itr;
        }
    }

    return nullptr;
}

void MainWindow::SetOrder(const QDate &NewDate, int TimeIndex, const QString &NewName, const QString &NewSurname, const QString &NewPhoneNumber)
{
    if (NewName.isEmpty() || NewSurname.isEmpty() || NewPhoneNumber.isEmpty())
    {
        return;
    }

    if (WorkingDay* FindedWorkingDay = FindWorkingDay(NewDate))
    {
        FindedWorkingDay->SetOrder(TimeIndex, NewName, NewSurname, NewPhoneNumber);
        return;
    }

    WorkingDay NewDay;

    NewDay.Date = NewDate;
    NewDay.SetOrder(TimeIndex, NewName, NewSurname, NewPhoneNumber);
}


void WorkingDay::SetOrder(int TimeIndex, const QString &NewName, const QString &NewSurname, const QString &NewPhoneNumber)
{
    Orders[TimeIndex][Name] = NewName;
    Orders[TimeIndex][Surname] = NewSurname;
    Orders[TimeIndex][PhoneNumber] = NewPhoneNumber;
}

void MainWindow::on_PB_AddOrder_clicked()
{

}
