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

    QColor colorDarken(QColor baseColor);
    QColor colorLighten(QColor baseColor);

    bool m_enabled;
    bool m_selected;
    bool m_hovered;
    QVector<AbstractItem*> *items;
    QColor m_fillColor;
    QRectF m_rect;


private slots:
    virtual void slot_onItemClicked(AbstractItem *item);

public:
    AbstractItem();
    ~AbstractItem();
    AbstractItem(const QRectF &rect, QColor fillColor = Qt::gray, bool enabled = true, QGraphicsItem *parent = nullptr);


    virtual QRectF boundingRect() const override;
    virtual void setRect(quint16 posX, quint16 posY, quint16 sizeX, quint16 sizeY);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

    virtual bool isSelected();
    virtual bool isEnabled();

    virtual void setSelected(bool option);
    virtual void setEnabled(bool enabled);
    virtual void addItem(AbstractItem *item);
    virtual QVector<AbstractItem*> *getItems();
    virtual QPolygon* drawTriangle(quint16 x = 0, quint16 y = 0, quint8 scale = 100, quint16 rotation = 0);



};
#endif
