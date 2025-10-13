#include "include/calendarevent.h"

CalendarEvent::CalendarEvent(const QRectF &rect,  QColor colorPrimary, QColor colorSecondary, QColor colorTertiary, bool enabled, QGraphicsItem *parent ) :
    AbstractItem(rect, colorPrimary, colorSecondary, colorTertiary, enabled, parent)
{
    m_text = "lorem ipsum skibidi toilet";
}

void CalendarEvent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor hoverColor(colorDarken(colorPrimary));

    QBrush brush(colorPrimary);
    QBrush brushHover(hoverColor);

    QColor outlineColor(colorDarken(colorPrimary));
    QColor hoverOutlineColor(colorLighten(colorPrimary));

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
