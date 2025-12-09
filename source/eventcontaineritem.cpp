#include "include/eventcontaineritem.h"
#include "include/customdatetime.h"

EventContainerItem::EventContainerItem(const QRectF &rect,
                                       QString text,
                                       QColor colorPrimary,
                                       QColor colorSecondary,
                                       QColor colorTertiary,
                                       bool enabled,
                                       QObject *parent)
    : AbstractItem(rect,
                   text,
                   colorPrimary,
                   colorSecondary,
                   colorTertiary,
                   enabled,
                   parent)
{
    m_expandable = true;
}

void EventContainerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    std::unique_ptr<QPolygon> triangle = buildTriangle(m_rect, 1.0, static_cast<qint16>(m_selected * 90));
    painter->drawPolygon(*triangle);
}

std::unique_ptr<QPolygon> EventContainerItem::buildTriangle(const QRectF &parentRect, double scale, qint16 rotation)
{
    std::unique_ptr<QPolygon> triangle(new QPolygon);
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
