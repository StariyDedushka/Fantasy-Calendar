#include "include/calendarscene.h"

CalendarScene::CalendarScene(CalendarSystem *system, CustomDateTime *globalTime) :
    AbstractScene()
    , m_system(system)
    , m_globalTime(globalTime)
{
    EventContainer container(QRectF(20, 20, 60, 60), "text");
}

CalendarScene::~CalendarScene()
{
}


void CalendarScene::initialize()
{
    this->setSceneRect(0, 0, m_wWidth, m_wHeight);
    m_rectSizeX = 120;
    m_rectSizeY = 70;
    qDebug() << "Initialized scene!";

    /*slot_*/rebuild();
}



void CalendarScene::/*slot_*/windowResized(quint16 wWidth, quint16 wHeight)
{
    m_wWidth = wWidth;
    m_wHeight = wHeight;
    this->setSceneRect(0, 0, m_wWidth, m_wHeight);
    m_rectSizeX = wWidth / m_system->daysInWeek() - 10;
    m_rectSizeY = wHeight / ((m_system->daysInMonth(m_globalTime->month()) / m_system->daysInWeek()) + 1);

    reposition();
}

void CalendarScene::/*slot_*/settingsChanged()
{

}
void CalendarScene::reposition()
{
    int columns = m_system->daysInMonth(m_globalTime->month());

    for(int i = 0; i < m_system->daysInMonth(m_globalTime->month()); i++)
    {
        int row = 0;
        if(columns != 0)
            row = i / columns;
        int column = i % columns;

        m_items[i]->setRect(column * (m_rectSizeX + 8) + 10, row * (m_rectSizeY + 8) + 10, m_rectSizeX, m_rectSizeY);
    }
    update();
}

void CalendarScene::/*slot_*/rebuild(QVector<AbstractItem*> *input)
{
    qDebug() << "Rebuild called!";
    if(!m_items.isEmpty())
    {
        for(int i = 0; i < m_system->daysInMonth(m_globalTime->month()); i++)
        {
            // qDebug() << "Removing item №" << i << "...";
            this->removeItem(m_items.at(0));
            m_items.removeAt(0);
        }
    }

    int columns = m_system->daysInWeek();

    for(int i = 0; i < m_system->daysInMonth(m_globalTime->month()); i++)
    {
        int row = i / columns;
        int column = i % columns;

        // временно прописываем позицию отрисовки прямо в иницилизации ячейки календаря
        // TODO: перенести параметры позиции в настройки
        CalendarItem *item (new CalendarItem(QRectF(column * (m_rectSizeX + 8) + 10, row * (m_rectSizeY + 8), m_rectSizeX, m_rectSizeY), " ",
                                            Qt::green, Qt::gray, Qt::yellow/*palette.colorPrimary, palette.colorSecondary, palette.colorTertiary*/, true, i + 1, 2000, 2000, this));
        item->setDay(i + 1); // +1 т.к. нумерация дней идёт с 1, не с 0
        m_items.push_back(item);
        this->addItem(item);
        connect(item, &AbstractItem::signal_itemClicked, this, &CalendarScene::/*slot_*/onItemClicked);
    }
    update();
    // emit signal_rebuild(this);
}
