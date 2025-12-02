#include "include/eventitem.h"

EventItem::EventItem(CustomDateTime startTime, CustomDateTime endTime,
                             const QRectF &rect, QString text, QColor colorPrimary,
                             QColor colorSecondary, QColor colorTertiary,
                             bool enabled, QObject *parent)
    : AbstractItem(rect, text, colorPrimary, colorSecondary, colorTertiary, enabled, parent)
    , m_startTime(startTime)
    , m_endTime(endTime)
    , m_isAllDay(false)
{
}

EventItem::EventItem(CustomDateTime startTime, const QRectF &rect, QString text,
                             QColor colorPrimary, QColor colorSecondary, QColor colorTertiary,
                             bool enabled, QObject *parent)
    : AbstractItem(rect, text, colorPrimary, colorSecondary, colorTertiary, enabled, parent)
    , m_startTime(startTime)
    , m_isAllDay(true)
{
    calculateAutoEndTime();
}

void EventItem::setStartTime(const CustomDateTime &time)
{
    if (time.isValid()) {
        m_startTime = time;
        if (m_isAllDay) {
            calculateAutoEndTime();
        }
        update();
    }
}

void EventItem::setEndTime(const CustomDateTime &time)
{
    if (time.isValid() && time < m_startTime) {
        qDebug() << "End time cannot be before start time";
        return;
    }
    m_endTime = time;
    m_isAllDay = false;
    update();
}

void EventItem::calculateAutoEndTime()
{
    // Автоматически устанавливаем конец события через 1 час
    m_endTime = m_startTime;
    // m_endTime.setTime((m_startTime.hour() + 1) % m_startTime.m_calendarSystem->hoursPerDay(),
    //                   m_startTime.minute(), m_startTime.second());
}

bool EventItem::isValid() const
{
    return m_startTime.isValid() && m_endTime.isValid() && m_startTime < m_endTime;
}

quint32 EventItem::durationInMinutes() const
{
    // Упрощенный расчет длительности (можно усложнить)
    quint32 totalMinutes = 0;
    if (m_startTime.day() == m_endTime.day() &&
        m_startTime.month() == m_endTime.month() &&
        m_startTime.year() == m_endTime.year()) {
        // totalMinutes = (m_endTime.hour() - m_startTime.hour()) *
        //                    m_startTime.m_calendarSystem->minutesPerHour() +
        //                (m_endTime.minute() - m_startTime.minute());
    }
    return totalMinutes;
}

void EventItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    // Настройка painter'а
    painter->setRenderHint(QPainter::Antialiasing);

    // Фон
    QRectF rect = boundingRect();
    QBrush backgroundBrush = m_colorPrimary;

    // Изменение цвета в зависимости от состояния
    if (!m_enabled) {
        backgroundBrush = Qt::lightGray;
    } else if (m_selected) {
        backgroundBrush = m_colorSecondary;
    } else if (m_hovered) {
        backgroundBrush = m_colorSecondary.darker(120);
    }

    // Рисуем фон
    painter->setBrush(backgroundBrush);
    painter->setPen(QPen(m_colorTertiary, 1));
    painter->drawRoundedRect(rect, 4, 4);

    // Рисуем текст
    if (!m_text.isEmpty()) {
        painter->setPen(m_enabled ? Qt::black : Qt::darkGray);
        QFont font = painter->font();
        font.setPointSize(10);

        // Отображаем время и текст события
        QString displayText = QString("%1:%2 - %3")
                                  .arg(m_startTime.hour(), 2, 10, QChar('0'))
                                  .arg(m_startTime.minute(), 2, 10, QChar('0'))
                                  .arg(m_text);

        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter, displayText);
    }

    // Индикатор событий
    if (m_enabled) {
        painter->setBrush(Qt::red);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(rect.topRight() - QPointF(8, -4), 3, 3);
    }

    // Выделение
    if (m_highlighted) {
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(Qt::blue, 2));
        painter->drawRoundedRect(rect.adjusted(1, 1, -1, -1), 4, 4);
    }

}
