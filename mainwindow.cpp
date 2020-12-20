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



    for (int i = 0; i < WorkingHours; ++i)
    {
        ui->TW_Orders->setItem(i, Name, new QTableWidgetItem());
        ui->TW_Orders->setItem(i, Surname, new QTableWidgetItem());
        ui->TW_Orders->setItem(i, PhoneNumber, new QTableWidgetItem());
    }


    LoadData();

    ui->W_Calendar->showToday();
    on_W_Calendar_selectionChanged();
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
                QString CurrentPrefixName = PrefixName + "_" + QString::number(TimeIndex);

                Data.setValue(CurrentPrefixName + "Name", Itr.Orders[TimeIndex][Name]);
                Data.setValue(CurrentPrefixName + "Surname", Itr.Orders[TimeIndex][Surname]);
                Data.setValue(CurrentPrefixName + "PhoneNumber", Itr.Orders[TimeIndex][PhoneNumber]);
            }
        }

        OrderSaveIndex++;
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
    OrdersList.push_back(NewDay);
}

void MainWindow::SetOrderInTablWidget(int Row, const QString &NewName, const QString &NewSurname, const QString &NewPhoneNumber)
{
    if (QTableWidgetItem* NameItem = ui->TW_Orders->item(Row, Name))
    {
        NameItem->setText(NewName);
    }

    if (QTableWidgetItem* SurnameItem = ui->TW_Orders->item(Row, Surname))
    {
        SurnameItem->setText(NewSurname);
    }

    if (QTableWidgetItem* PhoneItem = ui->TW_Orders->item(Row, PhoneNumber))
    {
        PhoneItem->setText(NewPhoneNumber);
    }
}

void MainWindow::ClearAllOrdersInTablWidget()
{
    for (int i = 0; i < WorkingHours; ++i)
    {
        SetOrderInTablWidget(i, "", "", "");
    }
}


void WorkingDay::SetOrder(int TimeIndex, const QString &NewName, const QString &NewSurname, const QString &NewPhoneNumber)
{
    Orders[TimeIndex][Name] = NewName;
    Orders[TimeIndex][Surname] = NewSurname;
    Orders[TimeIndex][PhoneNumber] = NewPhoneNumber;
}

void MainWindow::on_PB_AddOrder_clicked()
{
    int RowIndex = ui->TW_Orders->currentRow();

    if (RowIndex < 0)
    {
        return;
    }

    QString NewName = ui->LE_Name->text();
    QString NewSurame = ui->LE_Surname->text();
    QString NewPhone = ui->LE_Phone->text();

    SetOrderInTablWidget(RowIndex, NewName, NewSurame, NewPhone);
    SetOrder(ui->W_Calendar->selectedDate(), RowIndex, NewName, NewSurame, NewPhone);
}


void MainWindow::on_W_Calendar_selectionChanged()
{
    if (WorkingDay const* FindedDay = FindWorkingDay(ui->W_Calendar->selectedDate()))
    {
        for (int i = 0; i < WorkingHours; ++i)
        {
            SetOrderInTablWidget(i, FindedDay->Orders[i][Name], FindedDay->Orders[i][Surname], FindedDay->Orders[i][PhoneNumber]);
        }
    }
    else
    {
        ClearAllOrdersInTablWidget();
    }
}
