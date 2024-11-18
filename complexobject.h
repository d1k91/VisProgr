#ifndef COMPLEXOBJECT_H
#define COMPLEXOBJECT_H
#include "shape.h"
#include <QGraphicsItem>
#include <QList>
#include <QTimer>
#include <QGraphicsView>
#include <QSoundEffect>
#include <QMediaPlayer>

class ComplexObject : public Shape
{
public:
    ComplexObject();
    ~ComplexObject();

    void addItem(QGraphicsItem* item);
    void removeItem(QGraphicsItem* item);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void move(QGraphicsView *view);

private:
    QList<QGraphicsItem*> items;
    qreal dx; // Change in x-direction
    qreal dy; // Change in y-direction
    QSoundEffect collisionSound; // Sound effect for collisions
};

#endif // COMPLEXOBJECT_H
