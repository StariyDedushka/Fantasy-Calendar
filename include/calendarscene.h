#ifndef CALENDARSCENE_H
#define CALENDARSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include "calendaritem.h"
#include "common/calendarstructures.h"


class CalendarScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit CalendarScene(QObject *parent = nullptr);
    ~CalendarScene();

    // Основной метод для установки данных
    void setCalendarData(const CalendarVisualData& data);

    // Очистка сцены
    void clearCalendar();

    // Настройки отображения
    void setCellSize(const QSizeF& size);
    void setGridSize(quint16 columns, quint16 rows);
    void setBackgroundColor(const QColor& color);
    void setHeaderVisible(bool visible);

    // Получение элементов
    QVector<CalendarItem*> items() const { return m_calendarItems; }
    CalendarItem* itemAtPos(const QPointF& pos) const;

signals:
    void itemClicked(CalendarItem* item);
    void sceneReady();

public slots:
    void updateLayout();
    void highlightDate(quint16 day, quint16 month, quint32 year);
    void clearHighlights();

private slots:
    void handleItemClick(AbstractItem* item);

private:
    void setupConnections();
    void repositionItems();
    void createHeader();
    void createWeekDaysHeader();

    QVector<CalendarItem*> m_calendarItems;
    QSizeF m_cellSize;
    quint16 m_columns;
    quint16 m_rows;
    QString m_headerText;
    QString m_weekDaysHeader;
    QColor m_backgroundColor;
    bool m_showHeader;
    bool m_showWeekDays;

    // Графические элементы заголовков
    QGraphicsTextItem* m_headerItem;
    QGraphicsTextItem* m_weekDaysItem;
};

#endif // CALENDARSCENE_H
