#ifndef SHADOWCANENDARWIDGET_H
#define SHADOWCANENDARWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QPropertyAnimation>

class RectButton {
public:
    RectButton()  {}

    QRect rect;
    QString text;
    bool isHover;//鼠标滑过菜单项图标高亮显示
};

class CalendarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalendarWidget(QWidget *parent = nullptr);
    ~CalendarWidget();

    typedef enum {CellYear, CellMonth, CellWeek} CellType;
    void setChangeCellType(CellType type);

    void setCurrentDate();
signals:

protected:
    QDate  m_date;
    int    m_startYear;
    int    m_stratMonth;
    int    m_prevMonthDays;

    QRect m_scaleRect;

    CellType m_cellType;
    int m_nRowCount;
    int m_nColCount;
    int m_cellWidth;
    int m_cellHeight;

    int m_nHoverIndex;
    int m_nHoverX;
    int m_nHoverY;

    QPropertyAnimation *m_animation;

    RectButton m_btnCalendar;
    RectButton m_btnPrev;
    RectButton m_btnNext;

protected:
    void calcCellSize();
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *) override;
    void drawTitles(QPainter *painter);//标题：yyyy年MM月 yyyy年 yyyy-yyyy
    void drawGrids(QPainter *painter);
    void drawYears(QPainter *painter);
    void drawMonth(QPainter *painter);
    void drawCalendar(QPainter *painter);
    void drawDayOfMonth(QPainter *painter, QRect rect, QDate date, QColor color);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void calcMousePoint(QPoint pos, bool bHover = false);
};

#endif // SHADOWCANENDARWIDGET_H
