#include "include/eventscene.h"

EventScene::EventScene(QObject *parent)
    : AbstractScene(parent)
{
}



void EventScene::setSceneData(const SceneVisualData& data)
{
    AbstractScene::setSceneData(data);

    // Расставляем ячейки
    repositionItems();
    emit sceneReady();
}


void EventScene::updateLayout()
{
    AbstractScene::updateLayout();
}

void EventScene::repositionItems()
{
    AbstractScene::repositionItems();
}

void EventScene::createHeader(const QString& key)
{
    AbstractScene::createHeader(key);
}
