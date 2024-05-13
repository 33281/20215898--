#include "calendarwidget.h"
#include "calendarinfo.h"

#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QDateTime>

#define MARGIN      10//边缘
#define GRID_SPACE  5 //网格区域
#define CELL_TITLE_HTIGHT 30//子模块标题高度
#define CALENDAR_TITLE    50//万年历标题高度（时间）

static const QStringList s_strWeeks = QStringList() << "日" << "一" << "二" << "三" << "四" << "五" << "六";//设置星期条

CalendarWidget::CalendarWidget(QWidget *parent) : QWidget(parent) ,
    m_cellType(CellWeek)
{
    m_date = QDate::currentDate();

    m_nRowCount = 6;//设置6行7列
    m_nColCount = 7;
    m_cellWidth = 50;//设置宽度50高度40
    m_cellHeight = 40;
    m_nHoverIndex = -1;

    setChangeCellType(CellWeek);
    this->setMouseTracking(true);

    m_animation = new QPropertyAnimation(this, "geometry");
    m_animation->setDuration(200);
    m_animation->setEasingCurve(QEasingCurve::Linear);
}

CalendarWidget::~CalendarWidget()
{

}

void CalendarWidget::setChangeCellType(CellType type)
{
    m_startYear = m_date.year();
    m_cellType = type;
    m_nRowCount = (CellWeek == type) ? 6 : 3;
    m_nColCount = (CellWeek == type) ? 7 : 4;
    if (CellWeek == type) m_btnCalendar.text = m_date.toString("yyyy年MM月");
    else if (CellMonth == type) m_btnCalendar.text = m_date.toString("yyyy年");
    else if (CellYear == type) m_btnCalendar.text = m_date.toString("%1 - %2").arg(m_startYear).arg(m_startYear + 11);

    QDate dateTemp = QDate(m_date.year(), m_date.month(), 1);
    m_stratMonth = dateTemp.dayOfWeek();
    dateTemp = dateTemp.addMonths(-1);
    m_prevMonthDays = dateTemp.daysInMonth();
    calcCellSize();
    this->update();//更新窗体
}

void CalendarWidget::setCurrentDate()
{
    m_date = QDate::currentDate();
    setChangeCellType(m_cellType);
}

void CalendarWidget::calcCellSize()
{
    m_btnCalendar.rect = QRect(10, 10, this->width() / 2, 30);
    m_btnNext.rect = QRect(this->width() - 30, 15, 20, 20);
    m_btnPrev.rect = QRect(this->width() - 60, 15, 20, 20);
    m_btnNext.text = QString(">");
    m_btnPrev.text = QString("<");

    m_cellWidth = (this->width() - MARGIN * 2 - GRID_SPACE * (m_nColCount - 1)) / m_nColCount;
    m_cellHeight = (this->height() - MARGIN * 2 - GRID_SPACE * (m_nRowCount - 1) - CELL_TITLE_HTIGHT - CALENDAR_TITLE) / m_nRowCount;
    this->update();
}

void CalendarWidget::resizeEvent(QResizeEvent *event)
{
    calcCellSize();
    if (m_scaleRect.width() == 0) m_scaleRect = this->geometry();
    QWidget::resizeEvent(event);
}

void CalendarWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.fillRect(this->rect(), QColor("#3c3c3c"));

#if 0
    QFont font("Mircosoft YaHei");
    font.setPixelSize(12);
    painter.setFont(font);
#endif

    drawGrids(&painter);
    drawTitles(&painter);

    if (CellYear == m_cellType) drawYears(&painter);
    else if (CellMonth == m_cellType) drawMonth(&painter);
    else drawCalendar(&painter);
}

void CalendarWidget::drawTitles(QPainter *painter)
{
    painter->save();
    QFont font = painter->font();
    font.setPixelSize(16);
    painter->setFont(font);
    painter->setPen(m_btnCalendar.isHover ?  QColor("#ffffff") : QColor("#d0d0d0"));
    painter->drawText(m_btnCalendar.rect, Qt::AlignVCenter, m_btnCalendar.text);//设置垂直方向居中

    font.setPixelSize(20);
    painter->setFont(font);
    painter->setPen(m_btnPrev.isHover ?  QColor("#ffffff") : QColor("#666666"));
    painter->drawText(m_btnPrev.rect, Qt::AlignVCenter, m_btnPrev.text);

    painter->setPen(m_btnNext.isHover ?  QColor("#ffffff") : QColor("#666666"));
    painter->drawText(m_btnNext.rect, Qt::AlignVCenter, m_btnNext.text);

    painter->restore();
}

void CalendarWidget::drawGrids(QPainter *painter)
{
    painter->save();
    for (int ir = 0; ir < m_nRowCount; ir++) {
        for (int ic = 0; ic < m_nColCount; ic ++) {
            painter->setPen(((ir * m_nColCount + ic) == m_nHoverIndex) ? QColor("#eeeeee") : QColor("#575757"));
            painter->drawRect(ic * (m_cellWidth + GRID_SPACE) + MARGIN,
                              ir * (m_cellHeight + GRID_SPACE) + MARGIN + CALENDAR_TITLE +
                              ((CellWeek == m_cellType) ? CELL_TITLE_HTIGHT : 0),
                              m_cellWidth,
                              m_cellHeight);
        }
    }

    painter->restore();
}

void CalendarWidget::drawYears(QPainter *painter)
{
    painter->save();
    QFont font = painter->font();
    font.setPixelSize(16);//设置字号
    painter->setFont(font);

    int year = QDate::currentDate().year();
    for (int i = 0; i < 12; i++) {
        painter->setPen(i > 9 ? QColor("#999999") : QColor("#ffffff"));
        QRect rect = QRect((i % 4) * (m_cellWidth + GRID_SPACE) + MARGIN,
                           (i / 4) * (m_cellHeight + GRID_SPACE) + MARGIN + CALENDAR_TITLE,
                           m_cellWidth, m_cellHeight);
        if (year == (m_startYear + i)) {
            painter->fillRect(rect, QColor("#0078d7"));
        }
        painter->drawText(rect, Qt::AlignCenter, QString("%1").arg(m_startYear + i));
    }
    painter->restore();
}

void CalendarWidget::drawMonth(QPainter *painter)
{
    painter->save();
    QFont font = painter->font();
    font.setPixelSize(16);
    painter->setFont(font);
    int month = QDate::currentDate().month();

    for (int i = 0; i < 12; i++) {
        painter->setPen(i > 11 ? QColor("#999999") : QColor("#ffffff"));
        QRect rect = QRect((i % 4) * (m_cellWidth + GRID_SPACE) + MARGIN,
                           (i / 4) * (m_cellHeight + GRID_SPACE) + MARGIN + CALENDAR_TITLE,
                           m_cellWidth, m_cellHeight);
        if (month == (i + 1) && m_date.year() == QDate::currentDate().year())
        {
            painter->fillRect(rect, QColor("#0078d7"));
        }
        painter->drawText(rect, Qt::AlignCenter, QString("%1月").arg(i % 12 + 1));
    }
    painter->restore();
}

void CalendarWidget::drawCalendar(QPainter *painter)
{
    painter->save();
    QFont font = painter->font();
    font.setPixelSize(14);
    painter->setFont(font);
    painter->setPen(QColor("#ffffff"));

    for (int i = 0; i < m_nColCount; i++) {
        QRect rect(MARGIN + i * (m_cellWidth + GRID_SPACE), MARGIN + CALENDAR_TITLE, m_cellWidth, CELL_TITLE_HTIGHT);
        painter->drawText(rect, Qt::AlignCenter, s_strWeeks.at(i));
    }

    int daysInMonth = m_date.daysInMonth();

    for (int ir = 0; ir < m_nRowCount; ir++) {
        for (int ic = 0; ic < m_nColCount; ic ++) {
            QRect rect(ic * (m_cellWidth + GRID_SPACE) + MARGIN,
                       ir * (m_cellHeight + GRID_SPACE) + MARGIN + CELL_TITLE_HTIGHT + CALENDAR_TITLE,
                       m_cellWidth,
                       m_cellHeight);
            int index = ir * m_nColCount + ic;
            painter->setPen(QColor("#8a8a8a"));
            font.setPixelSize(14);
            painter->setFont(font);

            // prev month
            if (index < m_stratMonth) {
                int day = m_prevMonthDays - (m_stratMonth - index - 1);
                QDate date = m_date.addMonths(-1);
                date.setDate(date.year(), date.month(), day);
                drawDayOfMonth(painter, rect, date, QColor("#8a8a8a"));
            } else if (index >= (m_stratMonth + daysInMonth)) {
                int day = index - daysInMonth - m_stratMonth + 1;
                QDate date = m_date.addMonths(1);
                date.setDate(date.year(), date.month(), day);
                drawDayOfMonth(painter, rect, date, QColor("#8a8a8a"));
            } else {
                int day = index - m_stratMonth + 1;
                if (QDate(m_date.year(), m_date.month(), day) == QDate::currentDate()) {
                    painter->fillRect(rect, QColor("#0078d7"));
                }
                drawDayOfMonth(painter, rect, QDate(m_date.year(), m_date.month(), day), QColor("#ffffff"));
            }
        }
    }

    painter->restore();
}

void CalendarWidget::drawDayOfMonth(QPainter *painter, QRect rect, QDate date, QColor color)
{
    painter->setPen(color);

    QFont font = painter->font();
    font.setPixelSize(14);
    painter->setFont(font);
    QRect rectTemp(rect.left(), rect.top(), rect.width(), rect.height() / 2);
    painter->drawText(rectTemp, Qt::AlignCenter, QString("%1").arg(date.day()));

    font.setPixelSize(10);
    painter->setFont(font);
    rectTemp = QRect(rectTemp.left(), rectTemp.bottom(), rectTemp.width(), rectTemp.height());
}

void CalendarWidget::mousePressEvent(QMouseEvent *e)
{
    if (Qt::LeftButton == e->button()) {
        if (m_btnCalendar.rect.contains(e->pos())) {
            if (CellWeek == m_cellType) {
                setChangeCellType(CellMonth);
            } else if (CellMonth == m_cellType) {
                setChangeCellType(CellYear);
            } else if (CellYear == m_cellType) return;

            m_animation->setStartValue(QRect(m_scaleRect.x() + m_scaleRect.width() / 2,
                                             m_scaleRect.y() + m_scaleRect.height() / 2, 10, 10));
            m_animation->setEndValue(m_scaleRect);
            m_animation->start();
        }
        else if (m_btnPrev.rect.contains(e->pos())) {
            if (CellYear == m_cellType) {
                m_date = m_date.addYears(-16);
            } else if (CellMonth == m_cellType) {
                m_date = m_date.addYears(-1);
            } else if (CellWeek == m_cellType) {
                m_date = m_date.addMonths(-1);
            }
            setChangeCellType(m_cellType);
        } else if (m_btnNext.rect.contains(e->pos())) {
            if (CellYear == m_cellType) {
                m_date = m_date.addYears(16);
                setChangeCellType(CellYear);
            } else if (CellMonth == m_cellType) {
                m_date = m_date.addYears(1);
            } else if (CellWeek == m_cellType) {
                m_date = m_date.addMonths(1);
            }

            setChangeCellType(m_cellType);
        } else {
            calcMousePoint(e->pos());
        }
    }
}

void CalendarWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->y() < (CELL_TITLE_HTIGHT + CALENDAR_TITLE)) {
        m_btnCalendar.isHover = m_btnCalendar.rect.contains(e->pos());
        m_btnPrev.isHover = m_btnPrev.rect.contains(e->pos());
        m_btnNext.isHover = m_btnNext.rect.contains(e->pos());
        this->update(MARGIN, MARGIN, this->width() - MARGIN * 2, 40);
        return;
    }

    calcMousePoint(e->pos(), true);
    this->update();
}

void CalendarWidget::leaveEvent(QEvent *event)
{
    m_nHoverIndex = -1;
    this->update();
    QWidget::leaveEvent(event);
}

void CalendarWidget::calcMousePoint(QPoint pos, bool bHover)
{
    m_nHoverX = pos.x();
    m_nHoverY = pos.y();

    int nR = (m_nHoverY - MARGIN - CALENDAR_TITLE - ((CellWeek == m_cellType) ? CELL_TITLE_HTIGHT : 0)) / (m_cellHeight + GRID_SPACE);
    int nC = (m_nHoverX - MARGIN) / (m_cellWidth + GRID_SPACE);
    if (nC >= m_nColCount) nC = m_nColCount  - 1;
    if (nR >= m_nRowCount) nR = m_nRowCount  - 1;

    int index = nC + nR * m_nColCount + 1;
    if (bHover) m_nHoverIndex = index - 1;
    else {
        if (CellWeek == m_cellType) {

            return;
        }

        if (CellYear == m_cellType) {
            m_date = m_date.addYears(index - 1);
            m_btnCalendar.text = m_date.toString("yyyy年");
            setChangeCellType(CellMonth);
        } else if (CellMonth == m_cellType) {
            if (index > 11) m_date = m_date.addYears(1);
            m_date = m_date.addMonths((index % 12) - m_date.month());
            setChangeCellType(CellWeek);
        }

        m_animation->setStartValue(QRect(m_scaleRect.x() + m_scaleRect.width() / 2,
                                         m_scaleRect.y() + m_scaleRect.height() / 2, 10, 10));
        m_animation->setEndValue(m_scaleRect);
        m_animation->start();
    }
}
