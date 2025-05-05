#ifndef GRAPHICCONTROLLER_H
#define GRAPHICCONTROLLER_H

#include <QObject>
#include <QColor>
#include <QFont>
#include <QUndoStack>
#include "shape.h" // Include Shape to resolve errors

// Forward declare GraphicModel to break circular dependency
class GraphicModel;

enum class EditorMode { Select, CreateLine, CreateRect, CreateEllipse, CreateText, CreateRhombus };

class GraphicController : public QObject {
    Q_OBJECT
public:
    explicit GraphicController(GraphicModel* model, QObject* parent = nullptr);

    void setEditorMode(EditorMode mode);
    void setCurrentColor(const QColor& color);
    void setCurrentText(const QString& text);
    void setCurrentFont(const QFont& font);
    QColor getCurrentColor() const;
    void changeSelectedItemsColor(const QColor& color);
    void changeSelectedItemsFont(const QFont& font);

    EditorMode getEditorMode() const { return currentMode; }

    void mousePressed(const QPointF& pos);
    void mouseMoved(const QPointF& pos);
    void mouseReleased();

    void deleteSelectedItems();
    void clearAll();

    void setUndoStack(QUndoStack* stack) { undoStack = stack; }

private:
    GraphicModel* model;
    EditorMode currentMode;
    QColor currentColor;
    QString currentText;
    QFont currentFont;
    Shape* currentShape; // Resolved: Shape is now recognized
    bool isDrawing;
    bool isMoving;
    Shape* selectedShape; // Resolved: Shape is now recognized
    QPointF moveStartPos; // Store the initial position of the shape being moved
    QPointF moveEndPos;
    QUndoStack* undoStack;
    Shape* lastMovedShape = nullptr;
    QPointF lastMovedOldPos;
};

#endif // GRAPHICCONTROLLER_H
