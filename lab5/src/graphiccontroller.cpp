#include "graphiccontroller.h"
#include <QInputDialog>

GraphicController::GraphicController(GraphicModel* model, QObject* parent)
    : QObject(parent), model(model), currentMode(EditorMode::Select),
      currentColor(Qt::black), currentShape(nullptr), isDrawing(false),
      isMoving(false), selectedShape(nullptr) {}

void GraphicController::setEditorMode(EditorMode mode) {
    currentMode = mode;
}

void GraphicController::setCurrentColor(const QColor& color) {
    currentColor = color;
}

void GraphicController::setCurrentText(const QString& text) {
    currentText = text;
}

QColor GraphicController::getCurrentColor() const {
    return currentColor;
}

void GraphicController::changeSelectedItemsColor(const QColor& color) {
    for (Shape* shape : model->getShapes()) {
        if (shape->isSelected()) {
            shape->setColor(color);
        }
    }
}

void GraphicController::mousePressed(const QPointF& pos) {
    if (currentMode == EditorMode::Select) {
        QList<QGraphicsItem*> items = model->getScene()->items(pos);
        for (QGraphicsItem* item : items) {
            Shape* shape = dynamic_cast<Shape*>(item);
            if (shape) {
                isMoving = true;
                selectedShape = shape;
                return;
            }
        }
    }
    else {
        switch(currentMode) {
        case EditorMode::CreateLine:
            model->addShape(ShapeType::Line, pos, currentColor);
            break;
        case EditorMode::CreateRect:
            model->addShape(ShapeType::Rectangle, pos, currentColor);
            break;
        case EditorMode::CreateEllipse:
            model->addShape(ShapeType::Ellipse, pos, currentColor);
            break;
        case EditorMode::CreateText: {
            bool ok;
            QString text = QInputDialog::getText(nullptr, "Enter Text", "Text:",
                                              QLineEdit::Normal, "", &ok);
            if (ok && !text.isEmpty()) {
                model->addShape(ShapeType::Text, pos, currentColor);
                Shape* shape = model->getShapes().last();
                shape->setText(text);
            }
            return;
        }
        default:
            return;
        }

        currentShape = model->getShapes().last();
        isDrawing = true;
    }
}

void GraphicController::mouseMoved(const QPointF& pos) {
    if (isMoving && selectedShape) {
        selectedShape->setPos(pos - selectedShape->boundingRect().center());
    }
    else if (isDrawing && currentShape) {
        currentShape->setEndPos(pos);
    }
}

void GraphicController::mouseReleased() {
    isDrawing = false;
    isMoving = false;
    currentShape = nullptr;
    selectedShape = nullptr;
}

void GraphicController::deleteSelectedItems() {
    QList<Shape*> toRemove;
    for (Shape* shape : model->getShapes()) {
        if (shape->isSelected()) {
            toRemove.append(shape);
        }
    }

    for (Shape* shape : toRemove) {
        model->removeShape(shape);
    }
}

void GraphicController::clearAll() {
    model->clear();
}
