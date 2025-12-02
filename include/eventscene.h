#ifndef CALENDARSCENE_H
#define CALENDARSCENE_H

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
    ~EventScene();
    virtual void setSceneData(const SceneVisualData &data) override;

public slots:
    virtual void updateLayout() override;

private:
    void repositionItems();
    virtual void createHeader(const QString& key) override;

};

#endif // CALENDARSCENE_H
