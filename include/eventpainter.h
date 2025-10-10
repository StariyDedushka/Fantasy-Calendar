#ifndef EVENTPAINTER_H
#define EVENTPAINTER_H

#include <QObject>
#include <include/abstractpainter.h>
#include "eventcontainer.h"

class EventPainter : public AbstractPainter
{
    Q_OBJECT
public:
    EventPainter();
    ~EventPainter();
    virtual void initialize() override;

signals:
    virtual void signal_rebuild(AbstractPainter *scene) override;
public slots:
    virtual void slot_windowResized(quint16 wWidth, quint16 wHeight) override;
    virtual void slot_onItemClicked(AbstractItem *clickedItem) override;
    virtual void slot_settingsChanged() override;
    virtual void slot_rebuild(QVector<AbstractItem*> *input = nullptr) override;


private:
    virtual void reposition() override;

};

#endif // EVENTPAINTER_H
