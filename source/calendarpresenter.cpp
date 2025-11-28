#include "include/calendarpresenter.h"

CalendarPresenter::CalendarPresenter(CalendarSystem* system,
                                     CustomDateTime* globalTime,
                                     CalendarView* view,
                                     QObject* parent)
    : QObject(parent)
    , m_system(system)
    , m_globalTime(globalTime)
    , m_view(view)
    , m_columns(system->daysInWeek())
    , m_rows(system->weeksInMonth(globalTime->month(), globalTime->year()))
    , m_zoomLevel(1.0)
{
    // Устанавливаем начальную дату
    if (m_globalTime && m_system) {
        m_currentDisplayDate = *m_globalTime;
    } else {
        m_currentDisplayDate = CustomDateTime(1, 1, 2000);
    }

    initialize();
}

CalendarPresenter::~CalendarPresenter()
{
    // Отключаем все соединения
    if (m_view) {
        m_view->disconnect(this);
    }
}

void CalendarPresenter::initialize()
{
    if (!m_view || !m_system || !m_globalTime) {
        qWarning() << "CalendarPresenter: Missing dependencies";
        return;
    }

    // Настраиваем соединения
    setupConnections();

    // Первоначальная загрузка данных
    refreshCalendar();
}

void CalendarPresenter::setupConnections()
{
    if (!m_view || !m_system || !m_globalTime) return;

    // Подключаем сигналы от View
    connect(m_view, &CalendarView::dateClicked,
            this, &CalendarPresenter::handleDateClicked);
    connect(m_view, &CalendarView::viewResized,
            this, &CalendarPresenter::handleViewResized);
    connect(m_view, &CalendarView::itemClicked,
            this, &CalendarPresenter::handleItemClicked);
    connect(m_view, &CalendarView::zoomChanged,
            this, &CalendarPresenter::handleWheelZoom);

    // Подключаемся к моделям (если они имеют сигналы)
    // connect(m_system, &CalendarSystem::systemChanged,
    //         this, &CalendarPresenter::onSystemChanged);
    // connect(m_globalTime, &CustomDateTime::timeChanged,
    //         this, &CalendarPresenter::refreshCalendar);
}

void CalendarPresenter::refreshCalendar()
{
    if (!m_system || !m_view) return;

    // Генерируем визуальные данные
    CalendarVisualData visualData = generateVisualData();

    // Обновляем View
    updateView(visualData);
}

CalendarVisualData CalendarPresenter::generateVisualData() const
{
    CalendarVisualData data;

    // Генерируем данные дней
    data.items = generateMonthDays();
    data.headerText = generateHeaderText();
    data.weekDaysHeader = generateWeekDaysHeader();
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

QVector<CalendarDayData> CalendarPresenter::generateMonthDays() const
{
    QVector<CalendarDayData> days;

    if (!m_system) return days;

    // Получаем информацию о текущем месяце
    quint16 daysInMonth = m_system->daysInMonth(m_currentDisplayDate.month(),
                                                m_currentDisplayDate.year());

    // Определяем день недели первого дня месяца
    DayOfWeek *day = m_system->firstDayOfMonth(m_currentDisplayDate.month(), m_currentDisplayDate.year());
    quint16 firstDayOfWeek = day->position; // 1,2 .. x

    // Добавляем пустые дни в начале (для выравнивания)
    for (int i = 1; i < firstDayOfWeek; ++i) {
        CalendarDayData emptyDay;
        emptyDay.isEnabled = false;
        emptyDay.displayText = "";
        days.append(emptyDay);
    }

    // Добавляем дни месяца
    CustomDateTime today = m_globalTime ?
                           CustomDateTime(m_globalTime->day(), m_globalTime->month(), m_globalTime->year()) :
                           CustomDateTime(1, 1, 2000);

    for (quint16 day = 1; day <= daysInMonth; ++day) {
        CalendarDayData dayData;
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

QString CalendarPresenter::generateHeaderText() const
{
    // Генерируем заголовок "Месяц Год"
    return QString("%1 %2")
        .arg(m_currentDisplayDate.month())
        .arg(m_currentDisplayDate.year());
}

QString CalendarPresenter::generateWeekDaysHeader() const
{
    if (!m_system) return "";

    // Генерируем заголовок с днями недели
    QStringList weekDays;
    for (int i = 1; i <= m_columns; ++i) {
        DayOfWeek* dayInfo = m_system->dayOfWeek(i);
        if (dayInfo) {
            weekDays.append(dayInfo->name.left(2)); // Сокращенные названия
        } else {
            weekDays.append("--");
        }
    }
    return weekDays.join(" ");
}

void CalendarPresenter::updateView(const CalendarVisualData& data)
{
    if (!m_view) return;

    // Передаем данные в View
    m_view->displayCalendar(data);

    // // Можно добавить дополнительные обновления UI
    // emit calendarUpdated(m_currentDisplayDate);
}

// Обработчики навигации
void CalendarPresenter::onNextDay()
{
    if (!m_globalTime) return;

    m_globalTime->addDays(1);
    m_currentDisplayDate = m_currentDisplayDate.addDays(1);
    refreshCalendar();
}

void CalendarPresenter::onPrevDay()
{
    if (!m_globalTime) return;

    m_globalTime->addDays(-1);
    m_currentDisplayDate = m_currentDisplayDate.addDays(-1);
    refreshCalendar();
}

void CalendarPresenter::onNextMonth()
{
    m_currentDisplayDate = m_currentDisplayDate.addMonths(1);
    validateCurrentDate();
    refreshCalendar();
}

void CalendarPresenter::onPrevMonth()
{
    m_currentDisplayDate = m_currentDisplayDate.addMonths(-1);
    validateCurrentDate();
    refreshCalendar();
}

void CalendarPresenter::onToday()
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

void CalendarPresenter::onDateSelected(const CustomDateTime& date)
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
void CalendarPresenter::onSystemChanged()
{
    refreshCalendar();
}

void CalendarPresenter::onSettingsChanged()
{
    refreshCalendar();
}

void CalendarPresenter::onEventsUpdated()
{
    refreshCalendar();
}

// Обработчики сигналов от View
void CalendarPresenter::handleDateClicked(const CustomDateTime& date)
{
    onDateSelected(date);
}

void CalendarPresenter::handleViewResized(const QSize& size)
{
    m_viewSize = size;
    refreshCalendar();
}

void CalendarPresenter::handleItemClicked(CalendarItem* item)
{
    if (!item) return;

    CustomDateTime selectedDate(item->day(), item->month(), item->year());
    onDateSelected(selectedDate);
}

void CalendarPresenter::handleWheelZoom(qreal factor)
{
    m_zoomLevel *= factor;
    m_zoomLevel = qBound(0.5, m_zoomLevel, 3.0); // Ограничиваем zoom

    if (m_view) {
        m_view->setZoomLevel(m_zoomLevel);
    }
}

void CalendarPresenter::validateCurrentDate()
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
            qDebug() << "CalendarPresenter::validateCurrentDate"
        }
    }
}

// Методы для визуальных настроек
QColor CalendarPresenter::getDayColor(const CalendarDayData& dayData) const
{
    if (!dayData.isEnabled) return Qt::lightGray;
    if (dayData.isToday) return QColor(255, 255, 200); // светло-желтый
    if (dayData.isCurrentDay) return QColor(200, 230, 255); // светло-голубой
    if (dayData.hasEvents) return QColor(255, 230, 200); // светло-оранжевый

    return Qt::white;
}

QColor CalendarPresenter::getTextColor(const CalendarDayData& dayData) const
{
    if (!dayData.isEnabled) return Qt::darkGray;
    return Qt::black;
}

QColor CalendarPresenter::getBorderColor(const CalendarDayData& dayData) const
{
    if (dayData.isToday) return Qt::red;
    if (dayData.isCurrentDay) return Qt::blue;
    return Qt::gray;
}
