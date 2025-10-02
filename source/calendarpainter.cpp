#include "include/calendarpainter.h"

CalendarPainter::CalendarPainter() {
    // connect(this, &CalendarPainter::signal_rebuild, this, &CalendarPainter::slot_rebuild);
}

void CalendarPainter::addItem(CalendarItem *item)
{
    QGraphicsScene::addItem(item);
}

void CalendarPainter::initialize()
{
    this->setSceneRect(0, 0, m_wWidth, m_wHeight);
    m_rectSizeX = 120;
    m_rectSizeY = 70;
    m_daysPerMonth = 30;
    m_daysPerWeek = 7;
    m_daysPerYear = 365;
    qDebug() << "Initialized scene!";

    rebuild();
}

void CalendarPainter::slot_callRebuild()
{
    rebuild();
}

// void CalendarPainter::mousePressEvent(QGraphicsSceneMouseEvent *event)
// {
//     qDebug() << "Custom view clicked.";
//     QGraphicsScene::mousePressEvent(event);
// }

void CalendarPainter::slot_windowChanged(quint32 wWidth, quint32 wHeight)
{
    m_wWidth = wWidth;
    m_wHeight = wHeight;
    m_rectSizeX = wWidth / m_daysPerWeek;
    this->setSceneRect(0, 0, m_wWidth, m_wHeight);

    rebuild();
}

void CalendarPainter::slot_settingsChanged(quint16 daysPerWeek, quint16 daysPerMonth, quint16 daysPerYear)
{

}

void CalendarPainter::rebuild()
{
    qDebug() << "Rebuild called!";
    if(!activeItems.isEmpty())
    {
        for(int i = 0; i < m_daysPerMonth; i++)
        {
            // qDebug() << "Removing item №" << i << "...";
            this->removeItem(activeItems.at(0));
            activeItems.removeAt(0);
        }
    }

    int columns = m_daysPerWeek;
    // int rows = (m_daysPerMonth + columns - 1) / columns;

    for(int i = 0; i < m_daysPerMonth; i++)
    {
        int row = i / columns;
        int column = i % columns;
        CalendarItem *item = new CalendarItem(QRectF(column * (m_rectSizeX + 5), row * (m_rectSizeY + 5), m_rectSizeX, m_rectSizeY));
        // qDebug() << "item №" << i << ": xCoord =" << column * (m_rectSizeX + 5) << " yCoord = " << row * (m_rectSizeY + 5);
        activeItems.push_back(item);
        this->addItem(item);
    }
    emit signal_rebuild(this);
}
