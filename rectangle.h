#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include <QGraphicsItem>
#include <QPainter>

class Rectangle : public Shape {
public:
    Rectangle(qreal width, qreal height, const QBrush &fillColor, const QPen &borderColor);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

private:
    qreal width;
    qreal height;
    QBrush fillColor;
    QPen borderColor;
};

#endif // RECTANGLE_H
