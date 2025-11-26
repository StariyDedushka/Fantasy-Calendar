#ifndef CALENDARSCENE_H
#define CALENDARSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include "eventitem.h"
#include "common/calendarstructures.h"


class EventScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit EventScene(QObject *parent = nullptr);
    ~EventScene();

    // Основной метод для установки данных
    void setEventData(const EventVisualData& data);

    // Очистка сцены
    void clearEvents();

    // Настройки отображения
    void setCellSize(const QSizeF& size);
    void setGridSize(quint16 columns, quint16 rows);
    void setBackgroundColor(const QColor& color);
    void setHeaderVisible(bool visible);

    // Получение элементов
    QVector<EventItem*> items() const { return m_eventItems; }
    EventItem* itemAtPos(const QPointF& pos) const;

signals:
    void itemClicked(EventItem* item);
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

    QVector<EventItem*> m_eventItems;
    QSizeF m_cellSize;
    quint16 m_columns;
    quint16 m_rows;
    QString m_headerText;
    QColor m_backgroundColor;
    bool m_showHeader;

    // Графические элементы заголовков
    QGraphicsTextItem* m_headerItem;
};

#endif // CALENDARSCENE_H
