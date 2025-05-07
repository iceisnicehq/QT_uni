#ifndef GRAPHICMODEL_H
#define GRAPHICMODEL_H

#include <QObject>
#include <QList>
#include "customgraphicsscene.h"
#include "shape.h"
#include <QStack>

class GraphicModel : public QObject {
    Q_OBJECT
public:
    explicit GraphicModel(QObject* parent = nullptr);

    void addShape(ShapeType type, const QPointF& startPos, const QColor& color);
    void removeShape(Shape* shape);
    void clear();

    QList<Shape*> getShapes() const;
    CustomGraphicsScene* getScene() const;
    void undo();
    void redo();

signals:
    void sceneUpdated();


private:
    CustomGraphicsScene* scene;
    QList<Shape*> shapes;
    QStack<QList<Shape*>> undoStack;
    QStack<QList<Shape*>> redoStack;
};

#endif // GRAPHICMODEL_H
