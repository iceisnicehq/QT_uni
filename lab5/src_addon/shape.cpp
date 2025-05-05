#include "shape.h"
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene> // Include this to resolve incomplete type issue

Shape::Shape(ShapeType type, const QPointF& startPos, const QColor& color, QGraphicsItem* parent)
    : QGraphicsItem(parent), type(type), startPos(startPos), endPos(startPos),
      color(color), isEditing(false), currentHandle(None), isResizing(false) {
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
}

QRectF Shape::boundingRect() const {
    if (type == ShapeType::Text) {
        QFontMetrics fm(textFont);
        QRectF textRect = fm.boundingRect(text);
        textRect.moveTopLeft(startPos);
        return textRect.adjusted(-5, -5, 5, 5);  // Add some padding
    } else {
        QRectF rect(startPos, endPos);
        rect = rect.normalized();
        return rect.adjusted(-10, -10, 10, 10);
    }
}

void Shape::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(color, 2));
    
    QRectF rect(startPos, endPos); // Declare and initialize rect here
    rect = rect.normalized();

    switch(type) {
    case ShapeType::Line:
        painter->drawLine(startPos, endPos);
        break;
    case ShapeType::Rectangle:
        painter->drawRect(rect);
        break;
    case ShapeType::Ellipse:
        painter->drawEllipse(rect);
        break;
    case ShapeType::Rhombus: {
        QPointF points[4] = {
            QPointF(rect.left() + rect.width()/2, rect.top()),
            QPointF(rect.right(), rect.top() + rect.height()/2),
            QPointF(rect.left() + rect.width()/2, rect.bottom()),
            QPointF(rect.left(), rect.top() + rect.height()/2)
        };
        painter->drawPolygon(points, 4);
        break;
    }
    case ShapeType::Text:
        if (!isEditing) {
            painter->setFont(textFont);
            painter->drawText(startPos, text);
            if (isSelected()) {
                QFontMetrics fm(textFont);
                QRectF textRect = fm.boundingRect(text);
                textRect.moveTopLeft(startPos);
                painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
                painter->setBrush(Qt::NoBrush);
                painter->drawRect(textRect);
            }
        }
        break;
    }

    // Only draw resize handles for non-text shapes
    if (isSelected() && type != ShapeType::Text) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->drawRect(rect);
        painter->setBrush(Qt::white);
        painter->setPen(QPen(Qt::black, 1));

        for (int i = 1; i <= 4; ++i) {
            QRectF handle = getHandleRect(static_cast<ResizeHandle>(i));
            painter->drawRect(handle);
        }
    }
}

Shape::ResizeHandle Shape::getResizeHandle(const QPointF& pos) const {
    if (type == ShapeType::Text) return None;

    for (int i = 1; i <= 4; ++i) {
        ResizeHandle handle = static_cast<ResizeHandle>(i);
        if (getHandleRect(handle).contains(pos)) {
            return handle;
        }
    }
    return None;
}

QRectF Shape::getHandleRect(ResizeHandle handle) const {
    QRectF rect(startPos, endPos);
    rect = rect.normalized();
    const qreal handleSize = 8;

    switch(handle) {
    case TopLeft:     return QRectF(rect.topLeft() - QPointF(handleSize/2, handleSize/2),
                                   QSizeF(handleSize, handleSize));
    case TopRight:    return QRectF(rect.topRight() - QPointF(handleSize/2, handleSize/2),
                                   QSizeF(handleSize, handleSize));
    case BottomLeft:  return QRectF(rect.bottomLeft() - QPointF(handleSize/2, handleSize/2),
                                   QSizeF(handleSize, handleSize));
    case BottomRight: return QRectF(rect.bottomRight() - QPointF(handleSize/2, handleSize/2),
                                   QSizeF(handleSize, handleSize));
    default: return QRectF();
    }
}

void Shape::setEndPos(const QPointF& endPos) {
    prepareGeometryChange();
    this->endPos = endPos;
    update();
}

void Shape::setText(const QString& text) {
    this->text = text;
    update();
}

void Shape::setFont(const QFont& font) {
    textFont = font;
    update();
}

void Shape::setColor(const QColor& color) {
    this->color = color;
    update();
}

void Shape::setEditing(bool editing) {
    isEditing = editing;
    update();
}

ShapeType Shape::getType() const { return type; }
QColor Shape::getColor() const { return color; }
QString Shape::getText() const { return text; }
QFont Shape::getFont() const { return textFont; }

void Shape::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        currentHandle = getResizeHandle(event->pos());
        isResizing = (currentHandle != None);

        if (isResizing) {
            resizeStartPos = startPos;
            resizeStartEnd = endPos;
        }
    }
    QGraphicsItem::mousePressEvent(event);
}

void Shape::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    prepareGeometryChange();
    if (isResizing && (event->buttons() & Qt::LeftButton)) {
        QPointF delta = event->scenePos() - event->lastScenePos();

        switch(currentHandle) {
        case TopLeft:
            startPos += delta;
            break;
        case TopRight:
            endPos.setX(endPos.x() + delta.x());
            startPos.setY(startPos.y() + delta.y());
            break;
        case BottomLeft:
            startPos.setX(startPos.x() + delta.x());
            endPos.setY(endPos.y() + delta.y());
            break;
        case BottomRight:
            endPos += delta;
            break;
        default:
            break;
        }
        update();
    } else {
        if (type == ShapeType::Text) {
            QPointF delta = event->scenePos() - event->lastScenePos();
            startPos += delta;
            endPos = startPos;
            scene()->update(); // Force scene update to prevent artifacts
        } else {
            QGraphicsItem::mouseMoveEvent(event);
        }
    }
    update();
}

void Shape::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    isResizing = false;
    currentHandle = None;
    QGraphicsItem::mouseReleaseEvent(event);
}

void Shape::hoverMoveEvent(QGraphicsSceneHoverEvent* event) {
    ResizeHandle handle = getResizeHandle(event->pos());

    switch(handle) {
    case TopLeft:
    case BottomRight:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TopRight:
    case BottomLeft:
        setCursor(Qt::SizeBDiagCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
    }

    QGraphicsItem::hoverMoveEvent(event);
}

void Shape::setStartPos(const QPointF& pos) {
    prepareGeometryChange();
    startPos = pos;
    update();
}
