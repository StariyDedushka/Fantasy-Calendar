#include "include/calendarpresenter.h"
#include <QDebug>

CalendarPresenter::CalendarPresenter(CalendarSystem* system,
                                     CustomDateTime* globalTime,
                                     CalendarView* view,
                                     QObject* parent)
    : QObject(parent)
    , m_system(system)
    , m_globalTime(globalTime)
    , m_view(view)
    , m_scene(nullptr)
{
    // Используем текущую дату из globalTime как начальную
    if (m_globalTime && m_system) {
        m_currentDisplayDate = QDate(m_globalTime->year(),
                                     m_globalTime->month(),
                                     m_globalTime->day());
    } else {
        m_currentDisplayDate = CustomDateTime(1, 1, 1);    }

    initialize();
}

CalendarPresenter::~CalendarPresenter()
{
    // Presenter не владеет моделями и вьюхами, только очищает свои связи
    if (m_scene) {
        m_scene->disconnect(this);
    }
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

    // Создаем сцену (View компонент)
    m_scene = new CalendarScene(); // Без передачи моделей!
    m_view->setScene(m_scene);

    // Настраиваем соединения
    setupConnections();

    // Первоначальная загрузка данных
    refreshCalendar();
}

void CalendarPresenter::setupConnections()
{
    if (!m_view || !m_scene) return;

    // Подключаем сигналы от View
    connect(m_view, &CalendarView::dateSelected,
            this, &CalendarPresenter::onDateSelected);
    connect(m_view, &CalendarView::navigationRequested,
            this, [this](int days) {
                if (days > 0) this->onNextDay();
                else this->onPrevDay();
            });
    connect(m_view, &CalendarView::windowResized,
            this, &CalendarPresenter::handleViewResized);

    // Подключаем сигналы от Scene
    connect(m_scene, &CalendarScene::itemClicked,
            this, &CalendarPresenter::handleItemClicked);

    // Подключаем сигналы от Model (если они есть)
    if (m_system) {
        // connect(m_system, &CalendarSystem::systemChanged,
        //         this, &CalendarPresenter::onSystemTimeChanged);
    }
}

void CalendarPresenter::refreshCalendar()
{
    if (!m_system || !m_scene) return;

    // Генерируем данные для отображения
    CalendarDisplayData data = generateCalendarData();

    // Обновляем View
    updateView(data);
}

CalendarDisplayData CalendarPresenter::generateCalendarData() const
{
    CalendarDisplayData data;
    data.currentDate = m_currentDisplayDate;
    data.isValid = m_system->isValidDate(m_currentDisplayDate.day(),
                                         m_currentDisplayDate.month(),
                                         m_currentDisplayDate.year());

    // Генерация календарных элементов для текущего месяца
    quint16 daysInMonth = m_system->daysInMonth(m_currentDisplayDate.month(),
                                                m_currentDisplayDate.year());

    // Создаем элементы календаря
    for (quint16 day = 1; day <= daysInMonth; ++day) {
        QRectF rect(0, 0, 50, 50); // Размеры будут настроены в Scene
        CalendarItem* item = new CalendarItem(rect,
                                              QString::number(day),
                                              Qt::white, Qt::gray, Qt::blue,
                                              true, day,
                                              m_currentDisplayDate.month(),
                                              m_currentDisplayDate.year());
        data.items.append(item);
    }

    // Устанавливаем заголовок
    data.monthYearHeader = QString("%1 %2")
                               .arg(m_currentDisplayDate.month())
                               .arg(m_currentDisplayDate.year());

    return data;
}

void CalendarPresenter::updateView(const CalendarDisplayData& data)
{
    if (!m_scene) return;

    // Передаем данные в Scene для отображения
    m_scene->setCalendarData(data.items, data.monthYearHeader);

    // Можно добаditional логику обновления UI
    emit calendarUpdated(data.currentDate, data.isValid);
}

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
        m_currentDisplayDate = QDate(m_globalTime->year(),
                                     m_globalTime->month(),
                                     m_globalTime->day());
    } else {
        m_currentDisplayDate = QDate::currentDate();
    }
    refreshCalendar();
}

void CalendarPresenter::onDateSelected(const QDate& date)
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

void CalendarPresenter::onSystemTimeChanged()
{
    // Реакция на изменения в системе календаря
    if (m_globalTime) {
        m_currentDisplayDate = QDate(m_globalTime->year(),
                                     m_globalTime->month(),
                                     m_globalTime->day());
    }
    refreshCalendar();
}

void CalendarPresenter::handleViewResized(quint16 width, quint16 height)
{
    Q_UNUSED(width)
    Q_UNUSED(height)
    // Перенастраиваем отображение при изменении размера
    refreshCalendar();
}

void CalendarPresenter::handleItemClicked(AbstractItem* item)
{
    CalendarItem* calendarItem = qobject_cast<CalendarItem*>(item);
    if (calendarItem) {
        QDate selectedDate(calendarItem->year(),
                           calendarItem->month(),
                           calendarItem->day());
        onDateSelected(selectedDate);
    }
}

void CalendarPresenter::validateCurrentDate()
{
    if (!m_system) return;

    // Проверяем, что текущая дата валидна в системе календаря
    if (!m_system->isValidDate(m_currentDisplayDate.day(),
                               m_currentDisplayDate.month(),
                               m_currentDisplayDate.year())) {
        // Корректируем дату если нужно
        m_currentDisplayDate = QDate::currentDate();
    }
}
