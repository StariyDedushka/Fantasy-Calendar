#include "include/abstractview.h"

AbstractView::AbstractView(QWidget *parent)
    : QGraphicsView(parent)
    , m_zoomLevel(1.0)
    , m_isPanning(false)
{
    setupView();

    // Подключаем сигналы от сцены
    connect(m_scene, &AbstractScene::itemClicked,
            this, &AbstractView::handleSceneItemClicked);
}

AbstractView::~AbstractView()
{
}

void AbstractView::setupView()
{
    // Настройки рендеринга
    setRenderHint(QPainter::Antialiasing, true);
    setRenderHint(QPainter::TextAntialiasing, true);
    setRenderHint(QPainter::SmoothPixmapTransform, true);

    // Настройки View
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setDragMode(QGraphicsView::RubberBandDrag);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    // Фон
    setBackgroundBrush(QBrush(Qt::lightGray));

    // Оптимизация для большого количества элементов
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setCacheMode(QGraphicsView::CacheBackground);
}

void AbstractView::displayScene(const SceneVisualData& data)
{
    if (!m_scene) return;

    // Передаем данные в сцену
    m_scene->setSceneData(data);

    // Подстраиваем view под содержимое
    QTimer::singleShot(10, this, &AbstractView::fitToView);
}

void AbstractView::setZoomLevel(qreal level)
{
    qreal oldZoom = m_zoomLevel;
    m_zoomLevel = qBound(0.5, level, 3.0); // Ограничиваем zoom

    if (qFuzzyCompare(oldZoom, m_zoomLevel)) return;

    // Применяем трансформацию
    resetTransform();
    scale(m_zoomLevel, m_zoomLevel);

    emit zoomChanged(m_zoomLevel);
}

void AbstractView::fitToView()
{
    if (!m_scene || m_scene->items().isEmpty()) return;

    // Подгоняем view под bounding rect сцены с небольшими отступами
    QRectF sceneRect = m_scene->itemsBoundingRect();
    if (sceneRect.isValid()) {
        sceneRect.adjust(-10, -10, 10, 10); // Небольшие отступы
        fitInView(sceneRect, Qt::KeepAspectRatio);

        // Обновляем уровень zoom
        m_zoomLevel = transform().m11();
    }
}

void AbstractView::setInteractive(bool interactive)
{
    setDragMode(interactive ? QGraphicsView::RubberBandDrag : QGraphicsView::NoDrag);
    setInteractive(interactive);
}

void AbstractView::setAntialiasingEnabled(bool enabled)
{
    setRenderHint(QPainter::Antialiasing, enabled);
    setRenderHint(QPainter::TextAntialiasing, enabled);
}

void AbstractView::clearScene()
{
    if (m_scene) {
        m_scene->clearScene();
    }
}

void AbstractView::updateView()
{
    viewport()->update();
}

void AbstractView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);

    // Сообщаем о изменении размера
    emit viewResized(event->size());

    // Автоподгонка при изменении размера
    if (m_scene && !m_scene->items().isEmpty()) {
        QTimer::singleShot(0, this, &AbstractView::fitToView);
    }
}

void AbstractView::wheelEvent(QWheelEvent *event)
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

void AbstractView::mousePressEvent(QMouseEvent *event)
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

void AbstractView::mouseMoveEvent(QMouseEvent *event)
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

void AbstractView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton && m_isPanning) {
        m_isPanning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }

    QGraphicsView::mouseReleaseEvent(event);
}

// void AbstractView::handleSceneItemClicked(EventItem* item)
// {
//     // if (item && item->isEnabled()) {
//     //     // Пробрасываем сигнал с данными события
//     //     emit itemClicked(item->id());
//     // }
// }

void AbstractView::calculateOptimalZoom()
{
    if (!m_scene || m_scene->items().isEmpty()) return;

    // Автоматический расчет оптимального zoom
    QRectF sceneRect = m_scene->itemsBoundingRect();
    QRectF viewRect = viewport()->rect();

    if (sceneRect.isValid() && viewRect.isValid()) {
        qreal xRatio = viewRect.width() / sceneRect.width();
        qreal yRatio = viewRect.height() / sceneRect.height();
        qreal optimalZoom = qMin(xRatio, yRatio) * 0.9; // 90% для отступов

        setZoomLevel(optimalZoom);
    }
}
