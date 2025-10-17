#include "include/calendarevent.h"

CalendarEvent::CalendarEvent(CustomDateTime startTime, CustomDateTime endTime,
                             const QRectF &rect, QColor colorPrimary,
                             QColor colorSecondary, QColor colorTertiary,
                             bool enabled, QGraphicsItem *parent)
    : AbstractItem(rect, colorPrimary, colorSecondary, colorTertiary, enabled, parent)
    , m_startTime(startTime)
    , m_endTime(endTime)
    , m_text("New Event")
    , m_isAllDay(false)
{
}

CalendarEvent::CalendarEvent(CustomDateTime startTime, const QString &text,
                             const QRectF &rect, QColor colorPrimary,
                             QColor colorSecondary, QColor colorTertiary,
                             bool enabled, QGraphicsItem *parent)
    : AbstractItem(rect, colorPrimary, colorSecondary, colorTertiary, enabled, parent)
    , m_startTime(startTime)
    , m_text(text)
    , m_isAllDay(true)
{
    calculateAutoEndTime();
}

void CalendarEvent::setStartTime(const CustomDateTime &time)
{
    if (time.isValid()) {
        m_startTime = time;
        if (m_isAllDay) {
            calculateAutoEndTime();
        }
        update();
    }
}

void CalendarEvent::setEndTime(const CustomDateTime &time)
{
    if (time.isValid() && time < m_startTime) {
        qDebug() << "End time cannot be before start time";
        return;
    }
    m_endTime = time;
    m_isAllDay = false;
    update();
}

void CalendarEvent::calculateAutoEndTime()
{
    // Автоматически устанавливаем конец события через 1 час
    m_endTime = m_startTime;
    m_endTime.setTime((m_startTime.hour() + 1) % m_startTime.m_calendarSystem->hoursPerDay(),
                      m_startTime.minute(), m_startTime.second());
}

bool CalendarEvent::isValid() const
{
    return m_startTime.isValid() && m_endTime.isValid() && m_startTime < m_endTime;
}

quint32 CalendarEvent::durationInMinutes() const
{
    // Упрощенный расчет длительности (можно усложнить)
    quint32 totalMinutes = 0;
    if (m_startTime.day() == m_endTime.day() &&
        m_startTime.month() == m_endTime.month() &&
        m_startTime.year() == m_endTime.year()) {
        totalMinutes = (m_endTime.hour() - m_startTime.hour()) *
                           m_startTime.m_calendarSystem->minutesPerHour() +
                       (m_endTime.minute() - m_startTime.minute());
    }
    return totalMinutes;
}

void CalendarEvent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    setupPainter(painter);

    // Отображаем время и текст события
    QString displayText = QString("%1:%2 - %3")
                              .arg(m_startTime.hour(), 2, 10, QChar('0'))
                              .arg(m_startTime.minute(), 2, 10, QChar('0'))
                              .arg(m_text);

    painter->drawText(m_rect, Qt::AlignCenter, displayText);
}
