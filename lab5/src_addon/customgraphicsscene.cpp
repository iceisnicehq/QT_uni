#include "customgraphicsscene.h"
#include "graphiccontroller.h" 

CustomGraphicsScene::CustomGraphicsScene(QObject *parent)
    : QGraphicsScene(parent), controller(nullptr) 
{
}

void CustomGraphicsScene::setController(GraphicController* ctrl) {
    controller = ctrl;
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (controller && controller->getEditorMode() != EditorMode::Select) {
        
        emit sceneMousePressed(event->scenePos());
        return;
    }
    QGraphicsScene::mousePressEvent(event);
    if (!event->isAccepted()) {
        emit sceneMousePressed(event->scenePos());
    }
}

void CustomGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if (!event->isAccepted()) {
        emit sceneMouseMoved(event->scenePos());
    }
}

void CustomGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if (!event->isAccepted()) {
        emit sceneMouseReleased();
    }
}
