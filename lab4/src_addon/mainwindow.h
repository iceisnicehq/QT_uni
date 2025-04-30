#include "spiralprogressindicator.h"
#include <QMainWindow>
#include <QSlider>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    SpiralProgressIndicator *progressIndicator;
    QSlider *slider;
};
