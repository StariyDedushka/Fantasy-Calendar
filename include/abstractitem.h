#ifndef AbstractItem_H
#define AbstractItem_H

#include <QDate>
#include <QWidget>
#include <QRectF>
#include <QGraphicsItem>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QtDebug>

class AbstractItem : public QObject, public QGraphicsItem
{
    Q_INTERFACES(QGraphicsItem)
    Q_OBJECT

signals:
    void signal_itemClicked(AbstractItem *item);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    bool m_enabled;
    bool m_selected;
    bool m_hovered;
    QVector<AbstractItem*> *items;
    QColor m_fillColor;
    QRectF m_rect;

public:
    AbstractItem();
    ~AbstractItem();
    AbstractItem(const QRectF &rect, QColor fillColor, bool enabled = true, QGraphicsItem *parent = nullptr);


    virtual QRectF boundingRect() const override;
    virtual void setRect(quint16 posX, quint16 posY, quint16 sizeX, quint16 sizeY);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

    virtual bool isSelected();
    virtual bool isEnabled();

    virtual void setSelected(bool option);
    virtual void setEnabled(bool enabled);
    virtual void addItem(AbstractItem *item);



};
#endif
