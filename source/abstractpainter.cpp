#include "include/abstractpainter.h"

AbstractPainter::AbstractPainter(QColor itemColor) {
    m_previousClickedItem = nullptr;
    m_itemColor = itemColor;
}

AbstractPainter::~AbstractPainter()
{
}
void AbstractPainter::toggleClicked(AbstractItem *clickedItem)
{

    qDebug() << "AbstractPainter toggleClicked() clicked item:" << static_cast<void*>(clickedItem);

    if (!clickedItem) {
        qDebug() << "Clicked item is null!";
        return;
    }

    // Если кликнули по уже выделенному элементу - снимаем выделение
    if (clickedItem->isSelected()) {
        qDebug() << "Deselecting current item";
        clickedItem->setSelected(false);
        m_previousClickedItem = nullptr;
    }
    // Если кликнули по другому элементу
    else {
        // Снимаем выделение с предыдущего элемента
        if (m_previousClickedItem && m_previousClickedItem != clickedItem) {
            qDebug() << "Deselecting previous item";


            m_previousClickedItem->setSelected(false);
        }

        // Выделяем новый элемент
        qDebug() << "Selecting new item";
        clickedItem->setSelected(true);
        m_previousClickedItem = clickedItem;
    }
    update();

}


void AbstractPainter::addItem(AbstractItem *item)
{
    qDebug() << "Adding item to scene:" << &item;
    qDebug() << "Item type:" << typeid(*item).name();
    qDebug() << "Is QGraphicsItem?" << (dynamic_cast<QGraphicsItem*>(item) != nullptr);

    if (item == nullptr) {
        qDebug() << "ERROR: Attempt to add null item!";
        return;
    }

    if (!dynamic_cast<QGraphicsItem*>(item)) {
        qDebug() << "ERROR: Item is not a QGraphicsItem!";
        return;
    }

    QGraphicsScene::addItem(item);
}
