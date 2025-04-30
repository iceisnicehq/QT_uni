#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

#include <QWidget>
#include <QPainter>
#include <QWheelEvent>

class ProgressIndicator : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressIndicator(QWidget *parent = nullptr);

    void setProgressValue(int value);
    int progressValue() const;

    void setMaximumValue(int value);
    int maximumValue() const;

    void setMinimumValue(int value);
    int minimumValue() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    int m_progressValue;
    int m_maximumValue;
    int m_minimumValue;
};
#endif // PROGRESSINDICATOR_H
