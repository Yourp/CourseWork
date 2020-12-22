#ifndef WORKINGDAY_H
#define WORKINGDAY_H

#include <QDate>
#include "programstatics.h"

/** Класс рабочего дня. */
class WorkingDay
{
public:

    WorkingDay();

    /** Дата рабочего дня. */
    QDate Date;

    /** Список заказов. */
    QVector<QString> Orders[ProgramStatics::WorkingHours];

    /** Записываем данные заказа. */
    void SetOrder(int TimeIndex, QVector<QString> const& NewOrder);
};

#endif // WORKINGDAY_H
