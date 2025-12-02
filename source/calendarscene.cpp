#include "include/calendarscene.h"

CalendarScene::CalendarScene(QObject *parent)
    : AbstractScene(parent)
{
    m_showHeaders["weekdays"] = true;
}

CalendarScene::~CalendarScene()
{
    AbstractScene::~AbstractScene();
}

// void CalendarScene::setupConnections()
// {
//     // Соединения будут устанавливаться при добавлении элементов
// }

void CalendarScene::setSceneData(const SceneVisualData& data)
{
    AbstractScene::setSceneData(data);
    if(!data.headers["weekdays"].isEmpty())
        m_headerTexts["weekdays"] = data.headers["weekdays"];

    if (m_showHeaders["weekdays"]) {
        createHeader("weekdays");
    }
    // Расставляем элементы
    repositionItems();
    // Сцена готова
    emit sceneReady();
}




void CalendarScene::updateLayout()
{
    AbstractScene::updateLayout();
    if (m_headerItems["weekdays"]) {
        m_headerItems["weekdays"]->setVisible(m_showHeaders["weekdays"]);
    }
}

void CalendarScene::repositionItems()
{
    AbstractScene::repositionItems();

    // Место для заголовка дней недели
    if (!m_headerTexts["weekdays"].isEmpty() && m_headerItems["weekdays"])
    {
        m_headerItems["weekdays"]->setPos(0, 0);
    }

}
