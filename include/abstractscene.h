#ifndef ABSTRACTPAINTER_H
#define ABSTRACTPAINTER_H

#include <QObject>
#include <QGraphicsScene>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include "abstractitem.h"
#include "calendarsystem.h"
#include "customdatetime.h"

struct itemPalette {
    quint16 itemGroup;
    QColor colorPrimary;
    QColor colorSecondary;
    QColor colorTertiary;
};

class AbstractScene : public QGraphicsScene
{
    Q_OBJECT
public:
    AbstractScene() = default;
    ~AbstractScene();
    virtual void initialize() = 0;

public slots:
    virtual void /*slot_*/rebuild(QVector<AbstractItem*> *input = nullptr) = 0;
    virtual void /*slot_*/settingsChanged() = 0;
    virtual void /*slot_*/windowResized(quint16 wWidth, quint16 wHeight) = 0;
    virtual void /*slot_*/onItemClicked();

protected:
    virtual bool addItem(AbstractItem *item);
    virtual void reposition() = 0;

    quint16 m_rectSizeX;
    quint16 m_rectSizeY;

    quint16 m_wWidth;
    quint16 m_wHeight;

    QVector<itemPalette*> palette;

    QVector<AbstractItem*> m_items;

};

#endif // ABSTRACTPAINTER_H
