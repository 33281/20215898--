#ifndef LUNARCALENDARINFO_H
#define LUNARCALENDARINFO_H

#include <QObject>
#ifdef quc
#include <QtUiPlugin/QDesignerExportWidget>
#endif
class CalendarInfo : public QObject

{
    Q_OBJECT
public:
    explicit CalendarInfo(QObject *parent = 0);

    //计算是否闰年
    bool isLoopYear(int year);

    //计算指定年月该月共多少天
    int getMonthDays(int year, int month);

    //计算指定年月对应到该月共多少天
    int getTotalMonthDays(int year, int month);

    //计算指定年月对应星期几
    int getFirstDayOfWeek(int year, int month);
private:
    QList<int> monthAdd;                //公历每月前面的天数

};

#endif // LUNARCALENDARINFO_H
