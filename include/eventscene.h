#ifndef EVENTSCENE_H
#define EVENTSCENE_H

#include <QGraphicsScene>
#include <QObject>
#include "eventitem.h"
#include "structs.h"
#include "abstractscene.h"


class EventScene : public AbstractScene
{
    Q_OBJECT

public:
public:
    explicit EventScene(QObject *parent = nullptr);
    virtual void setSceneData(const SceneVisualData &data) override;

public slots:
    virtual void updateLayout() override;

private:
    void repositionItems();

};

#endif // EVENTSCENE_H
