#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include "shape.h"

class ChangeColorCommand : public QUndoCommand {
public:
    ChangeColorCommand(Shape* shape, const QColor& oldColor, const QColor& newColor)
        : shape(shape), oldColor(oldColor), newColor(newColor) {}

    void undo() override {
        shape->setColor(oldColor);
    }

    void redo() override {
        shape->setColor(newColor);
    }

private:
    Shape* shape;
    QColor oldColor;
    QColor newColor;
};

class ChangeFontCommand : public QUndoCommand {
public:
    ChangeFontCommand(Shape* shape, const QFont& oldFont, const QFont& newFont)
        : shape(shape), oldFont(oldFont), newFont(newFont) {}

    void undo() override {
        shape->setFont(oldFont);
    }

    void redo() override {
        shape->setFont(newFont);
    }

private:
    Shape* shape;
    QFont oldFont;
    QFont newFont;
};

class MoveShapeCommand : public QUndoCommand {
public:
    MoveShapeCommand(Shape* shape, const QPointF& oldStart, const QPointF& oldEnd, const QPointF& newStart, const QPointF& newEnd)
        : shape(shape), oldStart(oldStart), oldEnd(oldEnd), newStart(newStart), newEnd(newEnd) {}

    void undo() override {
        shape->setStartPos(oldStart);
        shape->setEndPos(oldEnd);
    }

    void redo() override {
        shape->setStartPos(newStart);
        shape->setEndPos(newEnd);
    }

private:
    Shape* shape;
    QPointF oldStart, oldEnd, newStart, newEnd;
};

#endif // COMMANDS_H
