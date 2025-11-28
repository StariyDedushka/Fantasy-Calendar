#ifndef CALENDARITEM_H
#define CALENDARITEM_H

#include "abstractitem.h"

class CalendarItem : public AbstractItem
{
    Q_OBJECT

public:
    CalendarItem(const QRectF &rect,
                 const QString &text = "",
                 const QColor &colorPrimary = Qt::white,
                 const QColor &colorSecondary = Qt::gray,
                 const QColor &colorTertiary = Qt::darkGray,
                 bool enabled = true,
                 CustomDateTime dateTime = CustomDateTime(1, 1, 2000),
                 QObject *parent = nullptr);

    // Только данные для отображения (read-only)
    quint16 day() const { return m_dateTime.day(); }
    quint16 month() const { return m_dateTime.month(); }
    quint32 year() const { return m_dateTime.year(); }

    // Визуальные состояния
    void setHighlighted(bool highlighted);
    void setHasEvents(bool hasEvents);
    void setToday(bool today);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget) override;

    // Ограниченная функциональность
    void updateAppearance();

private:
    // Immutable данные дня
    const CustomDateTime m_dateTime;

    // Визуальные состояния
    bool m_highlighted;
    bool m_hasEvents;
    bool m_isToday;
};

#endif // CALENDARITEM_H
