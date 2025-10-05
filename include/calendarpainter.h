#ifndef CALENDARPAINTER_H
#define CALENDARPAINTER_H

#include <QObject>
#include <QGraphicsScene>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include "calendaritem.h"

class CalendarPainter : public QGraphicsScene
{
    Q_OBJECT
public:
    CalendarPainter();
    void initialize();

signals:
    void signal_rebuild(CalendarPainter *scene);
public slots:
    void slot_callRebuild();
    void slot_settingsChanged(quint16 daysPerWeek, quint16 daysPerMonth, quint16 daysPerYear);
    void slot_windowChanged(quint32 wWidth, quint32 wHeight);
    void slot_onItemClicked();
private:
    virtual void addItem(CalendarItem *item);

    void rebuild();
    QVector<CalendarItem*> activeItems;
    quint16 m_daysPerWeek;
    quint16 m_daysPerMonth;
    quint16 m_daysPerYear;

    quint16 m_rectSizeX;
    quint16 m_rectSizeY;

    quint32 m_wWidth;
    quint32 m_wHeight;
};

#endif // CALENDARPAINTER_H
