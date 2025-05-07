#include "mainwindow.h"
#include <QFontDialog>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    model = new GraphicModel(this);
    controller = new GraphicController(model, this);

    setupUI();
    setupToolBar();
    setupConnections();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUI() {
    view = new QGraphicsView(this);
    view->setScene(model->getScene());
    view->setRenderHint(QPainter::Antialiasing);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setInteractive(true);
    setCentralWidget(view);

    toolBar = new QToolBar("Tools", this);
    addToolBar(Qt::LeftToolBarArea, toolBar);
}

void MainWindow::setupToolBar() {
    QAction* selectAction = toolBar->addAction("Select");
    QAction* lineAction = toolBar->addAction("Line");
    QAction* rectAction = toolBar->addAction("Rectangle");
    QAction* ellipseAction = toolBar->addAction("Ellipse");
    QAction* textAction = toolBar->addAction("Text");
    QAction* triangleAction = toolBar->addAction("Triangle");
    toolBar->addSeparator();
    QAction* colorAction = toolBar->addAction("Color");
    toolBar->addSeparator();
    QAction* deleteAction = toolBar->addAction("Delete");
    QAction* clearAction = toolBar->addAction("Clear");

    QAction* undoAction = toolBar->addAction("Undo");
    QAction* redoAction = toolBar->addAction("Redo");
    QAction* fontAction = toolBar->addAction("Font");

    connect(undoAction, &QAction::triggered, model, &GraphicModel::undo);
    connect(redoAction, &QAction::triggered, model, &GraphicModel::redo);
    connect(selectAction, &QAction::triggered, this, &MainWindow::onSelectAction);
    connect(lineAction, &QAction::triggered, this, &MainWindow::onLineAction);
    connect(rectAction, &QAction::triggered, this, &MainWindow::onRectAction);
    connect(ellipseAction, &QAction::triggered, this, &MainWindow::onEllipseAction);
    connect(textAction, &QAction::triggered, this, &MainWindow::onTextAction);
    connect(triangleAction, &QAction::triggered, this, &MainWindow::onTriangleAction);
    connect(colorAction, &QAction::triggered, this, &MainWindow::onColorAction);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::onDeleteAction);
    connect(clearAction, &QAction::triggered, this, &MainWindow::onClearAction);
    connect(fontAction, &QAction::triggered, this, [this]() {
        bool ok;
        QFont font = QFontDialog::getFont(&ok, this);
        if (ok) {
            controller->setCurrentFont(font);
        }
    });
}

void MainWindow::setupConnections() {
    connect(model->getScene(), &CustomGraphicsScene::sceneMousePressed,
            this, &MainWindow::handleMousePressed);
    connect(model->getScene(), &CustomGraphicsScene::sceneMouseMoved,
            this, &MainWindow::handleMouseMoved);
    connect(model->getScene(), &CustomGraphicsScene::sceneMouseReleased,
            this, &MainWindow::handleMouseReleased);
}

void MainWindow::onSelectAction() {
    controller->setEditorMode(EditorMode::Select);
    view->setDragMode(QGraphicsView::RubberBandDrag);
}

void MainWindow::onLineAction() {
    controller->setEditorMode(EditorMode::CreateLine);
    view->setDragMode(QGraphicsView::NoDrag);
}

void MainWindow::onRectAction() {
    controller->setEditorMode(EditorMode::CreateRect);
    view->setDragMode(QGraphicsView::NoDrag);
}

void MainWindow::onEllipseAction() {
    controller->setEditorMode(EditorMode::CreateEllipse);
    view->setDragMode(QGraphicsView::NoDrag);
}

void MainWindow::onTextAction() {
    controller->setEditorMode(EditorMode::CreateText);
    view->setDragMode(QGraphicsView::NoDrag);
}

void MainWindow::onTriangleAction() {
    controller->setEditorMode(EditorMode::CreateTriangle);
    view->setDragMode(QGraphicsView::NoDrag);
}

void MainWindow::onColorAction() {
    QColor color = QColorDialog::getColor(controller->getCurrentColor(),
                                        this, "Select Color");
    if (color.isValid()) {
        controller->setCurrentColor(color);
        controller->changeSelectedItemsColor(color);
    }
}

void MainWindow::onDeleteAction() {
    controller->deleteSelectedItems();
}

void MainWindow::onClearAction() {
    controller->clearAll();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Delete) {
        controller->deleteSelectedItems();
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::handleMousePressed(const QPointF& pos) {
    controller->mousePressed(pos);
}

void MainWindow::handleMouseMoved(const QPointF& pos) {
    controller->mouseMoved(pos);
}

void MainWindow::handleMouseReleased() {
    controller->mouseReleased();
}
