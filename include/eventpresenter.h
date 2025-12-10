#ifndef EVENTPRESENTER_H
#define EVENTPRESENTER_H

#include <QObject>
#include <QSize>
#include "calendarsystem.h"
#include "customdatetime.h"
#include "eventvisualstyle.h"
#include "eventitem.h"
#include "eventview.h"
#include "global_logger.h"

// #include "common/calendarstructures.h"


class EventPresenter : public QObject
{
    Q_OBJECT

public:
    explicit EventPresenter(CalendarSystem* system,
                            CustomDateTime* globalTime,
                            EventView* view,
                            QObject* parent = nullptr);
    ~EventPresenter();

    void initialize();
    void refreshEvents();

public slots:
    // void onNextDay();
    // void onPrevDay();
    // void onDateSelected(const CustomDateTime& date);

    // Обработка внешних событий
    void onSystemChanged();
    void onSettingsChanged();
    void onEventsUpdated();

private slots:
    // Обработка сигналов от View
    void handleViewResized(const QSize& size);
    void handleItemClicked(AbstractItem* item);
    void handleWheelZoom(qreal factor);

private:
    void setupConnections();
    SceneVisualData generateVisualData() const;
    void updateView(const SceneVisualData& data);
    void validateCurrentDate();
    void calculateGridSize();
    QVector<EventContainerData> generateContainers() const;
    QVector<CalendarEventData> *generateEvents() const;
    QString generateHeaderText() const;
    // Методы для работы со стилями
    void applyVisualStyle();
    void updateColorsFromSettings();

    // Визуальные настройки
    QColor getEventColor(const CalendarEventData& CalendarEventData) const;
    QColor getTextColor(const CalendarEventData& CalendarEventData) const;
    QColor getBorderColor(const CalendarEventData& CalendarEventData) const;

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

#endif // EVENTPRESENTER_H
