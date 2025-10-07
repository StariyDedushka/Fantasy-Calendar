#ifndef CalendarPainter_H
#define CalendarPainter_H


#include "abstractpainter.h"
#include "calendaritem.h"

class CalendarPainter : public AbstractPainter
{
    Q_OBJECT
public:
    CalendarPainter();
    ~CalendarPainter();
    virtual void initialize() override;

signals:
    void signal_rebuild(CalendarPainter *scene);
public slots:
    virtual void slot_windowResized(quint16 wWidth, quint16 wHeight) override;
    virtual void slot_onItemClicked() override;
    virtual void slot_settingsChanged() override;

protected:
    virtual void addItem(AbstractItem *item);
    virtual void reposition();
    virtual void rebuild();

private:
    quint16 m_daysPerWeek;
    quint16 m_daysPerMonth;
    quint16 m_daysPerYear;

};

#endif // CalendarPainter_H
