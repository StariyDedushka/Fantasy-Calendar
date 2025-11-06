#include "include/abstractscene.h"

AbstractScene::AbstractScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

AbstractScene::~AbstractScene()
{
    for(AbstractItem *item : m_items)
    {
        delete item;
    }
    m_items.clear();
}


bool AbstractScene::addItem(AbstractItem *item)
{
    // qDebug() << "Adding item to scene:" << &item;
    // qDebug() << "Item type:" << typeid(*item).name();
    // qDebug() << "Is QGraphicsItem?" << (dynamic_cast<QGraphicsItem*>(item) != nullptr);

    if (item == nullptr) {
        qDebug() << "ERROR: Attempt to add null item!";
        return false;
    }

    QGraphicsScene::addItem(item);
    return true;
}

void AbstractScene::/*slot_*/onItemClicked()
{
    update();
}
