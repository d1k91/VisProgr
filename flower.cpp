#include "flower.h"
#include <QBrush>
#include <QPen>
#include <QPolygonF>
#include <QColor>
Flower::Flower() : ComplexObject() {
    QColor petalColor(255, 105, 180); // Розовый цвет для лепестков

    // Лепестки цветка
    for (int i = 0; i < 6; ++i) {
        QPolygonF petal;
        petal << QPointF(0, -30) << QPointF(20, -10) << QPointF(0, 0)
              << QPointF(-20, -10) << QPointF(0, -30);
        QGraphicsPolygonItem* petalItem = new QGraphicsPolygonItem(petal);
        petalItem->setBrush(QBrush(petalColor));
        petalItem->setPen(QPen(Qt::black));
        petalItem->setRotation(i * 60); // Поворачиваем лепесток
        addItem(petalItem);
    }

    // Центр цветка
    QGraphicsEllipseItem* center = new QGraphicsEllipseItem(-10, -10, 20, 20);
    center->setBrush(QBrush(QColor(255, 215, 0))); // Желтый цвет для центра
    center->setPen(QPen(Qt::black));
    addItem(center);

    // Стебель цветка
    QGraphicsRectItem* stem = new QGraphicsRectItem(-5, 15, 10, 60);
    stem->setBrush(QBrush(QColor(34, 139, 34))); // Зеленый цвет для стебля
    stem->setPen(QPen(Qt::black));
    addItem(stem);


    // Листья цветка
    QPolygonF leftLeaf;
    leftLeaf << QPointF(-15, 20) << QPointF(-30, 40) << QPointF(-10, 30) << QPointF(-5, 20);
    QGraphicsPolygonItem* leftLeafItem = new QGraphicsPolygonItem(leftLeaf);
    leftLeafItem->setBrush(QBrush(QColor(0, 128, 0))); // Темно-зеленый цвет для листа
    leftLeafItem->setPen(QPen(Qt::black));
    addItem(leftLeafItem);

    QPolygonF rightLeaf;
    rightLeaf << QPointF(15, 20) << QPointF(30, 40) << QPointF(10, 30) << QPointF(5, 20);
    QGraphicsPolygonItem* rightLeafItem = new QGraphicsPolygonItem(rightLeaf);
    rightLeafItem->setBrush(QBrush(QColor(0, 128, 0)));
    rightLeafItem->setPen(QPen(Qt::black));
    addItem(rightLeafItem);
}
