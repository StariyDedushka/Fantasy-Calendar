#ifndef CALENDARITEM_H
#define CALENDARITEM_H

#include <QDate>
#include <QWidget>
#include <QRectF>
#include <QGraphicsItem>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QtDebug>
#include "include/calendarevent.h"

class CalendarItem : public QObject, public QGraphicsItem
{
    Q_INTERFACES(QGraphicsItem)
    Q_OBJECT
private:
    quint16 m_day;
    quint16 m_month;
    quint32 m_year;
    bool m_enabled;
    bool m_selected;
    bool m_hovered;
    QRectF m_rect;


signals:
    void signal_itemClicked(CalendarItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

public:
    CalendarItem();
    ~CalendarItem();
    CalendarItem(const QRectF &rect, quint16 day = 1, quint16 month = 1, quint32 year = 2000, bool enabled = true, QGraphicsItem *parent = nullptr);

    quint16 day() const;
    quint16 month() const;
    quint32 year() const;
    QVector<CalendarEvent*> *events;

    bool isEnabled();
    virtual QRectF boundingRect() const override;
    void setRect(quint16 posX, quint16 posY, quint16 sizeX, quint16 sizeY);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setSelected(bool option);
    bool isSelected();

    void setDay(quint16 day);
    void setMonth(quint16 month);
    void setYear(quint32 year);

    void setEnabled(bool enabled);
};

#endif
