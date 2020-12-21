#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>
#include <QMap>

constexpr uint8_t WorkingHours = 8;

enum TableColumnType
{
    Name = 0,
    Surname,
    PhoneNumber,
    ColumnTypeMax
};

struct WorkingDay
{
    QDate Date;
    QString Orders[WorkingHours][ColumnTypeMax];

    void SetOrder(int TimeIndex, QString const& NewName, QString const& NewSurname, QString const& NewPhoneNumber);
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent *Event) override;
    void SetCheckValidationOfAddOrderButton(bool NewVal) { bCheckValidationOfAddOrderButton = NewVal; }

private slots:

    void OnTick();
    void on_PB_AddOrder_clicked();
    void on_W_Calendar_selectionChanged();
    void on_TW_Orders_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);
    void AnyLineChanged(const QString & Arg);
    void on_PB_DeleteOrder_clicked();

private:
    Ui::MainWindow *ui;

    void SaveData();
    void LoadData();


    WorkingDay* FindWorkingDay(QDate const& date);
    void SetOrder(QDate const& NewDate, int TimeIndex, QString const& NewName, QString const& NewSurname, QString const& NewPhoneNumber);
    void ClearAllOrdersInTablWidget();
    void SetOrderInTablWidget(int Row, QString const& NewName, QString const& NewSurname, QString const& NewPhoneNumber);
    void HandleAddOrderButton();
    void HandleDeleteOrderButton();

    QTimer* Timer;

    QVector<WorkingDay> OrdersList;
    uint8_t bCheckValidationOfAddOrderButton : 1;

};
#endif // MAINWINDOW_H
