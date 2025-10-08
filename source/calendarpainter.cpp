#include "include/calendarpainter.h"

CalendarPainter::CalendarPainter() :
    AbstractPainter()
{
}

CalendarPainter::~CalendarPainter()
{
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


void CalendarPainter::slot_onItemClicked()
{
    AbstractItem *clickedItem = qobject_cast<AbstractItem*>(sender());
    if(clickedItem) {
        if(clickedItem->isSelected()) {
            clickedItem->setSelected(false);
        } else {
            clickedItem->setSelected(true);
            if(previousClickedItem)
            previousClickedItem->setSelected(false);
        }
        // qDebug() << "item №" << clickedItem->day();
    }
    previousClickedItem = clickedItem;
}



void CalendarPainter::slot_windowResized(quint16 wWidth, quint16 wHeight)
{
    m_wWidth = wWidth;
    m_wHeight = wHeight;
    this->setSceneRect(0, 0, m_wWidth, m_wHeight);
    m_rectSizeX = wWidth / m_daysPerWeek - 10;
    m_rectSizeY = wHeight / ((m_daysPerMonth / m_daysPerWeek) + 1);

    reposition();
}

void CalendarPainter::slot_settingsChanged()
{

}
void CalendarPainter::reposition()
{
    int columns = m_daysPerWeek;

    for(int i = 0; i < m_daysPerMonth; i++)
    {
        int row = i / columns;
        int column = i % columns;

        activeItems[i]->setRect(column * (m_rectSizeX + 8) + 10, row * (m_rectSizeY + 8) + 10, m_rectSizeX, m_rectSizeY);
    }
    update();
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

    for(int i = 0; i < m_daysPerMonth; i++)
    {
        int row = i / columns;
        int column = i % columns;

        // временно прописываем позицию отрисовки прямо в иницилизации ячейки календаря
        // TODO: перенести параметры позиции в настройки
        CalendarItem *item = new CalendarItem(QRectF(column * (m_rectSizeX + 8) + 10, row * (m_rectSizeY + 8), m_rectSizeX, m_rectSizeY), true, i + 1);
        item->setDay(i + 1); // +1 т.к. нумерация дней идёт с 1, не с 0
        activeItems.push_back(item);
        this->addItem(item);
        connect(item, &AbstractItem::signal_itemClicked, this, &CalendarPainter::slot_onItemClicked);
    }
    update();
    // emit signal_rebuild(this);
}
