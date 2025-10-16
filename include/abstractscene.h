#ifndef ABSTRACTPAINTER_H
#define ABSTRACTPAINTER_H

#include <QObject>
#include <QGraphicsScene>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include "include/abstractitem.h"

class AbstractScene : public QGraphicsScene
{
    Q_OBJECT
public:
    AbstractScene();
    ~AbstractScene();
    virtual void initialize() = 0;

signals:
    virtual void signal_rebuild(AbstractScene *scene);

public slots:
    virtual void slot_rebuild(QVector<AbstractItem*> *input = nullptr) = 0;
    virtual void slot_settingsChanged() = 0;
    virtual void slot_windowResized(quint16 wWidth, quint16 wHeight) = 0;
    virtual void slot_onItemClicked();

protected:
    virtual void addItem(AbstractItem *item);
    virtual void reposition() = 0;

    quint16 m_rectSizeX;
    quint16 m_rectSizeY;

    quint16 m_wWidth;
    quint16 m_wHeight;

    QColor m_colorPrimary;
    QColor m_colorSecondary;
    QColor m_colorTertiary;

    QVector<AbstractItem*> items;

};

#endif // ABSTRACTPAINTER_H
