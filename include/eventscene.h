#ifndef EVENTPAINTER_H
#define EVENTPAINTER_H

#include <QObject>
#include <include/abstractscene.h>
#include "eventcontainer.h"

class EventScene : public AbstractScene
{
    Q_OBJECT
public:
    EventScene();
    ~EventScene();
    virtual void initialize() override;
    bool addContainer(const QRectF &rect, QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen,
                      QColor colorTertiary = Qt::yellow, bool enabled = true, QObject *parent = nullptr);

public slots:
    virtual void /*slot_*/windowResized(quint16 wWidth, quint16 wHeight) override;
    virtual void /*slot_*/settingsChanged() override;
    virtual void /*slot_*/rebuild(QVector<AbstractItem*> *input = nullptr) override;


private:
    virtual void reposition() override;

};

#endif // EVENTPAINTER_H
