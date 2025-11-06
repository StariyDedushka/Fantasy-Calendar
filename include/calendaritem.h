#ifndef CALENDARITEM_H
#define CALENDARITEM_H

#include "include/abstractitem.h"

class CalendarItem : public AbstractItem
{
    Q_OBJECT

private:
    quint16 m_day;
    quint16 m_month;
    quint32 m_year;


public:
    CalendarItem(const QRectF &rect, QString text = "", QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen, QColor colorTertiary = Qt::yellow,
                 bool enabled = true, quint16 day = 1, quint16 month = 1, quint32 year = 2000, QObject *parent = nullptr);

    quint16 day() const;
    quint16 month() const;
    quint32 year() const;

    void setDay(quint16 day);
    void setMonth(quint16 month);
    void setYear(quint32 year);


    // virtual void addItem(AbstractItem &item) override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    bool operator==(const CalendarItem& other);
    CalendarItem& operator=(CalendarItem&& other);
    bool operator<(const CalendarItem& other);
    bool operator>(const CalendarItem& other);

};


#endif // CALENDARITEM_H
