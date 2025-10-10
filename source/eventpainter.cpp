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
    qDebug() << "Event Painter: initialized scene!";

    slot_rebuild();
}


void EventPainter::slot_onItemClicked()
{
    AbstractItem *clickedItem = qobject_cast<AbstractItem*>(sender());
    qDebug() << "EventPainter::slot_onItemClicked() from:" << static_cast<void*>(sender())
             << "clicked item:" << static_cast<void*>(clickedItem);

    if (clickedItem) {
        toggleClicked(clickedItem);
    }
}



void EventPainter::slot_windowResized(quint16 wWidth, quint16 wHeight)
{
    m_wWidth = wWidth;
    m_wHeight = wHeight;
    this->setSceneRect(0, 0, m_wWidth, m_wHeight);
    m_rectSizeX = wWidth - 20;
    m_rectSizeY = 40 * (items.count() + 1);

    reposition();
}

void EventPainter::slot_settingsChanged()
{

}
void EventPainter::reposition()
{
    qDebug() << "EventPainter: repositioning!";
    uint row = 0;
    foreach(AbstractItem *container, items)
    {
        uint size = container->getItems()->size();
        m_rectSizeY = 30 * size;
        container->setRect(10, row * (m_rectSizeY + 8) + 10, m_rectSizeX, m_rectSizeY);
        row++;
    }
    update();
}

void EventPainter::slot_rebuild(QVector<AbstractItem*> *input)
{
    qDebug() << "EventPainter: rebuild called!";
    while(!items.empty())
    {
        this->removeItem(items.at(0));
        items.removeAt(0);
    }


    int row = 0;
    row++;

    // временно прописываем позицию отрисовки прямо в иницилизации ячейки календаря
    // TODO: перенести параметры позиции в настройки
    if(input)
    {
        // Очищаем старые элементы
        // 1. Очищаем предыдущие элементы
        for(AbstractItem *item : items) {
            this->removeItem(item);  // Убираем из сцены
            delete item;             // Освобождаем память
        }
        items.clear();

        // // 2. Очищаем переданные элементы (если нужно)
        // if(input) {
        //     for(AbstractItem *item : *input) {
        //         delete item;  // Освобождаем старые объекты
        //     }
        //     input->clear();   // Очищаем вектор

        // Создаем новые элементы
        for(int i = 0; i < input->size(); ++i) {
            AbstractItem *container = new EventContainer(
                QRectF(row * (m_rectSizeX + 8) + 10, row * (m_rectSizeY + 8), m_rectSizeX, m_rectSizeY),
                Qt::green,
                true);
            // (*input)[i] = container; // Обновляем указатель в исходном векторе
            items.push_back(container);
            this->addItem(container);
            connect(container, &AbstractItem::signal_itemClicked, this, &EventPainter::slot_onItemClicked);
            qDebug() << "EventPainter: container entry added! Container address:" << &container;
        }
        update();
    }
}
