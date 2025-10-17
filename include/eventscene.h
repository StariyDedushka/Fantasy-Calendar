#ifndef EVENTPAINTER_H
#define EVENTPAINTER_H

#include <QObject>
#include <include/abstractscene.h>
#include "eventcontainer.h"

class EventScene : public AbstractScene
{
    Q_OBJECT
public:
    EventScene(CalendarSystem *system);
    ~EventScene();
    virtual void initialize() override;
    // virtual void addEvent();
    bool addContainer(const QRectF &rect, QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen,
                      QColor colorTertiary = Qt::yellow, bool enabled = true, QObject *parent = nullptr);

signals:
    void signal_rebuild(AbstractScene *scene);
public slots:
    virtual void slot_windowResized(quint16 wWidth, quint16 wHeight) override;
    virtual void slot_settingsChanged() override;
    virtual void slot_rebuild(QVector<AbstractItem*> *input = nullptr) override;


private:
    virtual void reposition() override;

};

#endif // EVENTPAINTER_H
