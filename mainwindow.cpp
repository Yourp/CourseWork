#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSettings>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(size());
    ui->TW_Orders->setRowCount(WorkingHours);
    ui->TW_Orders->setColumnCount(ColumnTypeMax);

    ui->TW_Orders->setHorizontalHeaderLabels(QStringList() << "Имя" << "Фамилия" << "Контактный телефон");
    ui->TW_Orders->setVerticalHeaderLabels(QStringList() << "09:00" << "10:00" << "11:00" << "12:00" << "13:00" << "14:00" << "15:00" << "16:00");
    ui->TW_Orders->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->TW_Orders->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->TW_Orders->verticalHeader()->setDefaultSectionSize(25);
    ui->TW_Orders->horizontalHeader()->setFixedHeight(20);

    ui->LE_Phone->setInputMask("999 99 999 99 99;_");



//    ui->LE_Name->setInputMask("!>A<AAAAAAAAAAAAAAAAAAAA");
//    ui->LE_Surname->setInputMask("!>A<AAAAAAAAAAAAAAAAAAAA");

    ui->TW_Orders->setColumnWidth(Name, 200);
    ui->TW_Orders->setColumnWidth(Surname, 200);
    ui->TW_Orders->setColumnWidth(PhoneNumber, 200);

    for (int i = 0; i < WorkingHours; ++i)
    {
        ui->TW_Orders->setItem(i, Name, new QTableWidgetItem());
        ui->TW_Orders->setItem(i, Surname, new QTableWidgetItem());
        ui->TW_Orders->setItem(i, PhoneNumber, new QTableWidgetItem());
    }

    connect(ui->LE_Name,    SIGNAL(textChanged(const QString &)), this, SLOT(AnyLineChanged(const QString &)));
    connect(ui->LE_Surname, SIGNAL(textChanged(const QString &)), this, SLOT(AnyLineChanged(const QString &)));
    connect(ui->LE_Phone,   SIGNAL(textChanged(const QString &)), this, SLOT(AnyLineChanged(const QString &)));

    LoadData();

    ui->W_Calendar->showToday();
    on_W_Calendar_selectionChanged();
    SetCheckValidationOfAddOrderButton(true);

    Timer = new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(OnTick()));
    Timer->start(50);
}

MainWindow::~MainWindow()
{
    delete Timer;
    delete ui;
}

void MainWindow::OnTick()
{
    if (bCheckValidationOfAddOrderButton)
    {
        SetCheckValidationOfAddOrderButton(false);
        HandleAddOrderButton();
    }
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

void MainWindow::HandleAddOrderButton()
{
    int RowIndex = ui->TW_Orders->currentRow();

    if (RowIndex < 0)
    {
        return;
    }

    bool bEnableAddOrderButton = !ui->LE_Name->text().isEmpty() && !ui->LE_Surname->text().isEmpty() && !ui->LE_Phone->text().isEmpty();

    if (QTableWidgetItem* NameItem = ui->TW_Orders->item(RowIndex, Name))
    {
        if (NameItem->text() != ui->LE_Name->text())
        {
            ui->PB_AddOrder->setEnabled(bEnableAddOrderButton);
            return;
        }
    }

    if (QTableWidgetItem* SurnameItem = ui->TW_Orders->item(RowIndex, Surname))
    {
        if (SurnameItem->text() != ui->LE_Surname->text())
        {
            ui->PB_AddOrder->setEnabled(bEnableAddOrderButton);
            return;
        }
    }

    if (QTableWidgetItem* PhoneItem = ui->TW_Orders->item(RowIndex, PhoneNumber))
    {
        if (PhoneItem->text() != ui->LE_Phone->text())
        {
            ui->PB_AddOrder->setEnabled(bEnableAddOrderButton);
            return;
        }
    }

    ui->PB_AddOrder->setEnabled(false);
}

void MainWindow::HandleDeleteOrderButton()
{
    int RowIndex = ui->TW_Orders->currentRow();

    if (RowIndex < 0)
    {
        return;
    }

    for (int i = 0; i < ColumnTypeMax; ++i)
    {
        if (QTableWidgetItem* Item = ui->TW_Orders->item(RowIndex, i))
        {
            if (!Item->text().isEmpty())
            {
                ui->PB_DeleteOrder->setEnabled(true);
                return;
            }
        }
    }

    ui->PB_DeleteOrder->setEnabled(false);
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
    ui->PB_AddOrder->setEnabled(false);
}

void MainWindow::on_PB_DeleteOrder_clicked()
{
    int RowIndex = ui->TW_Orders->currentRow();

    if (RowIndex < 0)
    {
        return;
    }

    SetOrderInTablWidget(RowIndex, "", "", "");
    SetOrder(ui->W_Calendar->selectedDate(), RowIndex, "", "", "");
    int Row    = ui->TW_Orders->currentRow();
    int Column = ui->TW_Orders->currentColumn();

    on_TW_Orders_currentCellChanged(Row, Column, Row, Column);
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

    int Row    = ui->TW_Orders->currentRow();
    int Column = ui->TW_Orders->currentColumn();

    on_TW_Orders_currentCellChanged(Row, Column, Row, Column);
}

void MainWindow::on_TW_Orders_currentCellChanged(int currentRow, int, int, int)
{
    if (QTableWidgetItem* NameItem = ui->TW_Orders->item(currentRow, Name))
    {
        ui->LE_Name->setText(NameItem->text());
    }

    if (QTableWidgetItem* SurnameItem = ui->TW_Orders->item(currentRow, Surname))
    {
        ui->LE_Surname->setText(SurnameItem->text());
    }

    if (QTableWidgetItem* PhoneItem = ui->TW_Orders->item(currentRow, PhoneNumber))
    {
        ui->LE_Phone->setText(PhoneItem->text());
    }

    HandleDeleteOrderButton();
}

void MainWindow::AnyLineChanged(const QString & Arg)
{
    if (Arg.isEmpty())
    {
        ui->PB_AddOrder->setEnabled(false);
        return;
    }

    SetCheckValidationOfAddOrderButton(true);
}


