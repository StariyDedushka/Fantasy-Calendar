#include "include/abstractitem.h"

AbstractItem::AbstractItem(const QRectF &rect,  bool enabled, QGraphicsItem *parent ) :
    QGraphicsItem(parent)
    , m_enabled(enabled)
    , m_rect(rect)
{
    m_hovered = false;
    m_selected = false;
    AbstractItem::setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}


AbstractItem::~AbstractItem()
{
}

bool AbstractItem::isSelected()
{
    return m_selected;
}

void AbstractItem::setSelected(bool option)
{
    m_selected = option;
    update();
}

bool AbstractItem::isEnabled()
{
    return m_enabled;
}

void AbstractItem::setEnabled(bool option)
{
    m_enabled = option;
    update();
}

void AbstractItem::setRect(quint16 posX, quint16 posY, quint16 sizeX, quint16 sizeY)
{
    QPoint point(posX, posY);
    m_rect.setWidth(sizeX);
    m_rect.setHeight(sizeY);
    m_rect.setTopLeft(point);
}


void AbstractItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Item clicked!";
    emit signal_itemClicked(this);


    event->accept();
}

void AbstractItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_hovered = true;
    update();
    event->accept();
}

void AbstractItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_hovered = false;
    update();
    event->accept();
}


QRectF AbstractItem::boundingRect() const
{
    return m_rect;
}
