#ifndef CalendarPainter_H
#define CalendarPainter_H


#include "abstractscene.h"
#include "calendaritem.h"
#include "common/calendarStructures.h"

class CalendarScene : public AbstractScene
{
    // Q_INTERFACES(AbstractScene)
    Q_OBJECT
public:
    CalendarScene(CalendarSystem *system);
    ~CalendarScene();
    virtual void initialize() override;

signals:
    void signal_rebuild(AbstractScene *scene);
public slots:
    virtual void /*slot_*/windowResized(quint16 wWidth, quint16 wHeight) override;
    virtual void /*slot_*/settingsChanged() override;
    virtual void /*slot_*/rebuild(QVector<AbstractItem*> *input = nullptr) override;


private:
    virtual void reposition() override;
    QVector<Month*> *m_months;

};

#endif // CalendarPainter_H
