#ifndef ABSTRACTPAINTER_H
#define ABSTRACTPAINTER_H

#include <QObject>
#include <QGraphicsScene>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include "include/abstractitem.h"

class AbstractPainter : public QGraphicsScene
{
    Q_OBJECT
public:
    AbstractPainter(QColor itemColor = Qt::gray);
    ~AbstractPainter();
    virtual void initialize() = 0;

signals:
    virtual void signal_rebuild(AbstractPainter *scene);

public slots:
    virtual void slot_rebuild(QVector<AbstractItem*> *input = nullptr) = 0;
    virtual void slot_settingsChanged() = 0;
    virtual void slot_windowResized(quint16 wWidth, quint16 wHeight) = 0;
    virtual void slot_onItemClicked(AbstractItem *clickedItem) = 0;

protected:
    virtual void addItem(AbstractItem *item);
    virtual void reposition() = 0;

    quint16 m_rectSizeX;
    quint16 m_rectSizeY;

    quint16 m_wWidth;
    quint16 m_wHeight;
    QColor m_itemColor;

    QVector<AbstractItem*> items;
    AbstractItem *m_previousClickedItem;
    virtual void toggleClicked(AbstractItem *clickedItem);

};

#endif // ABSTRACTPAINTER_H
