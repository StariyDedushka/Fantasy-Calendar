#ifndef AbstractItem_H
#define AbstractItem_H

#include <QDate>
#include <QWidget>
#include <QRectF>
#include <QVector>
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
    bool m_expanded;
    bool m_expandable;
    QVector<AbstractItem*> items;
    QRectF m_rect;

    QColor colorPrimary;
    QColor colorSecondary;
    QColor colorTertiary;

    static inline AbstractItem *m_selectedItem = nullptr;

    virtual void toggleClicked();


private slots:
    virtual void slot_onItemClicked(AbstractItem *item);

public:
    AbstractItem();
    virtual ~AbstractItem();
    AbstractItem(const QRectF &rect, QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen, QColor colorTertiary = Qt::yellow,
                 bool enabled = true, QGraphicsItem *parent = nullptr);


    virtual QRectF boundingRect() const override;
    virtual void setRect(quint16 posX, quint16 posY, quint16 sizeX, quint16 sizeY);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

    virtual bool isSelected();
    virtual bool isEnabled();

    static void setSelected(AbstractItem *item);
    virtual void setEnabled(bool enabled);
    virtual void addItem(AbstractItem *item);
    virtual QVector<AbstractItem*>& getItems();
    virtual QSharedPointer<QPolygon> buildTriangle(const QRectF &parentRect, quint8 scale, qint16 rotation);

    virtual void collapse();
    virtual void expand();


};
#endif
