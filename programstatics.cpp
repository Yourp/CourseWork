#include "programstatics.h"

/** Инициализируем статические переменные класса ProgramStatics. */

const QVector<QString> ProgramStatics::EmptyWorkingDay = QVector<QString>().fill("", ColumnTypeMax);

const QVector<QString> ProgramStatics::PhotosessionType =
{
    "Портретная",
    "Семейная",
    "Свадебная",
    "Детская"
};


