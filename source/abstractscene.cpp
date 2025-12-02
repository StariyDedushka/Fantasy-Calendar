#include "include/abstractscene.h"
#include "include/calendarscene.h"

AbstractScene::AbstractScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_cellSize(50, 50)
    , m_backgroundColor(Qt::lightGray)
{
    m_headerItems["main"] = new QGraphicsTextItem();
    m_showHeaders["main"] = true;
    setBackgroundBrush(QBrush(m_backgroundColor));
    setupConnections();
}

AbstractScene::~AbstractScene()
{
    clearScene();
    for(QGraphicsTextItem* item : m_headerItems)
        delete item;
}

void AbstractScene::setupConnections()
{
    // Соединения будут устанавливаться при добавлении элементов
}

void AbstractScene::setSceneData(const SceneVisualData& data)
{
    clearScene();

    m_dataItems = data.items;
    m_headerTexts["main"] = data.headers["main"];
    m_cellSize = data.cellSize;
    m_columns = data.columns;
    m_rows = data.rows;

    // Добавляем элементы на сцену
    for (AbstractItem* item : m_items) {
        addItem(item);

        // Подключаем сигналы от каждого элемента
        connect(item, &AbstractItem::itemClicked,
                this, &AbstractScene::handleItemClick);
    }

    // Создаем заголовки
    if (m_showHeaders["main"])
        createHeader("main");

}

void AbstractScene::clearScene()
{
    // Отключаем все соединения
    for (AbstractItem* item : m_items) {
        item->disconnect(this);
    }

    // Удаляем все элементы со сцены
    clear();

    // Очищаем списки
    m_dataItems.clear();

    for(QGraphicsTextItem *item : m_headerItems)
        delete item;
    m_headerItems.clear();
}

void AbstractScene::setCellSize(const QSizeF& size)
{
    if (m_cellSize != size) {
        m_cellSize = size;
        updateLayout();
    }
}

void AbstractScene::setGridSize(quint16 columns, quint16 rows)
{
    if (m_columns != columns || m_rows != rows) {
        m_columns = columns;
        m_rows = rows;
        updateLayout();
    }
}

void AbstractScene::setBackgroundColor(const QColor& color)
{
    if (m_backgroundColor != color) {
        m_backgroundColor = color;
        setBackgroundBrush(QBrush(m_backgroundColor));
    }
}

void AbstractScene::setHeaderVisible(const QString& key, bool visible)
{
    if (m_showHeaders[key] != visible) {
        m_showHeaders[key] = visible;
        updateLayout();
    }
}

void AbstractScene::updateLayout()
{
    repositionItems();

    // Обновляем заголовки
    if (!m_headerItems.isEmpty()) {
        m_headerItems["main"]->setVisible(m_showHeaders["main"]);
    }
}

void AbstractScene::repositionItems()
{
    if (m_dataItems.isEmpty()) return;

    qreal startY = 0;

    // Место для главного заголовка
    if (m_showHeaders["main"] && m_headerItems["main"])
    {
        m_headerItems["main"]->setPos(0, startY);
        startY += m_cellSize.height();
    }

    // Расставляем дни в сетке
    int currentColumn = 0;
    int currentRow = 0;
    qreal x = 0;
    qreal y = startY;

    for (AbstractItem* item : m_items) {
        // Устанавливаем позицию и размер
        item->setPos(x, y);
        item->setRect(0, 0, m_cellSize.width(), m_cellSize.height());

        // Переходим к следующей ячейке
        currentColumn++;
        x += m_cellSize.width();

        // Переход на новую строку
        if (currentColumn >= m_columns) {
            currentColumn = 0;
            currentRow++;
            x = 0;
            y += m_cellSize.height();
        }

        // Защита от бесконечного цикла
        if (currentRow >= m_rows) {
            break;
        }
    }
}

void AbstractScene::createHeader(const QString& key)
{
    if (m_headerItems.isEmpty()) return;

    if (!m_headerItems[key]) {
        m_headerItems[key] = new QGraphicsTextItem();
        m_headerItems[key]->setDefaultTextColor(Qt::black);
        QFont headerFont;
        headerFont.setPointSize(12);
        headerFont.setBold(true);
        m_headerItems[key]->setFont(headerFont);
        addItem(m_headerItems[key]);
    }

    m_headerItems[key]->setPlainText(m_headerTexts[key]);
    m_headerItems[key]->setVisible(m_showHeaders[key]);
}

// void AbstractScene::createWeekDaysHeader()
// {
//     if (m_weekDaysHeader.isEmpty()) return;

//     if (!m_weekDaysItem) {
//         m_weekDaysItem = new QGraphicsTextItem();
//         m_weekDaysItem->setDefaultTextColor(Qt::darkBlue);
//         QFont weekDaysFont;
//         weekDaysFont.setPointSize(9);
//         m_weekDaysItem->setFont(weekDaysFont);
//         addItem(m_weekDaysItem);
//     }

//     m_weekDaysItem->setPlainText(m_weekDaysHeader);
//     m_weekDaysItem->setVisible(m_showWeekDays);
// }

void AbstractScene::highlightItem(quint32 id)
{
    // Снимаем выделение со всех элементов
    for (AbstractItem* item : m_items) {
        item->setSelected(false);
    }

    // Находим и выделяем нужный элемент
    for (AbstractItem* item : m_items) {
        if (item->id() == id) {
            item->setSelected(true);
            break;
        }
    }
}

void AbstractScene::clearHighlights()
{
    for (AbstractItem* item : m_items) {
        item->setSelected(false);
    }
}

AbstractItem* AbstractScene::itemAtPos(const QPointF& pos) const
{
    QGraphicsItem* item = itemAt(pos, QTransform());
    return qgraphicsitem_cast<AbstractItem*>(item);
}

void AbstractScene::handleItemClick(AbstractItem* item)
{
    if (item && item->isEnabled()) {
        // Можно добавить дополнительную логику выделения
        clearHighlights();
        item->setSelected(true);

        emit itemClicked(item);
    }
}
