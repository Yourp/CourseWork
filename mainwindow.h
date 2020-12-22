#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

class WorkingDay;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /** Вызывается, когда окно программы закрывается, но перед деструктором конечно же. */
    void closeEvent(QCloseEvent *Event) override;

    void SetCheckValidationOfAddOrderButton(bool NewVal) { bCheckValidationOfAddOrderButton = NewVal; }

private slots:

    /** Вызывается каждые 50мс. */
    void OnTick();

    /** Вызывается при изменении любой строки ввода данных. */
    void AnyLineChanged(const QString & Arg);

    /** Методы, которые сгенерированы самим QT. */

    /** Вызывается во время нажатия кнопки: Записать клиента. */
    void on_PB_AddOrder_clicked();

    /** Вызывается во время смены дня в календаре. */
    void on_W_Calendar_selectionChanged();

    /** Вызывается во время выбора строки в таблице заказов. */
    void on_TW_Orders_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    /** Вызывается во время нажатия кнопки: Удалить заказ. */
    void on_PB_DeleteOrder_clicked();

    /** Вызывается во время смены типа фотосъемки. */
    void on_CB_SessionType_currentIndexChanged(int index);

private:

    /** Переменная QT. В ней храняется данные всех визуальных элементов. */
    Ui::MainWindow *ui;

    /** Сохраняем данные в файл. */
    void SaveData();

    /** Извлекаем данные из файла. */
    void LoadData();

    /** Пробуем найти рабочий день в списке OrdersList. */
    WorkingDay* FindWorkingDay(QDate const& date);

    /** Записываем данные заказа в список OrdersList. */
    void SetOrder(QDate const& NewDate, int TimeIndex, QVector<QString> const& NewOrder);

    /** Чистим весь день от заказов. */
    void ClearAllOrdersInTablWidget();

    /** Редактируем выбранный заказ в таблице. */
    void SetOrderInTablWidget(int Row, QVector<QString> const& NewOrder);

    /** Обработка активации кнопки: Записать клиента. */
    void HandleAddOrderButton();

    /** Обработка активации кнопки: Удалить заказ. */
    void HandleDeleteOrderButton();

    /** Указатель на таймер. */
    QTimer* Timer;

    /** Список всех рабочих дней с заказами. */
    QVector<WorkingDay> OrdersList;

    /** Переменная которая контролирует обработку активации кнопки: Записать клиента. */
    uint8_t bCheckValidationOfAddOrderButton : 1;

};
#endif // MAINWINDOW_H
