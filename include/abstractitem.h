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
#include "customdatetime.h"
#include <QStyleOption>

class AbstractItem : public QObject, public QGraphicsItem
{
    Q_INTERFACES(QGraphicsItem)
    Q_OBJECT

signals:
    void itemClicked(AbstractItem *item);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    bool m_enabled;
    bool m_expanded;
    bool m_expandable;
    // Визуальные состояния
    bool m_highlighted;
    bool m_hovered;

    quint16 m_groupId;
    QString m_text;
    QVector<quint32> m_item_ids;

    QColor m_colorPrimary;
    QColor m_colorSecondary;
    QColor m_colorTertiary;

    // QVector<AbstractItem*> m_items;
    QRectF m_rect;

    // static inline AbstractItem *m_selectedItem = nullptr;

    // virtual void setupPainter(QPainter *painter);

    void setText(const QString &text);
    QString text() const { return m_text; }


private slots:
    virtual void /*slot_*/onItemClicked(AbstractItem *item);

public:
    virtual ~AbstractItem();
    AbstractItem(const QRectF &rect,
                 const QString &text = "",
                 const QColor &colorPrimary = Qt::white,
                 const QColor &colorSecondary = Qt::gray,
                 const QColor &colorTertiary = Qt::darkGray,
                 bool enabled = true,
                 QObject *parent = nullptr);


    virtual QRectF boundingRect() const override;
    virtual void setRect(quint16 posX, quint16 posY, quint16 sizeX, quint16 sizeY);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

    virtual bool isSelected() const;
    virtual bool isEnabled() const;

    // static void setSelectedItem(AbstractItem *item);
    virtual void setHighlighted(bool highlighted);
    virtual void setEnabled(bool enabled);
    // virtual void addItem(AbstractItem *item);
    // virtual QVector<AbstractItem*>& getItems();
    // virtual QSharedPointer<QPolygon> buildTriangle(const QRectF &parentRect, double scale, qint16 rotation);

    virtual void collapse();
    virtual void expand();

    AbstractItem* operator=(AbstractItem&& other);
    bool operator==(const AbstractItem& other);

};
#endif
