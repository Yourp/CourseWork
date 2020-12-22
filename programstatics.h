#ifndef PROGRAMSTATICS_H
#define PROGRAMSTATICS_H
#include <QVector>

/** Нумерация столбцов данных в таблице. На ней завязана логика обработки списков. Последовательность важна. */
enum ColumnTypes
{
    Name = 0,
    Surname,
    PhoneNumber,
    SessionType,
    Cost,
    ColumnTypeMax
};

/** Класс общих статических данных программы. */
class ProgramStatics
{
    ProgramStatics() {}

public:

    /** Хранит названия типов фотосъемки. */
    static const QVector<QString> PhotosessionType;

    /** Это список с пустыми данными. Им просто легче чистить данные целого заказа. */
    static const QVector<QString> EmptyWorkingDay;

    /** Количество рабочих часов фотографа. */
    static constexpr uint8_t WorkingHours = 8;

};

#endif // PROGRAMSTATICS_H
