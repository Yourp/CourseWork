#include "workingday.h"

WorkingDay::WorkingDay()
{
    /** Заполняем день пустыми заказами. Так проще работать с рабочим днем оперируя индексами. */
    for (int i = 0; i < ProgramStatics::WorkingHours; ++i)
    {
        Orders[i].fill("", ColumnTypeMax);
    }
}

void WorkingDay::SetOrder(int TimeIndex, QVector<QString> const& NewOrder)
{
    for (int i = 0; i < ColumnTypeMax; ++i)
    {
        Orders[TimeIndex][i] = NewOrder[i];
    }
}
