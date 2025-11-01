#include "include/abstractitem.h"

AbstractItem::AbstractItem(const QRectF &rect, QString text,  QColor colorPrimary, QColor colorSecondary, QColor colorTertiary,
                           bool enabled, QObject *parent) :
    QGraphicsItem()
    , m_enabled(enabled)
    , m_colorPrimary(colorPrimary)
    , m_colorSecondary(colorSecondary)
    , m_colorTertiary(colorTertiary)
    , m_rect(rect)
    , m_text(text)
    , m_parentScene(parent)
{
    // if(parent->metaObject()->className() == "AbstractScene")
    // {
    //     m_parentScene = parent;
    // }
    m_hovered = false;
    m_selected = false;
    m_selectedItem = nullptr;
    AbstractItem::setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}


AbstractItem::~AbstractItem()
{
    for(AbstractItem *item : m_items)
    {
        delete item;
    }
    m_items.clear();
}

QVector<AbstractItem*>& AbstractItem::getItems()
{
    return m_items;
}

void AbstractItem::setupPainter(QPainter *painter)
{

    QBrush brush(m_colorPrimary);
    QBrush brushHover(m_colorPrimary.darker(120));


    QPen pen(m_colorPrimary.darker(150));
    QPen hoverPen(m_colorPrimary.lighter(150));


    if(m_hovered || m_selected) {
        painter->setBrush(brushHover);
        painter->setPen(hoverPen);
        painter->drawRect(m_rect);
    } else {
        painter->setBrush(brush);
        painter->setPen(pen);
        painter->drawRect(m_rect);
    }
}

QSharedPointer<QPolygon> AbstractItem::buildTriangle(const QRectF &parentRect, double scale, qint16 rotation)
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


void AbstractItem::/*slot_*/onItemClicked(AbstractItem *item)
{
    emit signal_itemClicked(item);
}

void AbstractItem::addItem(AbstractItem *item)
{
    m_items.append(item);
    connect(item, &AbstractItem::signal_itemClicked, this, &AbstractItem::/*slot_*/onItemClicked);
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

void AbstractItem::setEnabled(bool option)
{
    m_enabled = option;
    update();
}

void AbstractItem::setSelected(AbstractItem *item)
{
    m_selectedItem = item;
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

void AbstractItem::expand()
{
    m_expanded = true;
    quint32 height = 0;
    for(AbstractItem *item : m_items)
    {
        height += item->m_rect.height();
        height += 10;
    }

    height *= m_items.size();
    m_rect.setHeight(height);

    for(AbstractItem *item : m_items)
    {
        item->show();
    }
    update();
}

void AbstractItem::collapse()
{
    m_expanded = false;
    qreal height = 50;
    m_rect.setHeight(height);
    for(AbstractItem *item : m_items)
    {
        item->hide();
    }
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
    if(!m_items.empty()) {
        QPointF scenePos = event->scenePos();

        for (AbstractItem *child : m_items) {
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


AbstractItem& AbstractItem::operator=(AbstractItem&& other)
{
    m_enabled = std::move(other.m_enabled);
    m_selected = std::move(other.m_selected);
    m_hovered = std::move(other.m_hovered);
    m_expanded = std::move(other.m_expanded);
    m_expandable = std::move(other.m_expandable);
    m_groupId = std::move(other.m_groupId);
    m_text = std::move(other.m_text);
    m_parentScene = std::move(other.m_parentScene);

    m_colorPrimary = std::move(other.m_colorPrimary);
    m_colorSecondary = std::move(other.m_colorSecondary);
    m_colorTertiary = std::move(other.m_colorTertiary);


    m_rect = std::move(other.m_rect);

    m_selectedItem = std::move(other.m_selectedItem);

}


bool AbstractItem::operator==(const AbstractItem& other)
{
    return m_enabled == other.m_enabled && m_selected == other.m_selected && m_expandable == other.m_expandable && m_groupId == other.m_groupId
           && m_text == other.m_text && m_parentScene == other.m_parentScene && m_colorPrimary == other.m_colorPrimary
           && m_colorSecondary == other.m_colorSecondary && m_colorTertiary == other.m_colorTertiary && m_rect == other.m_rect;
}
