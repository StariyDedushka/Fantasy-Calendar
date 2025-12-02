#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QWidget>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QScrollBar>
#include <QTimer>
#include "abstractitem.h"
#include "abstractscene.h"


struct SceneVisualData;

class AbstractView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit AbstractView(QWidget *parent = nullptr);
    ~AbstractView();

    // Основной метод для отображения календаря
    virtual void displayScene(const SceneVisualData& data) = 0;

    // Управление отображением
    void setZoomLevel(qreal level);
    void fitToView();
    void setInteractive(bool interactive);

    // Настройки View
    void setAntialiasingEnabled(bool enabled);
    void setViewportUpdateMode(ViewportUpdateMode mode);

public slots:
    void clearScene();
    void updateView();

signals:
    // Сигналы пользовательских действий
    void viewResized(const QSize& size);
    void zoomChanged(qreal zoomLevel);
    void itemClicked(AbstractItem *item);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    virtual void handleSceneItemClicked(AbstractItem* item);

private:
    void setupView();
    void calculateOptimalZoom();

protected:
    AbstractScene *m_scene;
    qreal m_zoomLevel;
    bool m_isPanning;
    QPoint m_panStartPos;
};

#endif // ABSTRACTVIEW_H
