#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>

enum TableColumnType
{
    Name = 0,
    Surname,
    PhoneNumber,
    ColumnTypeMax
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

private:
    Ui::MainWindow *ui;

    void SaveData();
    void LoadData();

    QMap<QDate, QString> OrdersMap;

};
#endif // MAINWINDOW_H
