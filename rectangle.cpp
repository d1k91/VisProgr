#include "rectangle.h"
#include <QStyleOptionGraphicsItem>

Rectangle::Rectangle(qreal width, qreal height, const QBrush &fillColor, const QPen &borderColor)
    : Shape(), width(width), height(height), fillColor(fillColor), borderColor(borderColor) {}

QRectF Rectangle::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setBrush(fillColor);
    painter->setPen(borderColor);
    painter->drawRect(boundingRect());

    if (option->state & QStyle::State_Selected) {
        QPen selectedPen(Qt::DashLine);
        selectedPen.setColor(Qt::black);
        selectedPen.setWidth(6);
        painter->setPen(selectedPen);
        painter->drawRect(boundingRect());
    }
}
