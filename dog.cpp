#include "dog.h"
#include <QBrush>
#include <QPen>
#include <QPolygonF>
#include <QColor>

Dog::Dog() : ComplexObject() {
    QColor brown(139, 69, 19); // Define a brown color

    QGraphicsEllipseItem* body = new QGraphicsEllipseItem(-50, -50, 100, 100);
    body->setBrush(QBrush(brown));
    body->setPen(QPen(Qt::black));
    addItem(body);

    // Create the head of the dog
    QGraphicsEllipseItem* head = new QGraphicsEllipseItem(-30, -50, 60, 60);
    head->setBrush(QBrush(brown));
    head->setPen(QPen(Qt::black));
    addItem(head);

    // Create the eyes of the dog
    QGraphicsEllipseItem* leftEye = new QGraphicsEllipseItem(-20, -40, 15, 15);
    leftEye->setBrush(QBrush(Qt::white));
    leftEye->setPen(QPen(Qt::black));
    addItem(leftEye);

    QGraphicsEllipseItem* rightEye = new QGraphicsEllipseItem(5, -40, 15, 15);
    rightEye->setBrush(QBrush(Qt::white));
    rightEye->setPen(QPen(Qt::black));
    addItem(rightEye);

    // Create the pupils of the dog
    QGraphicsEllipseItem* leftPupil = new QGraphicsEllipseItem(-15, -35, 5, 5);
    leftPupil->setBrush(QBrush(Qt::black));
    addItem(leftPupil);

    QGraphicsEllipseItem* rightPupil = new QGraphicsEllipseItem(10, -35, 5, 5);
    rightPupil->setBrush(QBrush(Qt::black));
    addItem(rightPupil);

    // Create the nose of the dog
    QGraphicsEllipseItem* nose = new QGraphicsEllipseItem(-10, -20, 20, 10);
    nose->setBrush(QBrush(Qt::black));
    addItem(nose);

    // Create the ears of the dog
    QPolygonF leftEar;
    leftEar << QPointF(-30, -50) << QPointF(-50, -30) << QPointF(-30, -10);
    QGraphicsPolygonItem* leftEarItem = new QGraphicsPolygonItem(leftEar);
    leftEarItem->setBrush(QBrush(brown));
    leftEarItem->setPen(QPen(Qt::black));
    addItem(leftEarItem);

    QPolygonF rightEar;
    rightEar << QPointF(30, -50) << QPointF(50, -30) << QPointF(30, -10);
    QGraphicsPolygonItem* rightEarItem = new QGraphicsPolygonItem(rightEar);
    rightEarItem->setBrush(QBrush(brown));
    rightEarItem->setPen(QPen(Qt::black));
    addItem(rightEarItem);

    QGraphicsEllipseItem* leftHand = new QGraphicsEllipseItem(10, 40, 20, 20);
    leftHand->setBrush(QBrush(Qt::black));
    addItem(leftHand);

    QGraphicsEllipseItem* rightHand = new QGraphicsEllipseItem(-30, 40, 20, 20);
    rightHand->setBrush(QBrush(Qt::black));
    addItem(rightHand);
}
