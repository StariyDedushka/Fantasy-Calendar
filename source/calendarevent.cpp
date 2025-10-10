#include "include/calendarevent.h"

CalendarEvent::CalendarEvent(const QRectF &rect,  QColor fillColor, bool enabled, QGraphicsItem *parent) :
    AbstractItem(rect, fillColor, enabled, parent)
{
    m_text = "lorem ipsum skibidi toilet";
}

void CalendarEvent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor hoverColor(colorDarken(m_fillColor));

    QBrush brush(m_fillColor);
    QBrush brushHover(hoverColor);

    QColor outlineColor(colorDarken(m_fillColor));
    QColor hoverOutlineColor(colorLighten(m_fillColor));

    QPen pen(outlineColor);
    QPen hoverPen(hoverOutlineColor);

    if(m_hovered || m_selected) {
        painter->setBrush(brushHover);
        painter->setPen(hoverPen);
        painter->drawRect(m_rect);
    } else {
        painter->setBrush(brush);
        painter->setPen(pen);
        painter->drawRect(m_rect);
    }
    painter->drawText(m_rect, m_text);
}
