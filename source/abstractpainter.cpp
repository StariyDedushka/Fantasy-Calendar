#include "include/abstractpainter.h"

AbstractPainter::AbstractPainter()
{

}
AbstractPainter::~AbstractPainter()
{
    for(AbstractItem* item : items)
    {
        delete item;
    }
}


void AbstractPainter::addItem(AbstractItem *item)
{
    // qDebug() << "Adding item to scene:" << &item;
    // qDebug() << "Item type:" << typeid(*item).name();
    // qDebug() << "Is QGraphicsItem?" << (dynamic_cast<QGraphicsItem*>(item) != nullptr);

    if (item == nullptr) {
        // qDebug() << "ERROR: Attempt to add null item!";
        return;
    }

    if (!dynamic_cast<QGraphicsItem*>(item)) {
        // qDebug() << "ERROR: Item is not a QGraphicsItem!";
        return;
    }

    QGraphicsScene::addItem(item);
}

void AbstractPainter::slot_onItemClicked()
{
    update();
}
