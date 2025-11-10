#include "include/calendaritem.h"

CalendarItem::CalendarItem(const QRectF &rect, const QString &text,
                           const QColor &colorPrimary, const QColor &colorSecondary,
                           const QColor &colorTertiary, bool enabled,
                           CustomDateTime dateTime, QObject *parent)
    : AbstractItem(rect, text, colorPrimary, colorSecondary, colorTertiary, enabled, parent)
    , m_dateTime(dateTime)
    , m_hasEvents(false)
    , m_isToday(false)
{

}

void CalendarItem::paint(QPainter *painter,
                         const QStyleOptionGraphicsItem *option,
                         QWidget *widget)
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
    } else if (m_isToday) {
        backgroundBrush = QColor(255, 255, 200); // Светло-желтый для сегодня
    } else if (m_hasEvents) {
        backgroundBrush = QColor(255, 230, 200); // Светло-оранжевый для дней с событиями
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

        if (m_isToday) {
            font.setBold(true);
            painter->setPen(Qt::red);
        }

        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter, m_text);
    }

    // Индикатор событий
    if (m_hasEvents && m_enabled) {
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

void CalendarItem::setHasEvents(bool hasEvents)
{
    if (m_hasEvents != hasEvents) {
        m_hasEvents = hasEvents;
        update();
    }
}

void CalendarItem::setToday(bool today)
{
    if (m_isToday != today) {
        m_isToday = today;
        update();
    }
}

void CalendarItem::updateAppearance()
{
    update();
}
