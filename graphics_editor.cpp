#include "graphics_editor.h"
#include "circle.h"
#include "line.h"
#include "triangle.h"
#include "rectangle.h"
#include <QGraphicsView>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QInputDialog>
#include <QColorDialog>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QFontDialog>
#include <QGraphicsPixmapItem> // Для отображения изображений
#include <QComboBox>
#include <customgraphicsview.h>
#include "movabletextitem.h"
#include "QtMath"
#include "complexobject.h"
#include "dog.h"
#include "flower.h"
#include "parkword.h"
#include "varword.h"
#include "martword.h"

GraphicsEditorWindow::GraphicsEditorWindow(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)),
      currentBrushSize(10), isEraserMode(false), currentBrushStyle(Qt::SolidPattern) {

    // Создаем вид и добавляем сцену
    QGraphicsView *view = new CustomGraphicsView(scene, this);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("QGraphicsView { border: 3px solid black; background-color: white; }");

    setCentralWidget(view);
    setWindowTitle("Graphics Editor");

    // Устанавливаем минимальный и максимальный размер окна
    setMinimumSize(900, 900);  // Минимальный размер окна
    setMaximumSize(1600, 1600); // Максимальный размер окна
    setAcceptDrops(true);     // Разрешаем перетаскивание

    // Создаем панель инструментов
    QToolBar *toolbar = addToolBar("Shapes");

    QAction *addTextAction = new QAction(QIcon(":/toolbar/file.png"),"Add Text", this);
    toolbar->addAction(addTextAction);
    connect(addTextAction, &QAction::triggered, this, &GraphicsEditorWindow::addText);

    // Добавляем кнопку для круга
    QAction *addCircleAction = new QAction(QIcon(":/toolbar/plus.png"),"Add Circle", this);
    toolbar->addAction(addCircleAction);
    connect(addCircleAction, &QAction::triggered, this, &GraphicsEditorWindow::addCircle);

    // Кнопка для удаления выбранного элемента
    QAction *deleteAction = new QAction(QIcon(":/toolbar/delete.png"),"Delete", this);
    toolbar->addAction(deleteAction);
    connect(deleteAction, &QAction::triggered, this, &GraphicsEditorWindow::deleteSelectedItem);


    // Добавляем кнопку для импорта изображения
    QAction *importAction = new QAction(QIcon(":/toolbar/upload.png"),"Import Image", this);
    toolbar->addAction(importAction);
    connect(importAction, &QAction::triggered, this, &GraphicsEditorWindow::importImage);

    // Добавляем кнопку для сохранения изображения
    QAction *saveAction = new QAction(QIcon(":/toolbar/diskette.png"),"Save", this);
    toolbar->addAction(saveAction);
    connect(saveAction, &QAction::triggered, this, &GraphicsEditorWindow::saveImage);

    // Кнопка для изменения фона
    QAction *backgroundAction = new QAction(QIcon(":/toolbar/paint-bucket.png"),"Background Color", this);
    toolbar->addAction(backgroundAction);
    connect(backgroundAction, &QAction::triggered, this, &GraphicsEditorWindow::changeBackgroundColor);

    // Кнопка для изменения размера кисти
    QAction *brushSizeAction = new QAction(QIcon(":/toolbar/brush.png"),"Brush Size", this);
    toolbar->addAction(brushSizeAction);
    connect(brushSizeAction, &QAction::triggered, this, &GraphicsEditorWindow::setBrushSize);

    // Кнопка для изменения цвета кисти
    QAction *brushColorAction = new QAction(QIcon(":/toolbar/art.png"),"Brush Color", this);
    toolbar->addAction(brushColorAction);
    connect(brushColorAction, &QAction::triggered, this, &GraphicsEditorWindow::setBrushColor);

    // Добавляем кнопку для линии
    QAction *addLineAction = new QAction(QIcon(":/toolbar/menu.png"),"Add Line", this);
    toolbar->addAction(addLineAction);
    connect(addLineAction, &QAction::triggered, this, &GraphicsEditorWindow::addLine);

    // Добавляем кнопку для прямоугольника
    QAction *addRectangleAction = new QAction(QIcon(":/toolbar/interface.png"),"Add Rectangle", this);
    toolbar->addAction(addRectangleAction);
    connect(addRectangleAction, &QAction::triggered, this, &GraphicsEditorWindow::addRectangle);

    // Добавляем кнопку для треугольника
    QAction *addTriangleAction = new QAction(QIcon(":/toolbar/triangle.png"),"Add Triangle", this);
    toolbar->addAction(addTriangleAction);
    connect(addTriangleAction, &QAction::triggered, this, &GraphicsEditorWindow::addTriangle);

     QComboBox *brushStyleComboBox = new QComboBox(this);
     brushStyleComboBox->addItem("Solid", QVariant::fromValue(Qt::SolidPattern));
     brushStyleComboBox->addItem("Dense 1", QVariant::fromValue(Qt::Dense5Pattern));
     brushStyleComboBox->addItem("Dense 2", QVariant::fromValue(Qt::Dense6Pattern));
     brushStyleComboBox->addItem("Dense 3", QVariant::fromValue(Qt::Dense7Pattern));
     brushStyleComboBox->addItem("Dense 4", QVariant::fromValue(Qt::Dense7Pattern));
     brushStyleComboBox->addItem("Dense 5", QVariant::fromValue(Qt::Dense5Pattern));
     brushStyleComboBox->addItem("Dense 6", QVariant::fromValue(Qt::Dense6Pattern));
     brushStyleComboBox->addItem("Dense 7", QVariant::fromValue(Qt::Dense7Pattern));
     brushStyleComboBox->addItem("Cross", QVariant::fromValue(Qt::CrossPattern));
     brushStyleComboBox->addItem("Horizontal", QVariant::fromValue(Qt::HorPattern));
     brushStyleComboBox->addItem("Vertical", QVariant::fromValue(Qt::VerPattern));
     toolbar->addWidget(brushStyleComboBox);
     connect(brushStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &GraphicsEditorWindow::setBrushStyle);

     // Кнопка для ластика
     QAction *eraserAction = new QAction(QIcon(":/toolbar/eraser.png"),"Eraser", this);
     toolbar->addAction(eraserAction);
     connect(eraserAction, &QAction::triggered, this, &GraphicsEditorWindow::setEraser);

     QTimer *timer = new QTimer(this);
     timer->start(16); // Set the timer interval (e.g., 16 ms for ~60 FPS)

     Dog *dog = new Dog();
     dog->setPos(200, 400);
     connect(timer, &QTimer::timeout, [dog, view]() { dog->move(view); }); // Передаем представление в функцию перемещения
     scene->addItem(dog);




     Flower *flower = new Flower();
     flower->setPos(100, 200);
     connect(timer, &QTimer::timeout, [flower, view]() { flower->move(view); }); // Передаем представление в функцию перемещения
     scene->addItem(flower);

     ParkWord* parkWord = new ParkWord();
     scene->addItem(parkWord);
     connect(timer, &QTimer::timeout, [parkWord, view]() { parkWord->move(view); });
     parkWord->setPos(300, 140);

     VarWord* varWord = new VarWord();
     scene->addItem(varWord);
     connect(timer, &QTimer::timeout, [varWord, view]() { varWord->move(view); });
     varWord->setPos (300, 300);

     MartWord* martWord = new MartWord();
     scene->addItem(martWord);
     connect(timer, &QTimer::timeout, [martWord, view]() { martWord->move(view); });
     martWord->setPos(50, 50);
}

GraphicsEditorWindow::~GraphicsEditorWindow() {
    delete scene;
}


// Слот для добавления круга
void GraphicsEditorWindow::addCircle() {
    // Запрашиваем радиус
    bool ok;
    qreal radius = QInputDialog::getDouble(this, "Circle Radius", "Enter circle radius:", 50, 1, 200, 1, &ok);
    if (!ok) return;

    // Выбор цвета заливки
    QColor fillColor = QColorDialog::getColor(Qt::blue, this, "Select Fill Color");
    if (!fillColor.isValid()) return;

    // Выбор цвета обводки
    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Select Border Color");
    if (!borderColor.isValid()) return;

    QBrush brush(fillColor);
    QPen pen(borderColor);
    pen.setWidth(2); // Устанавливаем ширину обводки

    Circle *circle = new Circle(radius, brush, pen); // Создаём круг с заданными параметрами
    scene->addItem(circle); // Добавляем круг на сцену
    circle->setPos(100, 200);
}

// Слот для сохранения изображения
void GraphicsEditorWindow::saveImage() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG Files (*.png)");

    if (!filePath.isEmpty()) {
        // Устанавливаем размер изображения под размер сцены
        QPixmap pixmap(scene->sceneRect().size().toSize());

        // Создаём QPainter для рисования на QPixmap
        QPainter painter(&pixmap);

        // Отрисовываем сцену на QPixmap
        scene->render(&painter);

        // Сохраняем изображение в фа��л
        pixmap.save(filePath, "PNG");
    }
}

// Слот для импорта изображения

void GraphicsEditorWindow::importImage() {
    QString filePath = QFileDialog::getOpenFileName(this, "Import Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!filePath.isEmpty()) {
        QPixmap pixmap(filePath); // Загружаем изображение

        if (!pixmap.isNull()) {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
            item->setPos(0, 0); // Устанавливаем позицию на сцене
            scene->addItem(item); // Добавляем изображение на сцену
        }
    }
}

void GraphicsEditorWindow::setBrushStyle() {
    QComboBox *brushStyleComboBox = qobject_cast<QComboBox*>(sender());
    if (brushStyleComboBox) {
        Qt::BrushStyle style = static_cast<Qt::BrushStyle>(brushStyleComboBox->currentData().toInt());
        currentBrushStyle = style;
        static_cast<CustomGraphicsView*>(centralWidget())->setBrushStyle(currentBrushStyle);
    }
}

void GraphicsEditorWindow::setBrushSize() {
    bool ok;
    qreal size = QInputDialog::getDouble(this, "Brush Size", "Enter brush size:", currentBrushSize, 1, 50, 1, &ok);
    if (ok) {
        currentBrushSize = size;
        static_cast<CustomGraphicsView*>(centralWidget())->setBrushSize(currentBrushSize);
    }
}

void GraphicsEditorWindow::setBrushColor() {
    QColor color = QColorDialog::getColor(currentBrushColor, this, "Select Brush Color");
    if (color.isValid()) {
        currentBrushColor = color;
        isEraserMode = false;
        static_cast<CustomGraphicsView*>(centralWidget())->setBrushColor(currentBrushColor);
    }
}

void GraphicsEditorWindow::setEraser() {
    isEraserMode = true;
    static_cast<CustomGraphicsView*>(centralWidget())->setBrushColor(scene->backgroundBrush().color());
}

void GraphicsEditorWindow::changeBackgroundColor() {
    QColor color = QColorDialog::getColor(scene->backgroundBrush().color(), this, "Select Background Color");
    if (color.isValid()) {
        scene->setBackgroundBrush(color);
        if (isEraserMode) {
            static_cast<CustomGraphicsView*>(centralWidget())->setBrushColor(color);
        }
    }
}

// Слот для добавлеия текста
void GraphicsEditorWindow::addText() {
    // Запрашиваем текст
    bool ok;
    QString text = QInputDialog::getText(this, "Add Text", "Enter your text:", QLineEdit::Normal, "", &ok);
    if (!ok || text.isEmpty()) return;

    // Запрашиваем шрифт
    bool fontOk;
    QFont font = QFontDialog::getFont(&fontOk, QFont("Arial", 12), this, "Select Font");
    if (!fontOk) return;

    // Создаем элемент текста с поведением перемещения правой кнопкой мыши
    MovableTextItem *textItem = new MovableTextItem(text);
    textItem->setFont(font);

    // Добавляем текст на сцену
    scene->addItem(textItem);
    textItem->setPos(100, 200);
}


void GraphicsEditorWindow::deleteSelectedItem() {
    // Получаем выбранные элементы
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if (selectedItems.isEmpty()) {
        qDebug() << "No items selected for deletion."; // Отладочное сообщение
        return;
    }

    // Удаляем все выбранные элементы
    for (QGraphicsItem *item : selectedItems) {
        scene->removeItem(item); // Удаляем элемент из сцены
        delete item; // Удаляем объект из памяти
        qDebug() << "Item deleted."; // Подтверждение удаления
    }
}


// Обработка события входа перетаскивания
void GraphicsEditorWindow::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    }
}

// Обработка события завершения перетаскивания
void GraphicsEditorWindow::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasImage()) {
        QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
        item->setPos(event->pos()); // Устанавливаем позицию на сцене
        scene->addItem(item);        // Добавляем изображение на сцену
        event->acceptProposedAction();
    }
}
// Конструктор и слот для добавления линии
void GraphicsEditorWindow::addLine() {
    // Запрашиваем длину и угол
    bool ok;
    qreal length = QInputDialog::getDouble(this, "Line Length", "Enter line length:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    qreal angle = QInputDialog::getDouble(this, "Line Angle", "Enter line angle (in degrees):", 0, -360, 360, 1, &ok);
    if (!ok) return;

    // Выбор цвета обводки
    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Select Border Color");
    if (!borderColor.isValid()) return;

    QPen pen(borderColor);
    pen.setWidth(2); // Устанавливаем ширину обводки

    Line *line = new Line(length, qDegreesToRadians(angle), pen); // Создаём линию с заданными параметрами
    scene->addItem(line); // Добавляем линию на сцену
    line->setPos(100, 200);
}


// Конструктор и слот для добавления прямоугольника
void GraphicsEditorWindow::addRectangle() {
    // Запрашиваем ширину и высоту
    bool ok;
    qreal width = QInputDialog::getDouble(this, "Rectangle Width", "Enter rectangle width:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    qreal height = QInputDialog::getDouble(this, "Rectangle Height", "Enter rectangle height:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    // Выбор цвета заливки
    QColor fillColor = QColorDialog::getColor(Qt::blue, this, "Select Fill Color");
    if (!fillColor.isValid()) return;

    // Выбор цвета обводки
    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Select Border Color");
    if (!borderColor.isValid()) return;

    QBrush brush(fillColor);
    QPen pen(borderColor);
    pen.setWidth(2); // Устанавливаем ширину ��бводки

    Rectangle *rect = new Rectangle(width, height, brush, pen); // Создаём прямоугольник с заданными параметрми
    scene->addItem(rect); // Добавляем прямоугольник на сцену
    rect->setPos(100, 200);
}

// Конструктор и слот для добавления треугольника
void GraphicsEditorWindow::addTriangle() {
    // Запрашиваем основание и высоту
    bool ok;
    qreal base = QInputDialog::getDouble(this, "Triangle Base", "Enter triangle base:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    qreal height = QInputDialog::getDouble(this, "Triangle Height", "Enter triangle height:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    // Выбор цвета заливки
    QColor fillColor = QColorDialog::getColor(Qt::blue, this, "Select Fill Color");
    if (!fillColor.isValid()) return;

    // Выбор цвета обводки
    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Select Border Color");
    if (!borderColor.isValid()) return;

    QBrush brush(fillColor);
    QPen pen(borderColor);
    pen.setWidth(2); // Устанавливаем ширину обводки

    Triangle *triangle = new Triangle(base, height, brush, pen); // Создаём треугольник с заданными параметрами
    scene->addItem(triangle); // Добавляем треугольник на сцену
    triangle->setPos(100, 200);
}





