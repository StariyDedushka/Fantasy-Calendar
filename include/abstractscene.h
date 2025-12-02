#ifndef ABSTRACTPAINTER_H
#define ABSTRACTPAINTER_H

#include <QObject>
#include <QGraphicsScene>
#include <QtDebug>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include "abstractitem.h"
#include "structs.h"


class AbstractScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit AbstractScene(QObject *parent = nullptr);
    ~AbstractScene();

    // Основной метод для установки данных
    virtual void setSceneData(const SceneVisualData& data) = 0;

    // Очистка сцены
    void clearScene();

    // Настройки отображения
    void setCellSize(const QSizeF& size);
    void setGridSize(quint16 columns, quint16 rows);
    void setBackgroundColor(const QColor& color);
    void setHeaderVisible(bool visible);

    // Получение элементов
    QVector<AbstractItem*> items() const { return m_items; }
    AbstractItem* itemAtPos(const QPointF& pos) const;

signals:
    void itemClicked(AbstractItem* item);
    void sceneReady();

public slots:
    virtual void updateLayout() = 0;
    void highlightItem(quint32 id);
    void clearHighlights();

protected slots:
    void handleItemClick(AbstractItem* item);

protected:
    void setupConnections();
    void repositionItems();
    void createHeader();
    void createWeekDaysHeader();

    QVector<ItemData*> m_dataItems;
    QVector<AbstractItem*> m_items;

private:
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

#endif // ABSTRACTPAINTER_H
