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

private slots:

    void on_PB_AddOrder_clicked();
    void on_W_Calendar_selectionChanged();

private:
    Ui::MainWindow *ui;

    void SaveData();
    void LoadData();


    WorkingDay* FindWorkingDay(QDate const& date);
    void SetOrder(QDate const& NewDate, int TimeIndex, QString const& NewName, QString const& NewSurname, QString const& NewPhoneNumber);
    void ClearAllOrdersInTablWidget();
    void SetOrderInTablWidget(int Row, QString const& NewName, QString const& NewSurname, QString const& NewPhoneNumber);

    QVector<WorkingDay> OrdersList;

};
#endif // MAINWINDOW_H
