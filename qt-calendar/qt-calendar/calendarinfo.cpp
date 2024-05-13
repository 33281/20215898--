#include "calendarinfo.h"
#include "qmutex.h"
#include "qdebug.h"

CalendarInfo::CalendarInfo(QObject *parent) : QObject(parent)
{
   //公历每月前面的天数
    monthAdd << 0 << 31 << 59 << 90 << 120 << 151 << 181 << 212 << 243 << 273 << 304 << 334;
}

//计算是否闰年
bool CalendarInfo::isLoopYear(int year)
{
    return (((0 == (year % 4)) && (0 != (year % 100))) || (0 == (year % 400)));
}

//计算指定年月该月共多少天
int CalendarInfo::getMonthDays(int year, int month)
{
    int countDay = 0;
    int loopDay = isLoopYear(year) ? 1 : 0;

    switch (month) {
    case 1:
        countDay = 31;
        break;
    case 2:
        countDay = 28 + loopDay;
        break;
    case 3:
        countDay = 31;
        break;
    case 4:
        countDay = 30;
        break;
    case 5:
        countDay = 31;
        break;
    case 6:
        countDay = 30;
        break;
    case 7:
        countDay = 31;
        break;
    case 8:
        countDay = 31;
        break;
    case 9:
        countDay = 30;
        break;
    case 10:
        countDay = 31;
        break;
    case 11:
        countDay = 30;
        break;
    case 12:
        countDay = 31;
        break;
    default:
        countDay = 30;
        break;
    }

    return countDay;
}

//计算指定年月对应到该月共多少天 每月前面的天数+loopday
int CalendarInfo::getTotalMonthDays(int year, int month)
{
    int countDay = 0;
    int loopDay = isLoopYear(year) ? 1 : 0;

    switch (month) {
    case 1:
        countDay = 0;
        break;
    case 2:
        countDay = 31;
        break;
    case 3:
        countDay = 59 + loopDay;
        break;
    case 4:
        countDay = 90 + loopDay;
        break;
    case 5:
        countDay = 120 + loopDay;
        break;
    case 6:
        countDay = 151 + loopDay;
        break;
    case 7:
        countDay = 181 + loopDay;
        break;
    case 8:
        countDay = 212 + loopDay;
        break;
    case 9:
        countDay = 243 + loopDay;
        break;
    case 10:
        countDay = 273 + loopDay;
        break;
    case 11:
        countDay = 304 + loopDay;
        break;
    case 12:
        countDay = 334 + loopDay;
        break;
    default:
        countDay = 0;
        break;
    }

    return countDay;
}

//计算指定年月对应星期几   已知公元1年1月1日星期一来推算
int CalendarInfo::getFirstDayOfWeek(int year, int month)
{
    int week = 0;
    week = (year + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;//基姆拉尔森计算公式 (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400表示闰年的个数
    week += getTotalMonthDays(year, month);
    week = week % 7;
    return week;
}
