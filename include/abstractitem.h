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

    bool m_enabled;
    bool m_selected;
    bool m_hovered;
    bool m_expanded;
    bool m_expandable;
    quint16 m_groupId;
    QString m_text;
    QObject *m_parentScene = nullptr;

    QColor m_colorPrimary;
    QColor m_colorSecondary;
    QColor m_colorTertiary;

    QVector<AbstractItem*> m_items;
    QRectF m_rect;

    static inline AbstractItem *m_selectedItem = nullptr;

    virtual void toggleClicked();
    virtual void setupPainter(QPainter *painter);

    void setText(const QString &text);
    QString text() const { return m_text; }


private slots:
    virtual void /*slot_*/onItemClicked(AbstractItem *item);

public:
    virtual ~AbstractItem();
    AbstractItem(const QRectF &rect, QString text = "", QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen,
                 QColor colorTertiary = Qt::yellow, bool enabled = true, QObject *parent = nullptr);


    virtual QRectF boundingRect() const override;
    virtual void setRect(quint16 posX, quint16 posY, quint16 sizeX, quint16 sizeY);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override = 0;

    virtual bool isSelected() const;
    virtual bool isEnabled() const;

    static void setSelected(AbstractItem *item);
    virtual void setEnabled(bool enabled);
    virtual void addItem(AbstractItem *item);
    virtual QVector<AbstractItem*>& getItems();
    virtual QSharedPointer<QPolygon> buildTriangle(const QRectF &parentRect, double scale, qint16 rotation);

    virtual void collapse();
    virtual void expand();

    AbstractItem& operator=(AbstractItem&& other);
    bool operator==(const AbstractItem& other);

};
#endif
