#include "customgraphicsview.h"
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsEllipseItem>
#include <QMimeData>
#include <QResizeEvent>

CustomGraphicsView::CustomGraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {}

void CustomGraphicsView::setBrushSize(qreal size) {
    brushSize = size;
}

void CustomGraphicsView::setBrushColor(const QColor &color) {
    brushColor = color;
}

void CustomGraphicsView::setBrushStyle(Qt::BrushStyle style) {
    brushStyle = style;
}

void CustomGraphicsView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDrawing = true;
        drawAt(event->pos());
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void CustomGraphicsView::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction(); // Разрешаем перетаскивание изображений
    } else {
        QGraphicsView::dragEnterEvent(event);
    }
}

void CustomGraphicsView::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasImage()) {
        QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
        item->setPos(mapToScene(event->pos())); // Устанавливаем позицию изображения на сцене
        scene()->addItem(item);                 // Добавляем изображение на сцену
        event->acceptProposedAction();          // Принимаем перетаскивание
    } else {
        QGraphicsView::dropEvent(event);
    }
}

void CustomGraphicsView::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing) {
        drawAt(event->pos());
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void CustomGraphicsView::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDrawing = false;
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void CustomGraphicsView::drawAt(const QPoint &position) {
    QPointF scenePos = mapToScene(position);
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(
        scenePos.x() - brushSize / 2,
        scenePos.y() - brushSize / 2,
        brushSize,
        brushSize
    );

    // Устанавливаем стиль кисти
    QBrush brush(brushColor, brushStyle);
    ellipse->setBrush(brush);
    ellipse->setPen(Qt::NoPen);
    scene()->addItem(ellipse);
}

void CustomGraphicsView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    if (scene()) {
        scene()->setSceneRect(rect()); // Set the scene rect to match the view's rect
    }
}
