#include "include/eventpresenter.h"

EventPresenter::EventPresenter(CalendarSystem* system,
                               CustomDateTime* globalTime,
                               EventView* view,
                               QObject* parent)
    : QObject(parent)
    , m_system(system)
    , m_globalTime(globalTime)
    , m_view(view)
    , m_columns(1)
    , m_rows(0)
    , m_zoomLevel(1.0)
    , m_rows(system->weeksInMonth(globalTime->month(), globalTime->year()))
    , m_zoomLevel(1.0)
{
    // Устанавливаем начальную дату

    initialize();
}

EventPresenter::~EventPresenter()
{
    // Отключаем все соединения
    if (m_view) {
        LOG(INFO, logger, "Destructor called");
        m_view->disconnect(this);
    }
}

void EventPresenter::initialize()
{
    if (!m_view || !m_system || !m_globalTime) {
        LOG(WARN, logger, "EventPresenter: Missing dependencies");
        return;
    }

    // Настраиваем соединения
    setupConnections();

    // Первоначальная загрузка данных
    refreshEvents();
}

void EventPresenter::setupConnections()
{
    if (!m_view || !m_system || !m_globalTime) return;

    // Подключаем сигналы от View
    connect(m_view, &EventView::eventClicked,
            this, &EventPresenter::handleDateClicked);
    connect(m_view, &EventView::viewResized,
            this, &EventPresenter::handleViewResized);
    connect(m_view, &EventView::itemClicked,
            this, &EventPresenter::handleItemClicked);
    connect(m_view, &EventView::zoomChanged,
            this, &EventPresenter::handleWheelZoom);

    // Подключаемся к моделям (если они имеют сигналы)
    // connect(m_system, &CalendarSystem::systemChanged,
    //         this, &EventPresenter::onSystemChanged);
    // connect(m_globalTime, &CustomDateTime::timeChanged,
    //         this, &EventPresenter::refreshEvents);
}

void EventPresenter::refreshEvents()
{
    if (!m_system || !m_view) return;

    LOG(INFO, logger, "Refreshing events, generating visual data");
    // Генерируем визуальные данные
    SceneVisualData visualData = generateVisualData();

    // Обновляем View
    updateView(visualData);
}

SceneVisualData EventPresenter::generateVisualData() const
{
    SceneVisualData data;

    // Генерируем данные контейнеров событий
    data.items = generateContainers();
    data.headerText = generateHeaderText();
    // Генерируем данные дней
    data.items = generateEvents();
    data.headerText = generateHeaderText();
    data.columns = m_columns;
    data.rows = m_rows;
    // Рассчитываем размер ячейки на основе размера View
    if (m_viewSize.isValid()) {
        data.cellSize = QSizeF(m_viewSize.width() / m_columns,
                               m_viewSize.height() / m_rows);
    } else {
        data.cellSize = QSizeF(50, 50); // Размер по умолчанию
    }

    return data;
}

QVector<EventContainerData> EventPresenter::generateContainers() const
{
    QVector<EventContainerData> containers;

    if (!m_system) return containers;


    for (quint16 i = 0; i <= day; ++i) {
        CalendarEventData eventData;
        eventData.day = day;
        eventData.month = m_currentDisplayDate.month();
        eventData.year = m_currentDisplayDate.year();
        eventData.displayText = QString::number(day);
        eventData.isEnabled = m_system->isValidDate(day, eventData.month, eventData.year);
        eventData.isCurrentDay = (day == m_currentDisplayDate.day() &&
                                eventData.month == m_currentDisplayDate.month());
        eventData.isToday = (day == today.day() &&
                           eventData.month == today.month() &&
                           eventData.year == today.year());
        eventData.hasEvents = false; // Здесь можно добавить проверку событий

        // Устанавливаем цвета
        eventData.backgroundColor = getDayColor(eventData);
        eventData.textColor = getTextColor(eventData);
        eventData.borderColor = getBorderColor(eventData);

        days.append(eventData);
    }

    return days;
}

QVector<CalendarEventData> EventPresenter::generateEvents() const
{
    QVector<CalendarEventData> events;

    if (!m_system) return events;

    // Добавляем события
    for(Event event : m_system->fetchEvents(*m_globalTime))
    {
        CalendarEventData eventData;
        eventData.hour = event.time.hour();
        eventData.minute = event.time.minute();
        eventData.second = event.time.second();
        eventData.displayText["name"] = event.name;
        eventData.displayText["text"] = event.text;
        eventData.isEnabled = m_system->isValidTime(event.time.hour(), event.time.minute(), event.time.second());

        // Устанавливаем цвета
        eventData.backgroundColor = getEventColor(eventData);
        eventData.textColor = getTextColor(eventData);
        eventData.borderColor = getBorderColor(eventData);

        events.append(eventData);
    }

    return events;
}


void EventPresenter::updateView(const SceneVisualData& data)
{
    if (!m_view) return;

    // Передаем данные в View
    m_view->displayScene(data);

    // // Можно добавить дополнительные обновления UI
    // emit calendarUpdated(m_currentDisplayDate);
}



// Обработчики внешних событий
void EventPresenter::onSystemChanged()
{
    refreshEvents();
}

void EventPresenter::onSettingsChanged()
{
    refreshEvents();
}

void EventPresenter::onEventsUpdated()
{
    refreshEvents();
}

}

void EventPresenter::handleViewResized(const QSize& size)
{
    m_viewSize = size;
    refreshEvents();
}

void EventPresenter::handleItemClicked(EventItem* item)
{
    if (!item) return;

    // CustomDateTime selectedDate(item->day(), item->month(), item->year());
    // onDateSelected(selectedDate);
}

void EventPresenter::handleWheelZoom(qreal factor)
{
    m_zoomLevel *= factor;
    m_zoomLevel = qBound(0.5, m_zoomLevel, 3.0); // Ограничиваем zoom

    if (m_view) {
        m_view->setZoomLevel(m_zoomLevel);
    }
}

// void EventPresenter::validateCurrentDate()
// {
//     if (!m_system) return;

//     // Проверяем валидность даты в текущей календарной системе
//     if (!m_system->isValidDate(m_currentDisplayDate.day(),
//                                m_currentDisplayDate.month(),
//                                m_currentDisplayDate.year())) {
//         // Корректируем на сегодняшнюю дату
//         if (m_globalTime) {
//             m_currentDisplayDate = CustomDateTime(m_globalTime->day(),
//                                                   m_globalTime->month(),
//                                                   m_globalTime->year());
//         } else {
//             m_currentDisplayDate = CustomDateTime(1, 1, 2000);
//             qDebug() << "EventPresenter::validateCurrentDate"
//         }
//     }
// }

// Методы для визуальных настроек
QColor EventPresenter::getEventColor(const CalendarEventData& eventData) const
{
    if (!eventData.isEnabled) return Qt::lightGray;

    return Qt::blue;
}

QColor EventPresenter::getTextColor(const CalendarEventData& eventData) const
{
    if (!eventData.isEnabled) return Qt::darkGray;
    return Qt::black;
}

QColor EventPresenter::getBorderColor(const CalendarEventData& eventData) const
{
    // if (eventData.isToday) return Qt::red;
    // if (eventData.isCurrentDay) return Qt::blue;
    return Qt::red;
}
