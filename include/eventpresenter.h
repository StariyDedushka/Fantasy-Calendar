<<<<<<< HEAD
#ifndef EVENTPRESENTER_H
#define EVENTPRESENTER_H
=======
#ifndef CALENDARPRESENTER_H
#define CALENDARPRESENTER_H
>>>>>>> main

#include <QObject>
#include <QSize>
#include "calendarsystem.h"
#include "customdatetime.h"
#include "eventvisualstyle.h"
<<<<<<< HEAD
=======
#include "eventitem.h"
>>>>>>> main
#include "eventview.h"
#include "global_logger.h"

// #include "common/calendarstructures.h"


class EventPresenter : public QObject
{
    Q_OBJECT

public:
    explicit EventPresenter(CalendarSystem* system,
<<<<<<< HEAD
                            CustomDateTime* globalTime,
                            EventView* view,
                            QObject* parent = nullptr);
=======
                           CustomDateTime* globalTime,
                           EventView* view,
                           QObject* parent = nullptr);
>>>>>>> main
    ~EventPresenter();

    void initialize();
    void refreshEvents();

public slots:
    void onNextDay();
    void onPrevDay();
    // void onDateSelected(const CustomDateTime& date);

    // Обработка внешних событий
    void onSystemChanged();
    void onSettingsChanged();
    void onEventsUpdated();

private slots:
    // Обработка сигналов от View
    void handleViewResized(const QSize& size);
    void handleItemClicked(EventItem* item);
    void handleWheelZoom(qreal factor);

private:
    void setupConnections();
    EventVisualData generateVisualData() const;
    void updateView(const EventVisualData& data);
    void validateCurrentDate();
    void calculateGridSize();
<<<<<<< HEAD
    QVector<EventContainerData> generateContainers() const;
    QVector<CalendarEventData> generateEvents() const;
=======
    QVector<CalendarEventData> generateEvents() const;
    QString generateHeaderText() const;
    QString generateWeekDaysHeader() const;
>>>>>>> main
    // Методы для работы со стилями
    void applyVisualStyle();
    void updateColorsFromSettings();

    // Визуальные настройки
<<<<<<< HEAD
    QColor getEventColor(const CalendarEventData& dayData) const;
=======
    QColor getDayColor(const CalendarEventData& dayData) const;
>>>>>>> main
    QColor getTextColor(const CalendarEventData& dayData) const;
    QColor getBorderColor(const CalendarEventData& dayData) const;

    CalendarSystem* m_system;
    CustomDateTime* m_globalTime;
    EventView* m_view;
    // Визуальные настройки
    EventVisualStyle m_visualStyle;

    QSize m_viewSize;
    quint16 m_columns;
    quint16 m_rows;
    qreal m_zoomLevel;
};

<<<<<<< HEAD
#endif // EVENTPRESENTER_H
=======
#endif // CALENDARPRESENTER_H
>>>>>>> main
