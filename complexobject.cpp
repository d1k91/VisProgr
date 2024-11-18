#include "complexobject.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QDebug>

ComplexObject::ComplexObject() : dx(1), dy(1) {
    QSoundEffect collisionSound;
    collisionSound.setSource(QUrl("/sounds/coliz.wav")); // Убедитесь, что путь корректен
    collisionSound.setLoopCount(1);
    collisionSound.setVolume(0.5);


}


ComplexObject::~ComplexObject() {
    qDeleteAll(items);
}

void ComplexObject::addItem(QGraphicsItem* item) {
    items.append(item);
    item->setParentItem(this);
}

void ComplexObject::removeItem(QGraphicsItem* item) {
    items.removeOne(item);
    delete item;
}

QRectF ComplexObject::boundingRect() const {
    QRectF rect;
    for (const QGraphicsItem* item : items) {
        rect = rect.united(item->boundingRect());
    }
    return rect;
}

void ComplexObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    for (QGraphicsItem* item : items) {
        item->paint(painter, option, widget);
    }
}

void ComplexObject::move(QGraphicsView *view) {
    QGraphicsScene *scene = view->scene();

    // Move the object
    setPos(x() + dx, y() + dy);

    // Convert the view's rectangle to the scene's coordinate system
    QRectF viewRect = view->mapToScene(view->viewport()->rect()).boundingRect();
    QRectF objectRect = boundingRect().translated(pos());

    // Check for collisions with the view boundaries
    if (objectRect.left() < viewRect.left() || objectRect.right() > viewRect.right() ||
        objectRect.top() < viewRect.top() || objectRect.bottom() > viewRect.bottom()) {
        dx = -dx; // Reverse direction on x-axis
        dy = -dy; // Reverse direction on y-axis
        collisionSound.play(); // Play sound on collision
    }

    // Check for collisions with other items
    QList<QGraphicsItem *> collidingItems = scene->collidingItems(this);
    for (QGraphicsItem *item : collidingItems) {
        if ((dynamic_cast<ComplexObject*>(item) || dynamic_cast<Shape*>(item)) && !items.contains(item)) {
            dx = -dx; // Reverse direction on x-axis
            dy = -dy; // Reverse direction on y-axis
            collisionSound.play(); // Play sound on collision
            break;
        }
    }
}
