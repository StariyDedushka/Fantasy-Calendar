#ifndef EVENTVIEW_H
#define EVENTVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include "eventscene.h"


class EventScene;
struct CalendarVisualData;

class EventView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit EventView(QWidget *parent = nullptr);
    ~EventView();

    // Основной метод для отображения календаря
    void displayEvents(const EventVisualData& data);

    // Управление отображением
    void setZoomLevel(qreal level);
    void fitToView();
    void setInteractive(bool interactive);

    // Настройки View
    void setAntialiasingEnabled(bool enabled);
    void setViewportUpdateMode(ViewportUpdateMode mode);

public slots:
    void clearCalendar();
    void updateView();

signals:
    // Сигналы пользовательских действий
    void dateClicked(CustomDa);
    void viewResized(const QSize& size);
    void zoomChanged(qreal zoomLevel);
    void itemClicked(EventItem *item);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void handleSceneItemClicked(class EventItem* item);

private:
    void setupView();
    void calculateOptimalZoom();

    EventScene *m_scene;
    qreal m_zoomLevel;
    bool m_isPanning;
    QPoint m_panStartPos;
};

#endif // EVENTVIEW_H
