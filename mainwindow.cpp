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


    /** Заполняем комбобокс нашими названиями типов фотосъемки. */
    for (auto Itr : ProgramStatics::PhotosessionType)
    {
        ui->CB_SessionType->addItem(Itr);
    }

    /** Загружаем данные с файла Order.ini. */
    LoadData();

    /** Выбираем в календаре день текущей даты. */
    ui->W_Calendar->showToday();

    /**
     * Принудительно вызываем эту функцию, так как предыдущий метод showToday() почему то не делает этого.
     * Её нужно вызвать, так как мы должны в таблицы видеть запии фотографа на сегодня.
     */
    on_W_Calendar_selectionChanged();

    /** Сдесь мы указываем, что на следующем тике нам нужно проверить все условия для кнопки - Записать клиента. Что бы включить её если что. */
    SetCheckValidationOfAddOrderButton(true);

    /** Создаем таймер, который будет циклично тикать и выполнять что-то. */
    Timer = new QTimer(this);

    /** Указываем таймеру, что каждый раз когда он тикает - должна срабатывать функция OnTick(). */
    connect(Timer, SIGNAL(timeout()), this, SLOT(OnTick()));

    /** Запускаем таймер и указываем, что он должен тикать раз в 50 мс. */
    Timer->start(50);
}

MainWindow::~MainWindow()
{
    /** Удаляем ранее выделеную память для переменных. */

    delete Timer;
    delete ui;
}

void MainWindow::OnTick()
{
    if (bCheckValidationOfAddOrderButton)
    {
        /** Сразу выключаем переменную, так как нам не нужно что бы это выполнялось каждый тик. */
        SetCheckValidationOfAddOrderButton(false);

        /** Обрабатываем условия кнопки: Записать клиента и включаем её, если условия соблюдены. */
        HandleAddOrderButton();
    }
}

void MainWindow::closeEvent(QCloseEvent *Event)
{
    /** Сохраняем данные в файл Order.ini. */
    SaveData();

    /** Метод closeEvent виртуальный, по этому, что бы не ломать логику работы данного метода - вызываем его у класса родителя. */
    QMainWindow::closeEvent(Event);
}

void MainWindow::SaveData()
{
    /** Открываем Order.ini. */
    QSettings Data("Order.ini", QSettings::IniFormat);

    /** Очищаем файл для новых записей. */
    Data.clear();

    /** Устанавливаем кодировку текста с которым будем работать. Что бы русский текст не сохранялся в виде непонятных символов. */
    Data.setIniCodec("UTF-8");

    /** Номер индекса текущего элемента. */
    int OrderSaveIndex = 0;

    /** Сохраняем каждый элемент из списка OrdersList в файл Order.ini. Основная суть есть в документации QT. */
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
    /** Открываем и извлекаем данные с Order.ini. */
    QSettings Data("Order.ini", QSettings::IniFormat);

    /** Устанавливаем кодировку текста с которым будем работать. Что бы русский текст не сохранялся в виде непонятных символов. */
    Data.setIniCodec("UTF-8");

    /** Далее всё аналогично как и в SaveData, только здесь мы наоборот, полученые данные с файла заполняем в список OrdersList. */

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
    /** Узнаем выбранный номер строки в нашей таблице заказов. */
    int RowIndex = ui->TW_Orders->currentRow();

    if (RowIndex < 0)
    {
        /** Если строка не выбрана, то RowIndex будет равен -1. Не выполняем дальнейшую логику, если строка не выбрана. */
        return;
    }

    /** Проверяем, если поля ввода Имени, Фамилии и Телефона не пустые. Сохраняем результат в переменную. */
    bool bEnableAddOrderButton = !ui->LE_Name->text().isEmpty() && !ui->LE_Surname->text().isEmpty() && !ui->LE_Phone->text().isEmpty();

    /** Создаем список с параметрами и записываем их, последовательность важна (должна быть такая же, как и в ColumnTypes). */
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
        /** Извлекаем клетку из таблицы заказов. */
        if (QTableWidgetItem* Item = ui->TW_Orders->item(RowIndex, i))
        {
            /** Проверяем разницу текста клетки и соответствующего поля. */
            if (Item->text() != Param[i])
            {
                /** Включаем кнопку: Записать клиента, если есть разница текста. */
                ui->PB_AddOrder->setEnabled(bEnableAddOrderButton);

                /** Больше ничего не нужно - выходим с функции. */
                return;
            }
        }
    }

    /** Если мы проверили все клетки выбраного заказа с полями ввода и не нашли разницу в символах - выключаем кнопку на всякий случай. */
    ui->PB_AddOrder->setEnabled(false);
}

void MainWindow::HandleDeleteOrderButton()
{
    /** Узнаем выбранный номер строки в нашей таблице заказов. */
    int RowIndex = ui->TW_Orders->currentRow();

    if (RowIndex < 0)
    {
        /** Если строка не выбрана, то RowIndex будет равен -1. Не выполняем дальнейшую логику, если строка не выбрана. */
        return;
    }

    for (int i = 0; i < ColumnTypeMax; ++i)
    {
        /** Последовательно извлекаем клетку из таблицы заказов. */
        if (QTableWidgetItem* Item = ui->TW_Orders->item(RowIndex, i))
        {
            /** Проверяем имеет ли клетка хоть один символ. */
            if (!Item->text().isEmpty())
            {
                /** Если хоть одна клетка не пустая - активируем кнопку: Удалить заказ. */
                ui->PB_DeleteOrder->setEnabled(true);

                /** Больше ничего не нужно - выходим с функции прервав цикл. */
                return;
            }
        }
    }

    /** Если мы проверили все клетки выбраного заказа с полями ввода и все они пустые - выключаем кнопку на всякий случай. */
    ui->PB_DeleteOrder->setEnabled(false);
}

WorkingDay *MainWindow::FindWorkingDay(QDate const& date)
{
    /** Пытаемся найти рабочий день по дате из списка OrdersList. */

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
    /** Пытаемся найти рабочий день, вдруг он уже есть в OrdersList. */
    if (WorkingDay* FindedWorkingDay = FindWorkingDay(NewDate))
    {
        /** Нашли. Устанавливаем в него данные заказа. */
        FindedWorkingDay->SetOrder(TimeIndex, NewOrder);
        return;
    }

    /** Мы не нашли рабочий день в OrdersList, по этому создаем новый. */
    WorkingDay NewDay;

    /** Устанавливаем дату рабочего дня. */
    NewDay.Date = NewDate;

    /** Устанавливаем параметры заказа. */
    NewDay.SetOrder(TimeIndex, NewOrder);

    /** Добавляем рабочий день в список OrdersList. */
    OrdersList.push_back(NewDay);
}

void MainWindow::SetOrderInTablWidget(int Row, QVector<QString> const& NewOrder)
{
    /** Последовательно заполняем клетки выбранной строки (в таблице заказа) новыми данными из NewOrder. */
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
    /** Полностью очищаем все заказы выбранного дня в таблице заказов. Это может происходить, когда мы переключаем день, а в нем нет заказов. */
    for (int i = 0; i < ProgramStatics::WorkingHours; ++i)
    {
        SetOrderInTablWidget(i, ProgramStatics::EmptyWorkingDay);
    }
}

void MainWindow::on_PB_AddOrder_clicked()
{
    /** Узнаем выбранный номер строки в нашей таблице заказов. */
    int RowIndex = ui->TW_Orders->currentRow();

    if (RowIndex < 0)
    {
        /** Если строка не выбрана, то RowIndex будет равен -1. Не выполняем дальнейшую логику, если строка не выбрана. */
        return;
    }

    /** Создаем список с параметрами и записываем их, последовательность важна (должна быть такая же, как и в ColumnTypes). */
    QVector<QString> const Param =
    {
        ui->LE_Name->text(),
        ui->LE_Surname->text(),
        ui->LE_Phone->text(),
        ui->CB_SessionType->currentText(),
        ui->SB_Cost->text()
    };

    /** Устанавливаем заказ в таблицу. */
    SetOrderInTablWidget(RowIndex, Param);

    /** Фиксируем заказ внутри программы (в OrdersList). */
    SetOrder(ui->W_Calendar->selectedDate(), RowIndex, Param);

    /** Сразу выключаем кнопку от повторного нажатия. Заказ записан, данные синхронизированы. */
    ui->PB_AddOrder->setEnabled(false);
}

void MainWindow::on_PB_DeleteOrder_clicked()
{
    /** Узнаем выбранный номер строки в нашей таблице заказов. */
    int RowIndex = ui->TW_Orders->currentRow();

    if (RowIndex < 0)
    {
        /** Если строка не выбрана, то RowIndex будет равен -1. Не выполняем дальнейшую логику, если строка не выбрана. */
        return;
    }

    /** Устанавливаем пустой заказ в таблицу. */
    SetOrderInTablWidget(RowIndex, ProgramStatics::EmptyWorkingDay);

    /** Фиксируем пустой заказ внутри программы (в OrdersList). */
    SetOrder(ui->W_Calendar->selectedDate(), RowIndex, ProgramStatics::EmptyWorkingDay);

    /** Извлекаем номер выбранной строки в таблице заказов. */
    int Row    = ui->TW_Orders->currentRow();

    /** Это не нужно в принципе (но добавляем для хороших манер). Извлекаем номер выбранного столба в таблице заказов. */
    int Column = ui->TW_Orders->currentColumn();

    /** Выполняем функционал изменения выбранной строки с таблице заказов. Это нужно для того, что бы поля ввода изменились так же. */
    on_TW_Orders_currentCellChanged(Row, Column, Row, Column);
}

void MainWindow::on_W_Calendar_selectionChanged()
{
    /** Пробуем найти этот день в списке OrdersList. */
    if (WorkingDay const* FindedDay = FindWorkingDay(ui->W_Calendar->selectedDate()))
    {
        /** Нашли. Заполняем таблицу заказов этими данными. */
        for (int i = 0; i < ProgramStatics::WorkingHours; ++i)
        {
            SetOrderInTablWidget(i, FindedDay->Orders[i]);
        }
    }
    else
    {
        /** Не нашли. Значить нет заказов в этот день. Показываем что их нет - чистим таблицу. */
        ClearAllOrdersInTablWidget();
    }

    /** Извлекаем номер выбранной строки в таблице заказов. */
    int Row    = ui->TW_Orders->currentRow();

    /** Это не нужно в принципе (но добавляем для хороших манер). Извлекаем номер выбранного столба в таблице заказов. */
    int Column = ui->TW_Orders->currentColumn();

    /** Выполняем функционал изменения выбранной строки с таблице заказов. Это нужно для того, что бы поля ввода изменились так же. */
    on_TW_Orders_currentCellChanged(Row, Column, Row, Column);
}

void MainWindow::on_TW_Orders_currentCellChanged(int currentRow, int, int, int)
{
    /** Извлекаем клетку с именем заказчика. */
    if (QTableWidgetItem* NameItem = ui->TW_Orders->item(currentRow, Name))
    {
        /** Строку ввода имени заполняем данными с клетки. */
        ui->LE_Name->setText(NameItem->text());
    }

    /** Извлекаем клетку с фамилией заказчика. */
    if (QTableWidgetItem* SurnameItem = ui->TW_Orders->item(currentRow, Surname))
    {
        /** Строку ввода фимилии заполняем данными с клетки. */
        ui->LE_Surname->setText(SurnameItem->text());
    }

    /** Извлекаем клетку с телефоном заказчика. */
    if (QTableWidgetItem* PhoneItem = ui->TW_Orders->item(currentRow, PhoneNumber))
    {
        /** Строку ввода телефона заполняем данными с клетки. */
        ui->LE_Phone->setText(PhoneItem->text());
    }

    /** Извлекаем клетку с типом фотосъемки. */
    if (QTableWidgetItem* SessionTypeItem = ui->TW_Orders->item(currentRow, SessionType))
    {
        /** Синхронизируем тип фотосьемки с типом в клетке. */
        ui->CB_SessionType->setCurrentText(SessionTypeItem->text());
    }

    /** Извлекаем клетку с ценой заказа. */
    if (QTableWidgetItem* CostItem = ui->TW_Orders->item(currentRow, Cost))
    {
        /** Строку ввода цены заполняем данными с клетки. */
        ui->SB_Cost->setValue(CostItem->text().toInt());
    }

    /** Проверяем условия кнопки удаления заказа и активируем её, если условия соблюдены. */
    HandleDeleteOrderButton();
}

void MainWindow::AnyLineChanged(const QString & Arg)
{
    if (Arg.isEmpty())
    {
        /** Если любая строка ввода пустая - деактивируем кнопку: Записать клиента. */
        ui->PB_AddOrder->setEnabled(false);

        /** Одна из строк пустая - не делаем ничего больше. */
        return;
    }

    /** Сообщаем, что нам на следующий вызов функции OnTick() нужно определить активацию кнопки: Записать клиента. */
    SetCheckValidationOfAddOrderButton(true);
}

void MainWindow::on_CB_SessionType_currentIndexChanged(int)
{
    /** Сообщаем, что нам на следующий вызов функции OnTick() нужно определить активацию кнопки: Записать клиента. */
    SetCheckValidationOfAddOrderButton(true);
}
