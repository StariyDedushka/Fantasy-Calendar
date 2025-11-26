#ifndef EVENTITEM_H
#define EVENTITEM_H


#include <QObject>
#include "abstractitem.h"
#include "customdatetime.h"

class EventItem : public AbstractItem
{
    Q_OBJECT
public:
    EventItem();
    EventItem(CustomDateTime startTime, CustomDateTime endTime,
              const QRectF &rect, QString text, QColor colorPrimary = Qt::green,
              QColor colorSecondary = Qt::darkGreen, QColor colorTertiary = Qt::yellow,
              bool enabled = true, QObject *parent = nullptr);

    EventItem(CustomDateTime startTime, const QRectF &rect, QString text,
              QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen,
              QColor colorTertiary = Qt::yellow, bool enabled = true, QObject *parent = nullptr);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    CustomDateTime startTime() const { return m_startTime; }
    CustomDateTime endTime() const { return m_endTime; }
    quint32 durationInMinutes() const;


    // Сеттеры
    void setStartTime(const CustomDateTime &time);
    void setEndTime(const CustomDateTime &time);

    // Валидация
    bool isValid() const;
    bool isAllDay() const;

private:
    quint16 m_time;
    CustomDateTime m_startTime;
    CustomDateTime m_endTime;
    bool m_isAllDay;

    void calculateAutoEndTime();
};

#endif // EVENTITEM_H
