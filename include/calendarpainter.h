#ifndef CalendarPainter_H
#define CalendarPainter_H


#include "abstractpainter.h"
#include "calendaritem.h"

class CalendarPainter : public AbstractPainter
{
    // Q_INTERFACES(AbstractPainter)
    Q_OBJECT
public:
    CalendarPainter();
    ~CalendarPainter();
    virtual void initialize() override;

signals:
    virtual void signal_rebuild(AbstractPainter *scene) override;
public slots:
    virtual void slot_windowResized(quint16 wWidth, quint16 wHeight) override;
    virtual void slot_settingsChanged() override;
    virtual void slot_rebuild(QVector<AbstractItem*> *input = nullptr) override;


private:
    quint16 m_daysPerWeek;
    quint16 m_daysPerMonth;
    quint16 m_daysPerYear;

    virtual void reposition() override;

};

#endif // CalendarPainter_H
