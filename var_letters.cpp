#include "varword.h"
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

VarWord::VarWord() : ComplexObject() {
    qreal x = 0;
    qreal y = 0;
    qreal spacing = 70;

    QBrush brush(Qt::black);
    QPen pen(Qt::black);
    pen.setWidth(2);

    // О
            {QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(x, y, 50, 60);
            circle->setBrush(brush);
            circle->setPen(pen);
            addItem(circle);}

            x += spacing;

            // Г
            {QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
            verticalStem->setBrush(brush);
            verticalStem->setPen(pen);
           addItem(verticalStem);

            QGraphicsRectItem* horizontalBar = new QGraphicsRectItem(x + 10, y, 40, 10);
            horizontalBar->setBrush(brush);
            horizontalBar->setPen(pen);
            addItem(horizontalBar);}

            x += spacing;

            // А
            {QGraphicsLineItem* leftDiagonal = new QGraphicsLineItem(x + 25, y, x + 5, y + 60);
            leftDiagonal->setPen(pen);
            addItem(leftDiagonal);

            QGraphicsLineItem* rightDiagonal = new QGraphicsLineItem(x + 25, y, x + 45, y + 60);
            rightDiagonal->setPen(pen);
            addItem(rightDiagonal);

            QGraphicsRectItem* horizontalBar1 = new QGraphicsRectItem(x + 10, y + 30, 30, 5);
            horizontalBar1->setBrush(brush);
            horizontalBar1->setPen(pen);
            addItem(horizontalBar1);}

            x += spacing;

            // Р
            {QGraphicsRectItem* verticalStem1 = new QGraphicsRectItem(x, y, 10, 60);
            verticalStem1->setBrush(brush);
            verticalStem1->setPen(pen);
            addItem(verticalStem1);

            QGraphicsEllipseItem* topLoop = new QGraphicsEllipseItem(x + 10, y, 30, 30);
            topLoop->setBrush(brush);
            topLoop->setPen(pen);
            addItem(topLoop);}

            x += spacing;

            // К
            {QGraphicsRectItem* verticalStem2 = new QGraphicsRectItem(x, y, 10, 60);
            verticalStem2->setBrush(brush);
            verticalStem2->setPen(pen);
            addItem(verticalStem2);

            QGraphicsLineItem* upperDiagonal = new QGraphicsLineItem(x + 10, y + 30, x + 50, y);
            upperDiagonal->setPen(pen);
            addItem(upperDiagonal);

            QGraphicsLineItem* lowerDiagonal = new QGraphicsLineItem(x + 10, y + 30, x + 50, y + 60);
            lowerDiagonal->setPen(pen);
            addItem(lowerDiagonal);}

            x += spacing;

            // О
            {QGraphicsEllipseItem* circle1 = new QGraphicsEllipseItem(x, y, 50, 60);
            circle1->setBrush(brush);
            circle1->setPen(pen);
            addItem(circle1);}

            x += spacing;

            // В
            {QGraphicsRectItem* verticalStem3 = new QGraphicsRectItem(x, y, 10, 60);
            verticalStem3->setBrush(brush);
            verticalStem3->setPen(pen);
            addItem(verticalStem3);

            QGraphicsEllipseItem* topLoop1 = new QGraphicsEllipseItem(x + 10, y, 30, 30);
            topLoop1->setBrush(brush);
            topLoop1->setPen(pen);
            addItem(topLoop1);

            QGraphicsEllipseItem* bottomLoop1 = new QGraphicsEllipseItem(x + 10, y + 30, 30, 30);
            bottomLoop1->setBrush(brush);
            bottomLoop1->setPen(pen);
            addItem(bottomLoop1);}


    }

