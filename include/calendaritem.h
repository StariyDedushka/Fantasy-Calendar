#ifndef CALENDARITEM_H
#define CALENDARITEM_H

#include <QDate>
#include <QWidget>
#include <QRectF>
#include <QGraphicsItem>
#include <QPainter>
#include <QtDebug>
#include "structs.h"

class CalendarItem : public QGraphicsItem
{
private:
    // QWidget *m_parent;
    // QRectF m_rect;
    QDate m_date;
    // cellPos m_pos;
    bool m_enabled;
    QRectF m_rect;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public:
    CalendarItem();
    CalendarItem(const QRectF &rect, QDate date = QDate(1, 3, 2003), bool enabled = true, QGraphicsItem *parent = nullptr);
    // QWidget* getParent();
    QDate getDate();
    // cellPos getPos();
    bool isEnabled();
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // void setParent(QWidget* parent);
    void setDate(QDate date);
    // void setPos(qreal x1, qreal y1, qreal x2, qreal y2);
    void setEnabled(bool enabled);
};

#endif
