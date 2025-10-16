#include "include/AbstractScene.h"

AbstractScene::AbstractScene()
{

}

AbstractScene::~AbstractScene()
{

}


void AbstractScene::addItem(AbstractItem *item)
{
    // qDebug() << "Adding item to scene:" << &item;
    // qDebug() << "Item type:" << typeid(*item).name();
    // qDebug() << "Is QGraphicsItem?" << (dynamic_cast<QGraphicsItem*>(item) != nullptr);

    if (item == nullptr) {
        qDebug() << "ERROR: Attempt to add null item!";
        return;
    }


    QGraphicsScene::addItem(item);
}

void AbstractScene::slot_onItemClicked()
{
    update();
}
