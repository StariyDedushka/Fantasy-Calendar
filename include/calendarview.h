#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

#include <QGraphicsView>
#include "calendarscene.h"

enum CalendarViewMode { Days, Months, Years };

class CalendarView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit CalendarView(QWidget *parent = nullptr);

    // Управление отображением
    void setZoomLevel(qreal level);
    void fitToView();
    void setViewMode(CalendarViewMode mode); // month/week/day
    void displayCalendar(const CalendarVisualData& data);

public slots:
    void onDataReady(const CalendarVisualData& data);

signals:
    void dateClicked(const QDate& date);
    void viewResized(const QSize& size);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    CalendarScene *m_scene;
    qreal m_zoomLevel;
};

#endif // CALENDARVIEW_H
