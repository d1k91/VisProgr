#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle : public Shape {
public:
    Circle(qreal radius, const QBrush &fillColor, const QPen &borderColor);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

private:
    qreal radius;
    QBrush fillColor;
    QPen borderColor;
};

#endif // CIRCLE_H
