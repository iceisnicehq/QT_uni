#include "graphiccontroller.h"
#include "graphicmodel.h"
#include "customgraphicsscene.h"
#include "commands.h" // Include to use ChangeColorCommand, ChangeFontCommand, and MoveShapeCommand
#include <QInputDialog>

GraphicController::GraphicController(GraphicModel* model, QObject* parent)
    : QObject(parent), model(model), currentMode(EditorMode::Select),
      currentColor(Qt::black), currentShape(nullptr), isDrawing(false),
      isMoving(false), selectedShape(nullptr), lastMovedShape(nullptr) {}

void GraphicController::setEditorMode(EditorMode mode) {
    currentMode = mode;
}

void GraphicController::setCurrentColor(const QColor& color) {
    currentColor = color;
}

void GraphicController::setCurrentText(const QString& text) {
    currentText = text;
}

void GraphicController::setCurrentFont(const QFont& font) {
    currentFont = font;
}

QColor GraphicController::getCurrentColor() const {
    return currentColor;
}

void GraphicController::changeSelectedItemsColor(const QColor& color) {
    for (Shape* shape : model->getShapes()) {
        if (shape->isSelected()) {
            QColor oldColor = shape->getColor();
            undoStack->push(new ChangeColorCommand(shape, oldColor, color));
            shape->setColor(color); // Allow changing color of all shapes
        }
    }
}

void GraphicController::changeSelectedItemsFont(const QFont& font) {
    for (Shape* shape : model->getShapes()) {
        if (shape->isSelected() && shape->getType() == ShapeType::Text) {
            QFont oldFont = shape->getFont();
            undoStack->push(new ChangeFontCommand(shape, oldFont, font));
            shape->setFont(font);
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
                moveStartPos = shape->getStartPos();
                moveEndPos = shape->getEndPos();
                lastMovedShape = shape;
                lastMovedOldPos = shape->getStartPos(); // Not needed anymore, remove this
                return;
            }
        }
    }
    else {
        switch(currentMode) {
        case EditorMode::CreateLine:
        case EditorMode::CreateRect:
        case EditorMode::CreateEllipse:
        case EditorMode::CreateRhombus:
            model->addShapeWithUndo(currentMode == EditorMode::CreateLine ? ShapeType::Line :
                                    currentMode == EditorMode::CreateRect ? ShapeType::Rectangle :
                                    currentMode == EditorMode::CreateEllipse ? ShapeType::Ellipse :
                                    ShapeType::Rhombus, pos, currentColor, undoStack);
            currentShape = model->getShapes().last();
            isDrawing = true;
            break;
        case EditorMode::CreateText: {
            bool ok;
            QString text = QInputDialog::getText(nullptr, "Enter Text", "Text:",
                                              QLineEdit::Normal, "", &ok);
            if (ok && !text.isEmpty()) {
                model->addShapeWithUndo(ShapeType::Text, pos, currentColor, undoStack);
                Shape* shape = model->getShapes().last();
                shape->setText(text);
                shape->setFont(currentFont);
            }
            return;
        }
        }
    }
}

void GraphicController::mouseMoved(const QPointF& pos) {
    if (isMoving && selectedShape) {
        QPointF delta = pos - selectedShape->boundingRect().center();
        selectedShape->setStartPos(moveStartPos + delta);
        selectedShape->setEndPos(moveEndPos + delta);
    }
    else if (isDrawing && currentShape) {
        currentShape->setEndPos(pos);
    }
}

void GraphicController::mouseReleased() {
    if (isMoving && selectedShape) {
        QPointF newStart = selectedShape->getStartPos();
        QPointF newEnd = selectedShape->getEndPos();
        if (newStart != moveStartPos || newEnd != moveEndPos) {
            undoStack->push(new MoveShapeCommand(selectedShape, moveStartPos, moveEndPos, newStart, newEnd));
        }
    }
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

    if (!toRemove.isEmpty()) {
        for (Shape* shape : toRemove) {
            model->removeShapeWithUndo(shape, undoStack);
        }
    }
}

void GraphicController::clearAll() {
    model->clearWithUndo(undoStack);
}
