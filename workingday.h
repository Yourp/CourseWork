#ifndef WORKINGDAY_H
#define WORKINGDAY_H

#include <QDate>
#include "programstatics.h"

class WorkingDay
{
public:

    WorkingDay();

    QDate Date;
    QVector<QString> Orders[ProgramStatics::WorkingHours];

    void SetOrder(int TimeIndex, QVector<QString> const& NewOrder);
};

#endif // WORKINGDAY_H
