#include "include/eventpainter.h"


EventPainter::EventPainter() :
    AbstractPainter()
{
}

EventPainter::~EventPainter()
{
}


void EventPainter::initialize()
{
    this->setSceneRect(0, 0, m_wWidth, m_wHeight);
    m_rectSizeX = 120;
    m_rectSizeY = 70;
    qDebug() << "Initialized scene!";

    rebuild();
}


void EventPainter::slot_onItemClicked()
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



void EventPainter::slot_windowResized(quint16 wWidth, quint16 wHeight)
{
    m_wWidth = wWidth;
    m_wHeight = wHeight;
    this->setSceneRect(0, 0, m_wWidth, m_wHeight);
    m_rectSizeX = wWidth - 20;
    m_rectSizeY = wHeight / activeItems.count() - 10;

    reposition();
}

void EventPainter::slot_settingsChanged()
{

}
void EventPainter::reposition()
{
    uint row = 0;
    foreach(AbstractItem *container, activeItems)
    {
        container->setRect(10, row * (m_rectSizeY + 8) + 10, m_rectSizeX, m_rectSizeY);
        row++;
    }
    update();
}

void EventPainter::rebuild()
{
    qDebug() << "Rebuild called!";
    while(!activeItems.empty())
    {
        this->removeItem(activeItems.at(0));
        activeItems.removeAt(0);
    }


    while(!activeItems.end())
    {
        int row = 0;
        row++;

        // временно прописываем позицию отрисовки прямо в иницилизации ячейки календаря
        // TODO: перенести параметры позиции в настройки
        EventContainer *container = new EventContainer(QRectF(row * (m_rectSizeX + 8) + 10, row * (m_rectSizeY + 8), m_rectSizeX, m_rectSizeY), true);
        activeItems.push_back(container);
        this->addItem(container);
        connect(container, &AbstractItem::signal_itemClicked, this, &EventPainter::slot_onItemClicked);
    }
    update();
    // emit signal_rebuild(this);
}
