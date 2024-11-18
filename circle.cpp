#include "circle.h"
#include <QStyleOptionGraphicsItem>

Circle::Circle(qreal radius, const QBrush &fillColor, const QPen &borderColor)
    : Shape(), radius(radius), fillColor(fillColor), borderColor(borderColor) {}

QRectF Circle::boundingRect() const {
    return QRectF(-radius, -radius, 2 * radius, 2 * radius);
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setBrush(fillColor);
    painter->setPen(borderColor);
    painter->drawEllipse(boundingRect());

    if (option->state & QStyle::State_Selected) {
        QPen selectedPen(Qt::DashLine);
        selectedPen.setColor(Qt::black);
        selectedPen.setWidth(6);
        painter->setPen(selectedPen);
        painter->drawEllipse(boundingRect());
    }
}
