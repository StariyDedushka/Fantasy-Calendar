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
    virtual void setSceneData(const SceneVisualData &data) override;

public slots:
    virtual void updateLayout() override;

private:
    void repositionItems();
};

#endif // CALENDARSCENE_H
