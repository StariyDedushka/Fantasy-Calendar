#include "include/eventscene.h"


EventScene::EventScene(CalendarSystem *system) :
    AbstractScene(system)
{
}

EventScene::~EventScene()
{
}


void EventScene::initialize()
{
    this->setSceneRect(0, 0, m_wWidth, m_wHeight);
    m_rectSizeX = 120;
    m_rectSizeY = 70;
    qDebug() << "Event Painter: initialized scene!";

    slot_rebuild();
}



void EventScene::slot_windowResized(quint16 wWidth, quint16 wHeight)
{
    m_wWidth = wWidth;
    m_wHeight = wHeight;
    this->setSceneRect(0, 0, m_wWidth, m_wHeight);
    m_rectSizeX = wWidth - 20;
    m_rectSizeY = 40 * (m_items.count() + 1);

    reposition();
}

void EventScene::slot_settingsChanged()
{

}
void EventScene::reposition()
{
    qDebug() << "EventScene: repositioning!";
    uint row = 0;
    foreach(AbstractItem *container, m_items)
    {
        uint size = container->getItems().size();
        m_rectSizeY = 30 * size;
        container->setRect(10, row * (m_rectSizeY + 8) + 10, m_rectSizeX, m_rectSizeY);
        row++;
    }
    update();
}

void EventScene::slot_rebuild(QVector<AbstractItem*> *input)
{
    qDebug() << "EventScene: rebuild called!";
    while(!m_items.empty())
    {
        this->removeItem(m_items.at(0));
        m_items.removeAt(0);
    }


    int row = 0;
    row++;

    // временно прописываем позицию отрисовки прямо в иницилизации ячейки календаря
    // TODO: перенести параметры позиции в настройки
    if(input)
    {
        // Очищаем старые элементы
        // 1. Очищаем предыдущие элементы
        for(AbstractItem *item : m_items) {
            this->removeItem(item);  // Убираем из сцены
            delete item;             // Освобождаем память
        }
        m_items.clear();

        // Создаем новые элементы
        for(int i = 0; i < input->size(); ++i) {
            AbstractItem *container = new EventContainer(
                QRectF(row * (m_rectSizeX + 8) + 10, row * (m_rectSizeY + 8), m_rectSizeX, m_rectSizeY),
                "", Qt::green, Qt::darkGreen, Qt::yellow,
                true);
            m_items.push_back(container);
            this->addItem(container);
            connect(container, &AbstractItem::signal_itemClicked, this, &EventScene::slot_onItemClicked);
            qDebug() << "EventScene: container entry added! Container address:" << &container;
        }
        update();
    }
}
