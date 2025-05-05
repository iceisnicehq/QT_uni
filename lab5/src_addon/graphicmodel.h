#ifndef GRAPHICMODEL_H
#define GRAPHICMODEL_H

#include <QObject>
#include <QList>
#include <QUndoStack>
#include "shape.h"
#include "customgraphicsscene.h" // Include to resolve CustomGraphicsScene usage

class GraphicModel : public QObject {
    Q_OBJECT
public:
    explicit GraphicModel(QObject* parent = nullptr);

    void addShape(ShapeType type, const QPointF& startPos, const QColor& color);
    void removeShape(Shape* shape);
    void clear();

    void addShapeWithUndo(ShapeType type, const QPointF& startPos, const QColor& color, QUndoStack* undoStack);
    void removeShapeWithUndo(Shape* shape, QUndoStack* undoStack);
    void clearWithUndo(QUndoStack* undoStack);

    QList<Shape*>& getShapes();         // non-const reference
    QList<Shape*> getShapes() const;    // const copy

    CustomGraphicsScene* getScene() const;

signals:
    void sceneUpdated();

private:
    CustomGraphicsScene* scene;
    QList<Shape*> shapes;
};

#endif // GRAPHICMODEL_H
