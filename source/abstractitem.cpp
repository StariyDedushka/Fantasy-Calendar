#include "include/abstractitem.h"

AbstractItem::AbstractItem(const QRectF &rect,
                           const QString &text,
                           const QColor &colorPrimary,
                           const QColor &colorSecondary,
                           const QColor &colorTertiary,
                           bool enabled,
                           QObject *parent) :
    QObject(parent)
    , m_enabled(enabled)
    , m_colorPrimary(colorPrimary)
    , m_colorSecondary(colorSecondary)
    , m_colorTertiary(colorTertiary)
    , m_rect(rect)
    , m_highlighted(false)
    , m_text(text)
    , m_selected(false)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}


void AbstractItem::setHighlighted(bool highlighted)
{
    if (m_highlighted != highlighted) {
        m_highlighted = highlighted;
        update();
    }
}

// QVector<AbstractItem*>& AbstractItem::getItems()
// {
//     return m_items;
// }

// void AbstractItem::setupPainter(QPainter *painter)
// {

//     QBrush brush(m_colorPrimary);
//     QBrush brushHover(m_colorPrimary.darker(120));


//     QPen pen(m_colorPrimary.darker(150));
//     QPen hoverPen(m_colorPrimary.lighter(150));


//     if(m_hovered || m_selected) {
//         painter->setBrush(brushHover);
//         painter->setPen(hoverPen);
//         painter->drawRect(m_rect);
//     } else {
//         painter->setBrush(brush);
//         painter->setPen(pen);
//         painter->drawRect(m_rect);
//     }
// }

// QSharedPointer<QPolygon> AbstractItem::buildTriangle(const QRectF &parentRect, double scale, qint16 rotation)
// {
//     QSharedPointer<QPolygon> triangle(new QPolygon);
//     double modifier = scale / 100.0;
//     quint8 width = 15, height = 15;
//     QPoint center(parentRect.x() + width, parentRect.y() + parentRect.height() / 2);
//     // qDebug() << "ParentPos x:" << parentRect.x() << "ParentPos y:" << parentRect.y();
//     QPoint point1(center.x() - (width/2) * modifier, center.y() + (height/2) * modifier);
//     QPoint point2(center.x() - (width/2) * modifier, center.y() - (height/2) * modifier);
//     QPoint point3(center.x() + (width/2) * modifier, center.y());
//     *triangle << point1 << point2 << point3;
//     *triangle = QTransform().translate(center.x(), center.y()).rotate(rotation).translate(-center.x(), -center.y()).map(*triangle);
//     return triangle;
// }


void AbstractItem::/*slot_*/onItemClicked(AbstractItem *item)
{
    emit itemClicked(item);
}

// void AbstractItem::addItem(AbstractItem *item)
// {
//     m_items.append(item);
//     connect(item, &AbstractItem::itemClicked, this, &AbstractItem::/*slot_*/onItemClicked);
// }


void AbstractItem::setEnabled(bool option)
{
    m_enabled = option;
}

void AbstractItem::setSelected(bool selected)
{
    m_selected = selected;
}

bool AbstractItem::isSelected() const
{
    return m_selected;
}

bool AbstractItem::isEnabled() const
{
    return m_enabled;
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

    emit itemClicked(this);
    event->accept();
    update();
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

void AbstractItem::setSelectedItem(AbstractItem *item)
{
    m_selectedItem = item;
}


AbstractItem* AbstractItem::operator=(AbstractItem&& other)
{
    m_enabled = std::move(other.m_enabled);
    m_selected = std::move(other.m_selected);
    m_hovered = std::move(other.m_hovered);
    m_expanded = std::move(other.m_expanded);
    m_expandable = std::move(other.m_expandable);
    m_groupId = std::move(other.m_groupId);
    m_text = std::move(other.m_text);

    m_colorPrimary = std::move(other.m_colorPrimary);
    m_colorSecondary = std::move(other.m_colorSecondary);
    m_colorTertiary = std::move(other.m_colorTertiary);

    m_rect = std::move(other.m_rect);
    return this;
}


bool AbstractItem::operator==(const AbstractItem& other)
{
    return m_enabled == other.m_enabled
           && m_selected == other.m_selected
           && m_expandable == other.m_expandable
           && m_groupId == other.m_groupId
           && m_text == other.m_text
           && m_colorPrimary == other.m_colorPrimary
           && m_colorSecondary == other.m_colorSecondary
           && m_colorTertiary == other.m_colorTertiary
           && m_rect == other.m_rect;
}
