#include "include/eventpresenter.h"

EventPresenter::EventPresenter(CalendarSystem* system,
<<<<<<< HEAD
                               CustomDateTime* globalTime,
                               EventView* view,
                               QObject* parent)
=======
                                     CustomDateTime* globalTime,
                                     EventView* view,
                                     QObject* parent)
>>>>>>> main
    : QObject(parent)
    , m_system(system)
    , m_globalTime(globalTime)
    , m_view(view)
    , m_columns(1)
<<<<<<< HEAD
    , m_rows(0)
    , m_zoomLevel(1.0)
{
=======
    , m_rows(system->weeksInMonth(globalTime->month(), globalTime->year()))
    , m_zoomLevel(1.0)
{
    // Устанавливаем начальную дату

>>>>>>> main
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

<<<<<<< HEAD
=======
    // Подключаемся к моделям (если они имеют сигналы)
>>>>>>> main
    // connect(m_system, &CalendarSystem::systemChanged,
    //         this, &EventPresenter::onSystemChanged);
    // connect(m_globalTime, &CustomDateTime::timeChanged,
    //         this, &EventPresenter::refreshCalendar);
}

void EventPresenter::refreshEvents()
{
    if (!m_system || !m_view) return;

<<<<<<< HEAD
    LOG(INFO, logger, "Refreshing events, generating visual data");
=======
>>>>>>> main
    // Генерируем визуальные данные
    EventVisualData visualData = generateVisualData();

    // Обновляем View
    updateView(visualData);
}

EventVisualData EventPresenter::generateVisualData() const
{
    EventVisualData data;

<<<<<<< HEAD
    // Генерируем данные контейнеров событий
    data.items = generateContainers();
    data.headerText = generateHeaderText();
=======
    // Генерируем данные дней
    data.items = generateEvents();
    data.headerText = generateHeaderText();
    data.columns = m_columns;
>>>>>>> main
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

<<<<<<< HEAD
QVector<EventContainerData> EventPresenter::generateContainers() const
{
    QVector<EventContainerData> containers;

    if (!m_system) return containers;


    for (quint16 i = 0; i <= day; ++i) {
        CalendarEventData dayData;
        dayData.day = day;
        dayData.month = m_currentDisplayDate.month();
        dayData.year = m_currentDisplayDate.year();
        dayData.displayText = QString::number(day);
        dayData.isEnabled = m_system->isValidDate(day, dayData.month, dayData.year);
        dayData.isCurrentDay = (day == m_currentDisplayDate.day() &&
                                dayData.month == m_currentDisplayDate.month());
        dayData.isToday = (day == today.day() &&
                           dayData.month == today.month() &&
                           dayData.year == today.year());
        dayData.hasEvents = false; // Здесь можно добавить проверку событий

        // Устанавливаем цвета
        dayData.backgroundColor = getDayColor(dayData);
        dayData.textColor = getTextColor(dayData);
        dayData.borderColor = getBorderColor(dayData);

        days.append(dayData);
    }

    return days;
}

=======
>>>>>>> main
QVector<CalendarEventData> EventPresenter::generateEvents() const
{
    QVector<CalendarEventData> events;

    if (!m_system) return events;

<<<<<<< HEAD

    for (quint16 i = 0; i <= day; ++i) {
=======
    // Получаем информацию о текущем месяце
    quint16 daysInMonth = m_system->currentDay(m_currentDisplayDate.month(),
                                                m_currentDisplayDate.year());

    // Определяем день недели первого дня месяца
    Day *day = m_system.firstDayOfMonth(m_currentDisplayDate.month(), m_currentDisplayDate.year());
    quint16 firstDayOfWeek = day->position; // 1,2 .. x

    // Добавляем пустые дни в начале (для выравнивания)
    for (int i = 1; i < firstDayOfWeek; ++i) {
        CalendarEventData emptyDay;
        emptyDay.isEnabled = false;
        emptyDay.displayText = "";
        days.append(emptyDay);
    }

    // Добавляем дни месяца
    CustomDateTime today = m_globalTime ?
                           CustomDateTime(m_globalTime->day(), m_globalTime->month(), m_globalTime->year()) :
                           CustomDateTime(1, 1, 2000);

    for (quint16 day = 1; day <= daysInMonth; ++day) {
>>>>>>> main
        CalendarEventData dayData;
        dayData.day = day;
        dayData.month = m_currentDisplayDate.month();
        dayData.year = m_currentDisplayDate.year();
        dayData.displayText = QString::number(day);
        dayData.isEnabled = m_system->isValidDate(day, dayData.month, dayData.year);
        dayData.isCurrentDay = (day == m_currentDisplayDate.day() &&
                                dayData.month == m_currentDisplayDate.month());
        dayData.isToday = (day == today.day() &&
                           dayData.month == today.month() &&
                           dayData.year == today.year());
        dayData.hasEvents = false; // Здесь можно добавить проверку событий

        // Устанавливаем цвета
        dayData.backgroundColor = getDayColor(dayData);
        dayData.textColor = getTextColor(dayData);
        dayData.borderColor = getBorderColor(dayData);

        days.append(dayData);
    }

    return days;
}

QString EventPresenter::generateHeaderText() const
{
    // Генерируем заголовок "Месяц Год"
    return QString("%1 %2")
        .arg(m_currentDisplayDate.month())
        .arg(m_currentDisplayDate.year());
}

QString EventPresenter::generateWeekDaysHeader() const
{
    if (!m_system) return "";

    // Генерируем заголовок с днями недели
    QStringList weekDays;
    for (int i = 1; i <= m_columns; ++i) {
<<<<<<< HEAD
        DayOfWeek* dayInfo = m_system->dayOfWeek(i);
=======
        Day* dayInfo = m_system->dayOfWeek(i);
>>>>>>> main
        if (dayInfo) {
            weekDays.append(dayInfo->name.left(2)); // Сокращенные названия
        } else {
            weekDays.append("--");
        }
    }
    return weekDays.join(" ");
}

void EventPresenter::updateView(const EventVisualData& data)
{
    if (!m_view) return;

    // Передаем данные в View
    m_view->displayCalendar(data);

    // // Можно добавить дополнительные обновления UI
    // emit calendarUpdated(m_currentDisplayDate);
}

// Обработчики навигации
void EventPresenter::onNextDay()
{
    if (!m_globalTime) return;

    m_globalTime->addDays(1);
    m_currentDisplayDate = m_currentDisplayDate.addDays(1);
    refreshCalendar();
}

void EventPresenter::onPrevDay()
{
    if (!m_globalTime) return;

    m_globalTime->addDays(-1);
    m_currentDisplayDate = m_currentDisplayDate.addDays(-1);
    refreshCalendar();
}

void EventPresenter::onNextMonth()
{
    m_currentDisplayDate = m_currentDisplayDate.addMonths(1);
    validateCurrentDate();
    refreshCalendar();
}

void EventPresenter::onPrevMonth()
{
    m_currentDisplayDate = m_currentDisplayDate.addMonths(-1);
    validateCurrentDate();
    refreshCalendar();
}

void EventPresenter::onToday()
{
    if (m_globalTime) {
        m_currentDisplayDate = CustomDateTime(m_globalTime->day(),
                                              m_globalTime->month(),
                                              m_globalTime->year());
    } else {
        m_currentDisplayDate = CustomDateTime(1, 1, 2000);
    }
    refreshCalendar();
}

void EventPresenter::onDateSelected(const CustomDateTime& date)
{
    if (!date.isValid()) return;

    m_currentDisplayDate = date;

    // Обновляем глобальное время, если нужно
    if (m_globalTime && m_system) {
        if (m_system->isValidDate(date.day(), date.month(), date.year())) {
            m_globalTime->setDate(date.day(), date.month(), date.year());
        }
    }

    refreshCalendar();
}

// Обработчики внешних событий
void EventPresenter::onSystemChanged()
{
    refreshCalendar();
}

void EventPresenter::onSettingsChanged()
{
    refreshCalendar();
}

void EventPresenter::onEventsUpdated()
{
    refreshCalendar();
}

// Обработчики сигналов от View
void EventPresenter::handleDateClicked(const CustomDateTime& date)
{
    onDateSelected(date);
}

void EventPresenter::handleViewResized(const QSize& size)
{
    m_viewSize = size;
    refreshCalendar();
}

void EventPresenter::handleItemClicked(EventItem* item)
{
    if (!item) return;

    CustomDateTime selectedDate(item->day(), item->month(), item->year());
    onDateSelected(selectedDate);
}

void EventPresenter::handleWheelZoom(qreal factor)
{
    m_zoomLevel *= factor;
    m_zoomLevel = qBound(0.5, m_zoomLevel, 3.0); // Ограничиваем zoom

    if (m_view) {
        m_view->setZoomLevel(m_zoomLevel);
    }
}

void EventPresenter::validateCurrentDate()
{
    if (!m_system) return;

    // Проверяем валидность даты в текущей календарной системе
    if (!m_system->isValidDate(m_currentDisplayDate.day(),
                               m_currentDisplayDate.month(),
                               m_currentDisplayDate.year())) {
        // Корректируем на сегодняшнюю дату
        if (m_globalTime) {
            m_currentDisplayDate = CustomDateTime(m_globalTime->day(),
                                                  m_globalTime->month(),
                                                  m_globalTime->year());
        } else {
            m_currentDisplayDate = CustomDateTime(1, 1, 2000);
            qDebug() << "EventPresenter::validateCurrentDate"
        }
    }
}

// Методы для визуальных настроек
QColor EventPresenter::getDayColor(const CalendarEventData& dayData) const
{
    if (!dayData.isEnabled) return Qt::lightGray;
    if (dayData.isToday) return QColor(255, 255, 200); // светло-желтый
    if (dayData.isCurrentDay) return QColor(200, 230, 255); // светло-голубой
    if (dayData.hasEvents) return QColor(255, 230, 200); // светло-оранжевый

    return Qt::white;
}

QColor EventPresenter::getTextColor(const CalendarEventData& dayData) const
{
    if (!dayData.isEnabled) return Qt::darkGray;
    return Qt::black;
}

QColor EventPresenter::getBorderColor(const CalendarEventData& dayData) const
{
    if (dayData.isToday) return Qt::red;
    if (dayData.isCurrentDay) return Qt::blue;
    return Qt::gray;
}
