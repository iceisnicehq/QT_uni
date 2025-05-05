#include "mainwindow.h"
#include "graphiccontroller.h"
#include "graphicmodel.h"
#include "customgraphicsscene.h"
#include <QUndoStack>
#include <QActionGroup>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    undoStack = new QUndoStack(this);
    model = new GraphicModel(this);
    controller = new GraphicController(model, this);
    controller->setUndoStack(undoStack);

    setupUI();
    setupToolBar();
    setupConnections();

    // Set the controller for the scene
    model->getScene()->setController(controller);
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
    QAction* rhombusAction = toolBar->addAction("Rhombus");
    QAction* ellipseAction = toolBar->addAction("Ellipse");
    QAction* textAction = toolBar->addAction("Text");
    toolBar->addSeparator();
    QAction* colorAction = toolBar->addAction("Color");
    QAction* fontAction = toolBar->addAction("Font");
    toolBar->addSeparator();
    QAction* deleteAction = toolBar->addAction("Delete");
    QAction* clearAction = toolBar->addAction("Clear");
    toolBar->addSeparator();
    
    QAction* undoAction = undoStack->createUndoAction(this, tr("&Undo"));
    QAction* redoAction = undoStack->createRedoAction(this, tr("&Redo"));
    toolBar->addAction(undoAction);
    toolBar->addAction(redoAction);
    
    undoAction->setShortcut(QKeySequence::Undo);
    redoAction->setShortcut(QKeySequence::Redo);

    // Make tool actions checkable
    selectAction->setCheckable(true);
    lineAction->setCheckable(true);
    rectAction->setCheckable(true);
    rhombusAction->setCheckable(true);
    ellipseAction->setCheckable(true);
    textAction->setCheckable(true);

    // Group actions for mutual exclusivity
    QActionGroup* toolGroup = new QActionGroup(this);
    toolGroup->addAction(selectAction);
    toolGroup->addAction(lineAction);
    toolGroup->addAction(rectAction);
    toolGroup->addAction(rhombusAction);
    toolGroup->addAction(ellipseAction);
    toolGroup->addAction(textAction);
    toolGroup->setExclusive(true);

    // Default selection
    selectAction->setChecked(true);

    connect(selectAction, &QAction::triggered, this, &MainWindow::onSelectAction);
    connect(lineAction, &QAction::triggered, this, &MainWindow::onLineAction);
    connect(rectAction, &QAction::triggered, this, &MainWindow::onRectAction);
    connect(ellipseAction, &QAction::triggered, this, &MainWindow::onEllipseAction);
    connect(textAction, &QAction::triggered, this, &MainWindow::onTextAction);
    connect(colorAction, &QAction::triggered, this, &MainWindow::onColorAction);
    connect(deleteAction, &QAction::triggered, this, &MainWindow::onDeleteAction);
    connect(clearAction, &QAction::triggered, this, &MainWindow::onClearAction);
    connect(rhombusAction, &QAction::triggered, this, &MainWindow::onRhombusAction);
    connect(fontAction, &QAction::triggered, this, &MainWindow::onFontAction);
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

void MainWindow::onRhombusAction() {
    controller->setEditorMode(EditorMode::CreateRhombus);
    view->setDragMode(QGraphicsView::NoDrag);
}

void MainWindow::onFontAction() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        controller->setCurrentFont(font);
        controller->changeSelectedItemsFont(font);
    }
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
