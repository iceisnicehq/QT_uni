#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the main window
    QWidget window;
    window.setWindowTitle("Лабораторная работа 0");

    // Create a button with a question
    QPushButton button("Что ты будешь делать, если ничего не получится?");

    // Create a label to display the GIF
    QLabel gifLabel;
    gifLabel.setAlignment(Qt::AlignCenter);

    // Connect the button click event to load and play the GIF
    QObject::connect(&button, &QPushButton::clicked, [&]() {
        QMovie *movie = new QMovie("C:\\Users\\user\\Downloads\\zenbook\\gif.gif");
        gifLabel.setMovie(movie);
        movie->start();
    });

    // Create a vertical layout and add the button and GIF label
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(&button);
    layout->addWidget(&gifLabel);

    // Set the layout for the main window
    window.setLayout(layout);

    // Show the main window
    window.show();

    // Start the application event loop
    return app.exec();
}
