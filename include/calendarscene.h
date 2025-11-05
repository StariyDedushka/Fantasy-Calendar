#ifndef CALENDARSCENE_H
#define CALENDARSCENE_H

#include <QGraphicsScene>
#include "calendaritem.h"

class CalendarScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CalendarScene(QObject *parent = nullptr);

    // Чисто графические методы
    void setupCalendarLayout(const QSizeF& cellSize, int columns, int rows);
    void addCalendarDay(const CalendarDayData& dayData, const QPointF& position);
    void setVisualStyle(const CalendarVisualStyle& style);

signals:
    void dayItemClicked(CalendarItem* item);

private slots:
    void onItemSelected(CalendarItem* item);

private:
    QVector<CalendarItem*> m_items;
    CalendarVisualStyle m_style;
};

#endif // CALENDARSCENE_H
