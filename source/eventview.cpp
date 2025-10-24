#include "include/eventview.h"

EventView::EventView(CalendarSystem *system) :
    m_system(system)
{
    setDragMode(QGraphicsView::NoDrag);
    scene = new EventScene(system);
    emit signal_windowResized(this->width(), this->height());

    if (scene)
    {
        connect(this, &EventView::signal_windowResized, scene, &EventScene::/*slot_*/windowResized);
        connect(this, &EventView::signal_rebuild, scene, &EventScene::/*slot_*/rebuild);
    }
    emit signal_windowResized(this->width(), this->height());

    scene->initialize();
    setScene(scene);
    emit signal_rebuild(nullptr);
}

void EventView::resizeEvent(QResizeEvent *event)
{
    m_windowWidth = this->width();
    m_windowHeight = this->height();
    emit signal_windowResized(m_windowWidth, m_windowHeight);
}
