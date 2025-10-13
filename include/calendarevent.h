#ifndef CALENDAREVENT_H
#define CALENDAREVENT_H


#include <QObject>
#include "abstractitem.h"

class CalendarEvent : public AbstractItem
{
    Q_OBJECT
public:
    CalendarEvent();
    CalendarEvent(const QRectF &rect, QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen, QColor colorTertiary = Qt::yellow,
                 bool enabled = true, QGraphicsItem *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


private:
    quint16 m_time;
    QString m_text;

};

#endif // CALENDAREVENT_H
