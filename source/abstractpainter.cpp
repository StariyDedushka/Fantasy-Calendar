#include "include/abstractpainter.h"

AbstractPainter::AbstractPainter() {
    // connect(this, &AbstractPainter::signal_rebuild, this, &AbstractPainter::slot_rebuild);
    previousClickedItem = nullptr;
    // activeItems = new QVector<AbstractItem*>();
}

AbstractPainter::~AbstractPainter()
{
}


void AbstractPainter::slot_callRebuild()
{
    rebuild();
}

void AbstractPainter::slot_onItemClicked()
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

// void AbstractPainter::slot_windowResized(quint16 wWidth, quint16 wHeight)
// {
//     m_wWidth = wWidth;
//     m_wHeight = wHeight;
//     this->setSceneRect(0, 0, m_wWidth, m_wHeight);

//     reposition();
// }

void AbstractPainter::addItem(AbstractItem *item)
{
    QGraphicsScene::addItem(item);
}
