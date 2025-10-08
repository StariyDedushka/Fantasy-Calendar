#include "include/calendarevent.h"

CalendarEvent::CalendarEvent(const QRectF &rect,  QColor fillColor, bool enabled) :
    AbstractItem(rect, fillColor, enabled)
{

}

void CalendarEvent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int red = m_fillColor.red();
    int green = m_fillColor.green();
    int blue = m_fillColor.blue();
    int alpha = m_fillColor.alpha();

    QBrush brush(m_fillColor);
    QBrush brushHover(alpha - 55);

    QColor outlineColor(red + 15, green + 15, blue + 15);
    QColor hoverOutlineColor(red - 10, green - 10, blue - 10);

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
    update();
}
