#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "programstatics.h"
#include "workingday.h"
#include <QSettings>
#include <QTimer>

/** Конструктор класса. Сдесь происходит инициализация переменных и ввод различных параметров. */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    /** Инициализация переменных для ui. */
    ui->setupUi(this);

    /** Фиксируем размер главного окна программы. */
    setFixedSize(size());

    /** Устанавливаем количество возможных строк в таблице заказов. */
    ui->TW_Orders->setRowCount(ProgramStatics::WorkingHours);

    /** Устанавливаем количество возможных столбцов в таблице заказов. */
    ui->TW_Orders->setColumnCount(ColumnTypeMax);

    /** Подписываем название столбцов. */
    ui->TW_Orders->setHorizontalHeaderLabels(QStringList() << "Имя" << "Фамилия" << "Телефон" << "Тип фотосъемки" << "Цена");

    /** Подписываем название строк. 8-ми часовой рабочий день. Каждая строка - это час работы фотографа. */
    ui->TW_Orders->setVerticalHeaderLabels(QStringList() << "09:00" << "10:00" << "11:00" << "12:00" << "13:00" << "14:00" << "15:00" << "16:00");

    /** Фиксируем левую и верхнюю часть таблицы, там где у нас названия столбцов и расписание по времени. */
    ui->TW_Orders->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->TW_Orders->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    /** Устанавливаем высоту сегмента заказа. В пикселях. */
    ui->TW_Orders->verticalHeader()->setDefaultSectionSize(25);

    /** Устанавливаем высоту верхней части таблицы заказов. */
    ui->TW_Orders->horizontalHeader()->setFixedHeight(20);

    /** Маска ввода символов для номера телефона. */
    ui->LE_Phone->setInputMask("999 99 999 99 99;_");

    /** Устанавливаем длину каждого столбца таблицы заказов. */
    ui->TW_Orders->setColumnWidth(Name,        150);
    ui->TW_Orders->setColumnWidth(Surname,     150);
    ui->TW_Orders->setColumnWidth(PhoneNumber, 150);
    ui->TW_Orders->setColumnWidth(SessionType, 120);
    ui->TW_Orders->setColumnWidth(Cost,         50);
    
    
    /** Выделение памяти для каждой клетки таблицы заказов. В дальнейшем мы просто будем менять текст этих клеток для записей в таблицу заказов. */
    for (int Row = 0; Row < ProgramStatics::WorkingHours; ++Row)
    {
        for (int Column = 0; Column < ColumnTypeMax; ++Column)
        {
            QTableWidgetItem* NewItem = new QTableWidgetItem();
            NewItem->setTextAlignment(Qt::AlignCenter);
            ui->TW_Orders->setItem(Row, Column, NewItem);
        }
    }

    /** 
     * Макросы QT. Сдесь идет подключение вызова определенной функции, когда что-то происходит с обьектом.
     *
     * Например: Когда у обьекта LE_Name меняется текст (textChanged) - вызывается функция AnyLineChanged.
     * LE_Name - это строка ввода, стоит нам ввести или поменять символ - произойдет вызов метода AnyLineChanged.
     */
    connect(ui->LE_Name,    SIGNAL(textChanged(const QString &)), this, SLOT(AnyLineChanged(const QString &)));
    connect(ui->LE_Surname, SIGNAL(textChanged(const QString &)), this, SLOT(AnyLineChanged(const QString &)));
    connect(ui->LE_Phone,   SIGNAL(textChanged(const QString &)), this, SLOT(AnyLineChanged(const QString &)));
    connect(ui->SB_Cost,    SIGNAL(textChanged(const QString &)), this, SLOT(AnyLineChanged(const QString &)));

    for (auto Itr : ProgramStatics::PhotosessionType)
    {
        ui->CB_SessionType->addItem(Itr);
    }

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
    Data.clear();
    Data.setIniCodec("UTF-8");

    int OrderSaveIndex = 0;

    for (auto const& Itr : OrdersList)
    {
        QString PrefixName = "OSI" + QString::number(OrderSaveIndex);

        Data.setValue(PrefixName + "Date", Itr.Date);

        for (int TimeIndex = 0; TimeIndex < ProgramStatics::WorkingHours; ++TimeIndex)
        {
            if (!Itr.Orders[TimeIndex][Name].isEmpty())
            {
                QString CurrentPrefixName = PrefixName + "_" + QString::number(TimeIndex);

                Data.setValue(CurrentPrefixName + "Name", Itr.Orders[TimeIndex][Name]);
                Data.setValue(CurrentPrefixName + "Surname", Itr.Orders[TimeIndex][Surname]);
                Data.setValue(CurrentPrefixName + "PhoneNumber", Itr.Orders[TimeIndex][PhoneNumber]);
                Data.setValue(CurrentPrefixName + "SessionType", Itr.Orders[TimeIndex][SessionType]);
                Data.setValue(CurrentPrefixName + "Cost", Itr.Orders[TimeIndex][Cost]);
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

        for (int TimeIndex = 0; TimeIndex < ProgramStatics::WorkingHours; ++TimeIndex)
        {
            QString CurrentPrefixName = PrefixName + "_" + QString::number(TimeIndex);


            QVector<QString> const Param =
            {
                Data.value(CurrentPrefixName + "Name").toString(),
                Data.value(CurrentPrefixName + "Surname").toString(),
                Data.value(CurrentPrefixName + "PhoneNumber").toString(),
                Data.value(CurrentPrefixName + "SessionType").toString(),
                Data.value(CurrentPrefixName + "Cost").toString()
            };

            Day.SetOrder(TimeIndex, Param);
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

    QVector<QString> const Param =
    {
        ui->LE_Name->text(),
        ui->LE_Surname->text(),
        ui->LE_Phone->text(),
        ui->CB_SessionType->currentText(),
        ui->SB_Cost->text()
    };

    for (int i = 0; i < ColumnTypeMax; ++i)
    {
        if (QTableWidgetItem* Item = ui->TW_Orders->item(RowIndex, i))
        {
            if (Item->text() != Param[i])
            {
                ui->PB_AddOrder->setEnabled(bEnableAddOrderButton);
                return;
            }
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

void MainWindow::SetOrder(const QDate &NewDate, int TimeIndex, QVector<QString> const& NewOrder)
{
    if (WorkingDay* FindedWorkingDay = FindWorkingDay(NewDate))
    {
        FindedWorkingDay->SetOrder(TimeIndex, NewOrder);
        return;
    }

    WorkingDay NewDay;

    NewDay.Date = NewDate;
    NewDay.SetOrder(TimeIndex, NewOrder);
    OrdersList.push_back(NewDay);
}

void MainWindow::SetOrderInTablWidget(int Row, QVector<QString> const& NewOrder)
{
    for (int i = 0; i < ColumnTypeMax; ++i)
    {
        if (QTableWidgetItem* NameItem = ui->TW_Orders->item(Row, i))
        {
            NameItem->setText(NewOrder[i]);
        }
    }
}

void MainWindow::ClearAllOrdersInTablWidget()
{
    for (int i = 0; i < ProgramStatics::WorkingHours; ++i)
    {
        SetOrderInTablWidget(i, ProgramStatics::EmptyWorkingDay);
    }
}

void MainWindow::on_PB_AddOrder_clicked()
{
    int RowIndex = ui->TW_Orders->currentRow();

    if (RowIndex < 0)
    {
        return;
    }

    QVector<QString> const Param =
    {
        ui->LE_Name->text(),
        ui->LE_Surname->text(),
        ui->LE_Phone->text(),
        ui->CB_SessionType->currentText(),
        ui->SB_Cost->text()
    };

    SetOrderInTablWidget(RowIndex, Param);
    SetOrder(ui->W_Calendar->selectedDate(), RowIndex, Param);
    ui->PB_AddOrder->setEnabled(false);
}

void MainWindow::on_PB_DeleteOrder_clicked()
{
    int RowIndex = ui->TW_Orders->currentRow();

    if (RowIndex < 0)
    {
        return;
    }

    SetOrderInTablWidget(RowIndex, ProgramStatics::EmptyWorkingDay);
    SetOrder(ui->W_Calendar->selectedDate(), RowIndex, ProgramStatics::EmptyWorkingDay);
    int Row    = ui->TW_Orders->currentRow();
    int Column = ui->TW_Orders->currentColumn();

    on_TW_Orders_currentCellChanged(Row, Column, Row, Column);
}

void MainWindow::on_W_Calendar_selectionChanged()
{
    if (WorkingDay const* FindedDay = FindWorkingDay(ui->W_Calendar->selectedDate()))
    {
        for (int i = 0; i < ProgramStatics::WorkingHours; ++i)
        {
            SetOrderInTablWidget(i, FindedDay->Orders[i]);
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

    if (QTableWidgetItem* SessionTypeItem = ui->TW_Orders->item(currentRow, SessionType))
    {
        ui->CB_SessionType->setCurrentText(SessionTypeItem->text());
    }

    if (QTableWidgetItem* CostItem = ui->TW_Orders->item(currentRow, Cost))
    {
        ui->SB_Cost->setValue(CostItem->text().toInt());
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

void MainWindow::on_CB_SessionType_currentIndexChanged(int)
{
    SetCheckValidationOfAddOrderButton(true);
}
