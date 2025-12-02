#ifndef CALENDARSCENE_H
#define CALENDARSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include "calendaritem.h"
#include "abstractscene.h"
#include "structs.h"


class CalendarScene : public AbstractScene
{
    Q_OBJECT

public:
    explicit CalendarScene(QObject *parent = nullptr);
    ~CalendarScene();
    virtual setSceneData(const SceneVisualData &data) override;

public slots:
    virtual updateLayout() override;

private:
    void repositionItems();
    void createHeader();
    void createWeekDaysHeader();

    QString m_weekDaysHeader;
    bool m_showWeekDays;

    // Графические элементы заголовков
    QGraphicsTextItem* m_weekDaysItem;
};

#endif // CALENDARSCENE_H
