#include "include/calendarscene.h"

CalendarScene::CalendarScene(QObject *parent)
    : QGraphicsScene(parent)
    , m_cellSize(50, 50)
    , m_columns(7)
    , m_rows(6)
    , m_backgroundColor(Qt::lightGray)
    , m_showHeader(true)
    , m_showWeekDays(true)
    , m_headerItem(nullptr)
    , m_weekDaysItem(nullptr)
{
    setBackgroundBrush(QBrush(m_backgroundColor));
    setupConnections();
}

CalendarScene::~CalendarScene()
{
    clearCalendar();
}

void CalendarScene::setupConnections()
{
    // Соединения будут устанавливаться при добавлении элементов
}

void CalendarScene::setCalendarData(const CalendarVisualData& data)
{
    clearCalendar();

    m_calendarItems = data.items;
    m_headerText = data.headerText;
    m_weekDaysHeader = data.weekDaysHeader;
    m_cellSize = data.cellSize;
    m_columns = data.columns;
    m_rows = data.rows;

    // Добавляем элементы на сцену
    for (CalendarItem* item : m_calendarItems) {
        addItem(item);

        // Подключаем сигналы от каждого элемента
        connect(item, &CalendarItem::itemClicked,
                this, &CalendarScene::handleItemClick);
    }

    // Создаем заголовки
    if (m_showHeader) {
        createHeader();
    }

    if (m_showWeekDays) {
        createWeekDaysHeader();
    }

    // Расставляем элементы
    repositionItems();

    emit sceneReady();
}

void CalendarScene::clearCalendar()
{
    // Отключаем все соединения
    for (CalendarItem* item : m_calendarItems) {
        item->disconnect(this);
    }

    // Удаляем все элементы со сцены
    clear();

    // Очищаем списки
    m_calendarItems.clear();
    m_headerItem = nullptr;
    m_weekDaysItem = nullptr;
}

void CalendarScene::setCellSize(const QSizeF& size)
{
    if (m_cellSize != size) {
        m_cellSize = size;
        updateLayout();
    }
}

void CalendarScene::setGridSize(quint16 columns, quint16 rows)
{
    if (m_columns != columns || m_rows != rows) {
        m_columns = columns;
        m_rows = rows;
        updateLayout();
    }
}

void CalendarScene::setBackgroundColor(const QColor& color)
{
    if (m_backgroundColor != color) {
        m_backgroundColor = color;
        setBackgroundBrush(QBrush(m_backgroundColor));
    }
}

void CalendarScene::setHeaderVisible(bool visible)
{
    if (m_showHeader != visible) {
        m_showHeader = visible;
        updateLayout();
    }
}

void CalendarScene::updateLayout()
{
    repositionItems();

    // Обновляем заголовки
    if (m_headerItem) {
        m_headerItem->setVisible(m_showHeader);
    }
    if (m_weekDaysItem) {
        m_weekDaysItem->setVisible(m_showWeekDays);
    }
}

void CalendarScene::repositionItems()
{
    if (m_calendarItems.isEmpty()) return;

    qreal startY = 0;

    // Место для заголовка месяца
    if (m_showHeader && m_headerItem) {
        m_headerItem->setPos(0, startY);
        startY += m_cellSize.height();
    }

    // Место для заголовка дней недели
    if (m_showWeekDays && m_weekDaysItem) {
        m_weekDaysItem->setPos(0, startY);
        startY += m_cellSize.height();
    }

    // Расставляем дни в сетке
    int currentColumn = 0;
    int currentRow = 0;
    qreal x = 0;
    qreal y = startY;

    for (CalendarItem* item : m_calendarItems) {
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

void CalendarScene::createHeader()
{
    if (m_headerText.isEmpty()) return;

    if (!m_headerItem) {
        m_headerItem = new QGraphicsTextItem();
        m_headerItem->setDefaultTextColor(Qt::black);
        QFont headerFont;
        headerFont.setPointSize(12);
        headerFont.setBold(true);
        m_headerItem->setFont(headerFont);
        addItem(m_headerItem);
    }

    m_headerItem->setPlainText(m_headerText);
    m_headerItem->setVisible(m_showHeader);
}

void CalendarScene::createWeekDaysHeader()
{
    if (m_weekDaysHeader.isEmpty()) return;

    if (!m_weekDaysItem) {
        m_weekDaysItem = new QGraphicsTextItem();
        m_weekDaysItem->setDefaultTextColor(Qt::darkBlue);
        QFont weekDaysFont;
        weekDaysFont.setPointSize(9);
        m_weekDaysItem->setFont(weekDaysFont);
        addItem(m_weekDaysItem);
    }

    m_weekDaysItem->setPlainText(m_weekDaysHeader);
    m_weekDaysItem->setVisible(m_showWeekDays);
}

void CalendarScene::highlightDate(quint16 day, quint16 month, quint32 year)
{
    // Снимаем выделение со всех элементов
    for (CalendarItem* item : m_calendarItems) {
        item->setSelected(false);
    }

    // Находим и выделяем нужный элемент
    for (CalendarItem* item : m_calendarItems) {
        if (item->day() == day && item->month() == month && item->year() == year) {
            item->setSelected(true);
            break;
        }
    }
}

void CalendarScene::clearHighlights()
{
    for (CalendarItem* item : m_calendarItems) {
        item->setSelected(false);
    }
}

CalendarItem* CalendarScene::itemAtPos(const QPointF& pos) const
{
    QGraphicsItem* item = itemAt(pos, QTransform());
    return qgraphicsitem_cast<CalendarItem*>(item);
}

void CalendarScene::handleItemClick(CalendarItem* item)
{
    if (item && item->isEnabled()) {
        // Можно добавить дополнительную логику выделения
        clearHighlights();
        item->setSelected(true);

        emit itemClicked(item);
    }
}
