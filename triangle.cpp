#include "triangle.h"
#include <QStyleOptionGraphicsItem>

Triangle::Triangle(qreal base, qreal height, const QBrush &fillColor, const QPen &borderColor)
    : Shape(), base(base), height(height), fillColor(fillColor), borderColor(borderColor) {}

QRectF Triangle::boundingRect() const {
    return QRectF(-base / 2, -height, base, height);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setBrush(fillColor);
    painter->setPen(borderColor);

    QPointF points[3] = {
        QPointF(0, -height),
        QPointF(-base / 2, 0),
        QPointF(base / 2, 0)
    };
    painter->drawPolygon(points, 3);

    if (option->state & QStyle::State_Selected) {
        QPen selectedPen(Qt::DashLine);
        selectedPen.setColor(Qt::black);
        selectedPen.setWidth(6);
        painter->setPen(selectedPen);
        painter->drawPolygon(points, 3);
    }
}
