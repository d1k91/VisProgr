#include "martword.h"
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

MartWord::MartWord() : ComplexObject() {
    qreal x = 0;
    qreal y = 0;
    qreal spacing = 70;

    QBrush brush(Qt::black);
    QPen pen(Qt::black);
    pen.setWidth(2);

    // Буква "Б"
        {
        QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
        verticalStem->setBrush(brush);
        verticalStem->setPen(pen);
        addItem(verticalStem);

        // Удаляем верхний круг и добавляем вместо него горизонтальную линию
        QGraphicsLineItem* topLine = new QGraphicsLineItem(x + 10, y + 15, x + 40, y + 15);
        topLine->setPen(pen);
        addItem(topLine);

        QGraphicsEllipseItem* bottomLoop = new QGraphicsEllipseItem(x + 10, y + 30, 30, 30);
        bottomLoop->setBrush(brush);
        bottomLoop->setPen(pen);
        addItem(bottomLoop);
        }

        x += spacing; // Переход к следующей букве

        // Буква "А"
        {
            QGraphicsLineItem* leftDiagonal = new QGraphicsLineItem(x + 25, y, x + 5, y + 60);
            leftDiagonal->setPen(pen);
            addItem(leftDiagonal);

            QGraphicsLineItem* rightDiagonal = new QGraphicsLineItem(x + 25, y, x + 45, y + 60);
            rightDiagonal->setPen(pen);
            addItem(rightDiagonal);

            QGraphicsRectItem* horizontalBar = new QGraphicsRectItem(x + 10, y + 30, 30, 5);
            horizontalBar->setBrush(brush);
            horizontalBar->setPen(pen);
            addItem(horizontalBar);
        }

        x += spacing;

        // Буква "Ж"
        {
            QGraphicsRectItem* verticalStem1 = new QGraphicsRectItem(x, y, 10, 60);
                    verticalStem1->setBrush(brush);
                    verticalStem1->setPen(pen);
                    addItem(verticalStem1);

                    QGraphicsRectItem* verticalStem2 = new QGraphicsRectItem(x + 30, y, 10, 60);
                    verticalStem2->setBrush(brush);
                    verticalStem2->setPen(pen);
                    addItem(verticalStem2);

                    QGraphicsRectItem* verticalStem3 = new QGraphicsRectItem(x + 15, y, 10, 60);
                    verticalStem3->setBrush(brush);
                    verticalStem3->setPen(pen);
                    addItem(verticalStem3);

                    QGraphicsRectItem* horizontalBar1 = new QGraphicsRectItem(x, y + 25, 40, 10);
                    horizontalBar1->setBrush(brush);
                    horizontalBar1->setPen(pen);
                    addItem(horizontalBar1);


        }

        x += spacing;

        // Буква "Е"
        {
            QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
            verticalStem->setBrush(brush);
            verticalStem->setPen(pen);
            addItem(verticalStem);

            QGraphicsRectItem* horizontalTop = new QGraphicsRectItem(x + 10, y, 30, 10);
            horizontalTop->setBrush(brush);
            horizontalTop->setPen(pen);
            addItem(horizontalTop);

            QGraphicsRectItem* horizontalMiddle = new QGraphicsRectItem(x + 10, y + 25, 30, 10);
            horizontalMiddle->setBrush(brush);
            horizontalMiddle->setPen(pen);
            addItem(horizontalMiddle);

            QGraphicsRectItem* horizontalBottom = new QGraphicsRectItem(x + 10, y + 50, 30, 10);
            horizontalBottom->setBrush(brush);
            horizontalBottom->setPen(pen);
            addItem(horizontalBottom);
        }

        x += spacing;

        // Буква "Н"
        {
            QGraphicsRectItem* leftStem = new QGraphicsRectItem(x, y, 10, 60);
            leftStem->setBrush(brush);
            leftStem->setPen(pen);
            addItem(leftStem);

            QGraphicsRectItem* horizontalBar = new QGraphicsRectItem(x, y + 25, 50, 10);
            horizontalBar->setBrush(brush);
            horizontalBar->setPen(pen);
            addItem(horizontalBar);

            QGraphicsRectItem* rightStem = new QGraphicsRectItem(x + 40, y, 10, 60);
            rightStem->setBrush(brush);
            rightStem->setPen(pen);
            addItem(rightStem);
        }

        x += spacing;

        // Буква "О"
        {
            QGraphicsEllipseItem* outerCircle = new QGraphicsEllipseItem(x, y, 50, 60);
            outerCircle->setBrush(brush);
            outerCircle->setPen(pen);
            addItem(outerCircle);

            QGraphicsEllipseItem* innerCircle = new QGraphicsEllipseItem(x + 10, y + 10, 30, 40);
            innerCircle->setBrush(Qt::white);
            innerCircle->setPen(Qt::NoPen);
            addItem(innerCircle);
        }

        x += spacing;

        // Буква "В"
        {
            QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
            verticalStem->setBrush(brush);
            verticalStem->setPen(pen);
            addItem(verticalStem);

            QGraphicsEllipseItem* topLoop = new QGraphicsEllipseItem(x + 10, y, 30, 30);
            topLoop->setBrush(brush);
            topLoop->setPen(pen);
            addItem(topLoop);

            QGraphicsEllipseItem* bottomLoop = new QGraphicsEllipseItem(x + 10, y + 30, 30, 30);
            bottomLoop->setBrush(brush);
            bottomLoop->setPen(pen);
            addItem(bottomLoop);
        }
}
