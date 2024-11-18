// PARK_letters.cpp

#include "parkword.h"
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

ParkWord::ParkWord() : ComplexObject() {
    qreal x = 0;         // Starting x-position
    qreal y = 0;         // Starting y-position
    qreal spacing = 60;  // Spacing between letters

    QBrush brush(Qt::black);
    QPen pen(Qt::black);

    // Г
            QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
            verticalStem->setBrush(brush);
            verticalStem->setPen(pen);
            addItem(verticalStem);

            QGraphicsRectItem* horizontalBar = new QGraphicsRectItem(x + 10, y, 40, 10);
            horizontalBar->setBrush(brush);
            horizontalBar->setPen(pen);
            addItem(horizontalBar);

            x += spacing;

            // Л
            QGraphicsLineItem* leftDiagonal = new QGraphicsLineItem(x + 25, y, x + 5, y + 60);
            leftDiagonal->setPen(pen);
            addItem(leftDiagonal);

            QGraphicsLineItem* rightDiagonal = new QGraphicsLineItem(x + 25, y, x + 45, y + 60);
            rightDiagonal->setPen(pen);
            addItem(rightDiagonal);

            x += spacing;

            // И
            QGraphicsRectItem* leftStem = new QGraphicsRectItem(x, y, 10, 60);
            leftStem->setBrush(brush);
            leftStem->setPen(pen);
            addItem(leftStem);

            QGraphicsLineItem* diagonal = new QGraphicsLineItem(x + 10, y+60, x + 40, y);
            diagonal->setPen(pen);
            addItem(diagonal);

            QGraphicsRectItem* rightStem = new QGraphicsRectItem(x + 40, y, 10, 60);
            rightStem->setBrush(brush);
            rightStem->setPen(pen);
            addItem(rightStem);

            x += spacing;

            // Н
            QGraphicsRectItem* leftStem1 = new QGraphicsRectItem(x, y, 10, 60);
            leftStem1->setBrush(brush);
            leftStem1->setPen(pen);
            addItem(leftStem1);

            QGraphicsRectItem* horizontalBar1 = new QGraphicsRectItem(x, y + 25, 50, 10);
            horizontalBar1->setBrush(brush);
            horizontalBar1->setPen(pen);
            addItem(horizontalBar1);

            QGraphicsRectItem* rightStem1 = new QGraphicsRectItem(x + 40, y, 10, 60);
            rightStem1->setBrush(brush);
            rightStem1->setPen(pen);
            addItem(rightStem1);

            x += spacing;

            // С
            QGraphicsEllipseItem* semiCircle = new QGraphicsEllipseItem(x, y, 50, 60);
            semiCircle->setStartAngle(45 * 16);
            semiCircle->setSpanAngle(270 * 16);
            semiCircle->setPen(pen);
            addItem(semiCircle);

            x += spacing;

            // К
            QGraphicsRectItem* verticalStem2 = new QGraphicsRectItem(x, y, 10, 60);
            verticalStem2->setBrush(brush);
            verticalStem2->setPen(pen);
            addItem(verticalStem2);

            QGraphicsLineItem* upperDiagonal = new QGraphicsLineItem(x + 10, y + 30, x + 50, y);
            upperDiagonal->setPen(pen);
            addItem(upperDiagonal);

            QGraphicsLineItem* lowerDiagonal = new QGraphicsLineItem(x + 10, y + 30, x + 50, y + 60);
            lowerDiagonal->setPen(pen);
            addItem(lowerDiagonal);

            x += spacing;

            // И
            QGraphicsRectItem* leftStem2 = new QGraphicsRectItem(x, y, 10, 60);
            leftStem2->setBrush(brush);
            leftStem2->setPen(pen);
            addItem(leftStem2);

            QGraphicsLineItem* diagonal1 = new QGraphicsLineItem(x + 10, y+60, x + 40, y);
            diagonal1->setPen(pen);
            addItem(diagonal1);

            QGraphicsRectItem* rightStem2 = new QGraphicsRectItem(x + 40, y, 10, 60);
            rightStem2->setBrush(brush);
            rightStem2->setPen(pen);
            addItem(rightStem2);

            x += spacing;

            // Й
            QGraphicsRectItem* leftStem3 = new QGraphicsRectItem(x, y, 10, 60);
            leftStem3->setBrush(brush);
            leftStem3->setPen(pen);
            addItem(leftStem3);

            QGraphicsLineItem* diagonal2 = new QGraphicsLineItem(x + 10, y+60, x + 40, y);
            diagonal2->setPen(pen);
            addItem(diagonal2);

            QGraphicsLineItem* pis = new QGraphicsLineItem(x + 10, y-20, x + 40, y -20);
            pis->setPen(pen);
            addItem(pis);

            QGraphicsRectItem* rightStem3 = new QGraphicsRectItem(x + 40, y, 10, 60);
            rightStem3->setBrush(brush);
            rightStem3->setPen(pen);
            addItem(rightStem3);

            x += spacing;
        }

