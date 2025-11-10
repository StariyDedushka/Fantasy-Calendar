#ifndef CALENDAREVENT_H
#define CALENDAREVENT_H


#include <QObject>
#include "abstractitem.h"
#include "customdatetime.h"

class CalendarEvent : public AbstractItem
{
    Q_OBJECT
public:
    CalendarEvent();
    CalendarEvent(CustomDateTime startTime, CustomDateTime endTime,
                  const QRectF &rect, QString text, QColor colorPrimary = Qt::green,
                  QColor colorSecondary = Qt::darkGreen, QColor colorTertiary = Qt::yellow,
                  bool enabled = true, QObject *parent = nullptr);

    CalendarEvent(CustomDateTime startTime, const QRectF &rect, QString text,
                  QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen, QColor colorTertiary = Qt::yellow,
                  bool enabled = true, QObject *parent = nullptr);

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

#endif // CALENDAREVENT_H
