#ifndef ABSTRACTSCENE_H
#define ABSTRACTSCENE_H

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
    void setHeaderVisible(const QString& key, bool visible);

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
    virtual void repositionItems() = 0;
    // Общий метод для создания всех заголовков
    virtual void createHeader(const QString& key);

    QVector<ItemData*> m_dataItems;
    QVector<AbstractItem*> m_items;

    // Следующий сегмент позволяет свободно расширять количество заголовков на сцене
    // С помощью карты можно именовать заголовки и вызывать прямо в коде
    // Отображение заголовков
    QMap<QString, bool> m_showHeaders;
    // Тексты заголовков
    QMap<QString, QString> m_headerTexts;
    // Графические элементы заголовков
    QMap<QString, QGraphicsTextItem*> m_headerItems;

private:
    QSizeF m_cellSize;
    quint16 m_columns;
    quint16 m_rows;
    QColor m_backgroundColor;

};

#endif // ABSTRACTSCENE_H

