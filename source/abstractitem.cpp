#include "include/abstractitem.h"

AbstractItem::AbstractItem(const QRectF &rect,  QColor fillColor, bool enabled, QGraphicsItem *parent ) :
    QGraphicsItem(parent)
    , m_enabled(enabled)
    , m_fillColor(fillColor)
    , m_rect(rect)
{
    m_hovered = false;
    m_selected = false;
    items = new QVector<AbstractItem*>();
    AbstractItem::setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}


AbstractItem::~AbstractItem()
{
    delete items;
}

QVector<AbstractItem*> *AbstractItem::getItems()
{
    return items;
}

QPolygon* AbstractItem::drawTriangle(quint16 x, quint16 y, quint8 scale, quint16 rotation)
{
    QPolygon *triangle = new QPolygon();
    double modifier = scale / 100;
    QPoint point1(x, y + 22 * static_cast<int>(modifier) );
    QPoint point2((x - 15) * static_cast<int>(modifier), y * static_cast<int>(modifier) );
    QPoint point3((x + 15) * static_cast<int>(modifier), y * static_cast<int>(modifier) );
    *triangle << point1 << point2 << point3;
    return triangle;
}

QColor AbstractItem::colorDarken(QColor baseColor)
{
    int red = std::min(std::max(baseColor.red() - 40, 0), 255);
    int green = std::min(std::max(baseColor.green() - 40, 0), 255);
    int blue = std::min(std::max(baseColor.blue() - 40, 0), 255);
    QColor hoverColor(red, green, blue);
    return hoverColor;
}

QColor AbstractItem::colorLighten(QColor baseColor)
{
    int red = (baseColor.red() + 60) % 255;
    int green = (baseColor.green() + 60) % 255;
    int blue = (baseColor.blue() + 60) % 255;
    QColor hoverColor(red, green, blue);
    return hoverColor;

}

void AbstractItem::slot_onItemClicked(AbstractItem *item)
{
    emit signal_itemClicked(item);
}

void AbstractItem::addItem(AbstractItem *item)
{
    items->append(item);
    connect(item, &AbstractItem::signal_itemClicked, this, &AbstractItem::slot_onItemClicked);
}

bool AbstractItem::isSelected()
{
    return m_selected;
}

void AbstractItem::setSelected(bool option)
{
    m_selected = option;
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


    if (!m_enabled) {
        qDebug() << "Item disabled, ignoring";
        event->ignore();
        return;
    }
    if (items)
    {
        if(!items->empty()) {
            QPointF scenePos = event->scenePos();

            for (AbstractItem *child : *items) {
                if (child->isEnabled() && child->isVisible()) {
                    // Преобразуем позицию в координаты дочернего элемента
                    QPointF childPos = child->mapFromScene(scenePos);
                    if (child->contains(childPos)) {
                        qDebug() << "Event should go to child:" << static_cast<void*>(child);
                        event->ignore(); // Позволяем событию пройти к дочернему элементу
                        return;
                    }
                }
            }
        }
    }
    // Если дочерних элементов нет или событие не над ними - обрабатываем сами
    qDebug() << "Handling event in parent";
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
