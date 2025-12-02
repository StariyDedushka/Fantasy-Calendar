#include "include/eventview.h"

EventView::EventView(QWidget *parent)
    : AbstractView(parent)
    // , m_scene(new EventScene(this))
    // , m_zoomLevel(1.0)
    // , m_isPanning(false)
{
    m_scene = new EventScene(this);
    m_zoomLevel = 1.0;
    m_isPanning = false;
    setScene(m_scene);

    // Подключаем сигналы от сцены
    // connect(m_scene, &EventScene::itemClicked,
    //         this, &EventView::handleSceneItemClicked);
}


void EventView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        // Zoom колесиком мыши с зажатым Ctrl
        qreal zoomFactor = 1.0;
        if (event->angleDelta().y() > 0) {
            zoomFactor = 1.1; // Увеличить
        } else {
            zoomFactor = 0.9; // Уменьшить
        }

        setZoomLevel(m_zoomLevel * zoomFactor);
        event->accept();
    } else {
        // Стандартная прокрутка
        QGraphicsView::wheelEvent(event);
    }
}

void EventView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        // Включение панорамирования
        m_isPanning = true;
        m_panStartPos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }

    QGraphicsView::mousePressEvent(event);
}

void EventView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPanning) {
        // Панорамирование
        QScrollBar *hBar = horizontalScrollBar();
        QScrollBar *vBar = verticalScrollBar();
        QPoint delta = event->pos() - m_panStartPos;
        m_panStartPos = event->pos();

        hBar->setValue(hBar->value() - delta.x());
        vBar->setValue(vBar->value() - delta.y());
        event->accept();
        return;
    }

    QGraphicsView::mouseMoveEvent(event);
}

void EventView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton && m_isPanning) {
        m_isPanning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }

    QGraphicsView::mouseReleaseEvent(event);
}
