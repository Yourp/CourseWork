#ifndef PROGRAMSTATICS_H
#define PROGRAMSTATICS_H
#include <QVector>

enum ColumnTypes
{
    Name = 0,
    Surname,
    PhoneNumber,
    SessionType,
    Cost,
    ColumnTypeMax
};

class ProgramStatics
{
    ProgramStatics() {}

public:

    static const QVector<QString> PhotosessionType;

    static const QVector<QString> EmptyWorkingDay;

    static constexpr uint8_t WorkingHours = 8;

};

#endif // PROGRAMSTATICS_H
