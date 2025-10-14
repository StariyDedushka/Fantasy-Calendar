#include "include/abstractitem.h"

AbstractItem::AbstractItem(const QRectF &rect,  QColor colorPrimary, QColor colorSecondary, QColor colorTertiary, bool enabled, QGraphicsItem *parent ) :
    QGraphicsItem(parent)
    , m_enabled(enabled)
    , colorPrimary(colorPrimary)
    , colorSecondary(colorSecondary)
    , colorTertiary(colorTertiary)
    , m_rect(rect)
{
    m_hovered = false;
    m_selected = false;
    m_selectedItem = nullptr;
    AbstractItem::setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}


AbstractItem::~AbstractItem()
{
    for(AbstractItem *item : items)
    {
        delete item;
    }
    items.clear();
}

QVector<AbstractItem*>& AbstractItem::getItems()
{
    return items;
}

QSharedPointer<QPolygon> AbstractItem::buildTriangle(const QRectF &parentRect, quint8 scale, qint16 rotation)
{
    QSharedPointer<QPolygon> triangle(new QPolygon);
    double modifier = scale / 100.0;
    quint8 width = 15, height = 15;
    QPoint center(parentRect.x() + width, parentRect.y() + parentRect.height() / 2);
    // qDebug() << "ParentPos x:" << parentRect.x() << "ParentPos y:" << parentRect.y();
    QPoint point1(center.x() - (width/2) * modifier, center.y() + (height/2) * modifier);
    QPoint point2(center.x() - (width/2) * modifier, center.y() - (height/2) * modifier);
    QPoint point3(center.x() + (width/2) * modifier, center.y());
    *triangle << point1 << point2 << point3;
    *triangle = QTransform().translate(center.x(), center.y()).rotate(rotation).translate(-center.x(), -center.y()).map(*triangle);
    return triangle;
}

QColor AbstractItem::colorDarken(QColor baseColor)
{
    int red = std::min(std::max(baseColor.red() - 20, 0), 255);
    int green = std::min(std::max(baseColor.green() - 20, 0), 255);
    int blue = std::min(std::max(baseColor.blue() - 20, 0), 255);
    QColor hoverColor(red, green, blue);
    return hoverColor;
}

QColor AbstractItem::colorLighten(QColor baseColor)
{
    double mod = 1.3;
    int red = std::max(static_cast<int>(baseColor.red() * mod), 255);
    int green = std::max(static_cast<int>(baseColor.green() * mod), 255);
    int blue = std::max(static_cast<int>(baseColor.blue() * mod), 255);
    QColor hoverColor(red, green, blue);
    return hoverColor;

}

void AbstractItem::slot_onItemClicked(AbstractItem *item)
{
    emit signal_itemClicked(item);
}

void AbstractItem::addItem(AbstractItem *item)
{
    items.append(item);
    connect(item, &AbstractItem::signal_itemClicked, this, &AbstractItem::slot_onItemClicked);
}

bool AbstractItem::isSelected()
{
    return m_selected;
}

void AbstractItem::toggleClicked()
{
    // Если кликнули по уже выделенному элементу - снимаем выделение
    if (m_selected) {
        qDebug() << "Deselecting current item";
        m_selected = false;
        setSelected(nullptr);
    }
    // Если кликнули по другому элементу
    else {
        // Снимаем выделение с предыдущего элемента
        if (m_selectedItem && m_selectedItem != this) {
            qDebug() << "Deselecting previous item";

            m_selectedItem->m_selected = false;
            setSelected(nullptr);
        }

        // Выделяем новый элемент
        qDebug() << "Selecting new item";
        m_selected = true;
        setSelected(this);
    }

}

void AbstractItem::setSelected(AbstractItem *item)
{
    m_selectedItem = item;
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

void AbstractItem::expand()
{
    m_expanded = true;
    qreal height = items.size() * 60 + 10;
    m_rect.setHeight(height);
    update();
}

void AbstractItem::collapse()
{
    m_expanded = false;
    qreal height = 50;
    m_rect.setHeight(height);
    update();
}

void AbstractItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(m_expandable)
    {
        if(m_selected) collapse();
        else expand();
    }

    if (!m_enabled) {
        qDebug() << "Item disabled, ignoring";
        event->ignore();
        return;
    }
    if(!items.empty()) {
        QPointF scenePos = event->scenePos();

        for (AbstractItem *child : items) {
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
    // Если дочерних элементов нет или событие не над ними - обрабатываем сами
    qDebug() << "Handling event in parent";
    toggleClicked();
    emit signal_itemClicked(this);
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
