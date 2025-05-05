#include "graphicmodel.h"
#include "customgraphicsscene.h"
#include <QUndoCommand>

class AddShapeCommand : public QUndoCommand {
public:
    AddShapeCommand(GraphicModel* model, Shape* shape) 
        : model(model), shape(shape), taken(false) {}
    
    void undo() override {
        if (model->getScene()->items().contains(shape)) {  // Ensure the shape is in the scene before removing
            model->getScene()->removeItem(shape);
            model->getShapes().removeOne(shape);
        }
    }
    
    void redo() override {
        if (!taken) {
            taken = true;
            return;
        }
        if (!model->getScene()->items().contains(shape)) {  // Ensure the shape is not already in the scene
            model->getScene()->addItem(shape);
            model->getShapes().append(shape);
        }
    }
    
private:
    GraphicModel* model;
    Shape* shape;
    bool taken;
};

class RemoveShapeCommand : public QUndoCommand {
public:
    RemoveShapeCommand(GraphicModel* model, Shape* shape)
        : model(model), shape(shape) {}
    
    void undo() override {
        if (!model->getScene()->items().contains(shape)) {
            model->getScene()->addItem(shape); // Re-add to the scene
            model->getShapes().append(shape); // Re-add to the model's shapes list
        }
    }
    
    void redo() override {
        if (model->getScene()->items().contains(shape)) {
            model->getScene()->removeItem(shape); // Remove from the scene
            model->getShapes().removeOne(shape); // Remove from the model's shapes list
        }
    }
    
private:
    GraphicModel* model;
    Shape* shape;
};

class ClearCommand : public QUndoCommand {
public:
    ClearCommand(GraphicModel* model, const QList<Shape*>& shapesInScene)
        : model(model), shapes(shapesInScene) {}

    void undo() override {
        for (Shape* shape : shapes) {
            if (!model->getScene()->items().contains(shape)) {
                model->getScene()->addItem(shape); // Re-add to the scene
                model->getShapes().append(shape); // Re-add to the model's shapes list
            }
        }
    }

    void redo() override {
        for (Shape* shape : shapes) {
            if (model->getScene()->items().contains(shape)) {
                model->getScene()->removeItem(shape); // Remove from the scene
                model->getShapes().removeOne(shape); // Remove from the model's shapes list
            }
        }
    }

private:
    GraphicModel* model;
    QList<Shape*> shapes;
};

class DeleteGroupCommand : public QUndoCommand {
public:
    DeleteGroupCommand(GraphicModel* model, const QList<Shape*>& shapesToDelete)
        : model(model), shapes(shapesToDelete) {}
    
    void undo() override {
        for (Shape* shape : shapes) {
            if (!model->getScene()->items().contains(shape)) {
                model->getScene()->addItem(shape);
            }
            if (!model->getShapes().contains(shape)) {
                model->getShapes().append(shape);
            }
        }
    }

    void redo() override {
        for (Shape* shape : shapes) {
            if (model->getScene()->items().contains(shape)) {
                model->getScene()->removeItem(shape);
            }
            model->getShapes().removeOne(shape);
        }
    }
    
private:
    GraphicModel* model;
    QList<Shape*> shapes;
};

GraphicModel::GraphicModel(QObject* parent) : QObject(parent) {
    scene = new CustomGraphicsScene(this);
    scene->setSceneRect(-500, -500, 1000, 1000);
}

void GraphicModel::addShape(ShapeType type, const QPointF& startPos, const QColor& color) {
    Shape* shape = new Shape(type, startPos, color);
    shapes.append(shape);
    scene->addItem(shape);
    emit sceneUpdated();
}

void GraphicModel::removeShape(Shape* shape) {
    if (shapes.removeOne(shape)) {
        scene->removeItem(shape);
        delete shape;
        emit sceneUpdated();
    }
}

void GraphicModel::clear() {
    for (Shape* shape : shapes) {
        scene->removeItem(shape);
        delete shape;
    }
    shapes.clear();
    emit sceneUpdated();
}

QList<Shape*> GraphicModel::getShapes() const {
    return shapes;
}

CustomGraphicsScene* GraphicModel::getScene() const {
    return scene;
}

void GraphicModel::addShapeWithUndo(ShapeType type, const QPointF& startPos, const QColor& color, QUndoStack* undoStack) {
    Shape* shape = new Shape(type, startPos, color);
    undoStack->push(new AddShapeCommand(this, shape));
    shapes.append(shape);
    scene->addItem(shape);
    emit sceneUpdated();
}

void GraphicModel::removeShapeWithUndo(Shape* shape, QUndoStack* undoStack) {
    if (!shapes.contains(shape)) return;

    shapes.removeOne(shape);
    scene->removeItem(shape);
    undoStack->push(new RemoveShapeCommand(this, shape));
    emit sceneUpdated();
}

void GraphicModel::clearWithUndo(QUndoStack* undoStack) {
    if (shapes.isEmpty()) return;

    QList<Shape*> shapesToRemove = shapes; // Preserve the order of shapes
    undoStack->push(new ClearCommand(this, shapesToRemove));
    for (Shape* shape : shapesToRemove) {
        scene->removeItem(shape);
    }
    shapes.clear();
    emit sceneUpdated();
}
QList<Shape*>& GraphicModel::getShapes() {
    return shapes;
}

