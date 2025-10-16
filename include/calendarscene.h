#ifndef CalendarPainter_H
#define CalendarPainter_H


#include "abstractscene.h"
#include "calendaritem.h"

class CalendarScene : public AbstractScene
{
    // Q_INTERFACES(AbstractScene)
    Q_OBJECT
public:
    CalendarScene();
    ~CalendarScene();
    virtual void initialize() override;

signals:
    virtual void signal_rebuild(AbstractScene *scene) override;
public slots:
    virtual void slot_windowResized(quint16 wWidth, quint16 wHeight) override;
    virtual void slot_settingsChanged() override;
    virtual void slot_rebuild(QVector<AbstractItem*> *input = nullptr) override;


private:
    virtual void reposition() override;
    quint16 m_daysPerWeek;
    quint16 m_daysPerMonth;

};

#endif // CalendarPainter_H
