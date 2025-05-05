#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

// Forward declare GraphicController to break circular dependency
class GraphicController;

class CustomGraphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit CustomGraphicsScene(QObject *parent = nullptr);

    void setController(GraphicController* ctrl);
    GraphicController* getController() const { return controller; }

signals:
    void sceneMousePressed(const QPointF &pos);
    void sceneMouseMoved(const QPointF &pos);
    void sceneMouseReleased();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    GraphicController* controller;
};

#endif // CUSTOMGRAPHICSSCENE_H
