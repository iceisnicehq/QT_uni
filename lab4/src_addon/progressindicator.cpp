#include "progressindicator.h"


ProgressIndicator::ProgressIndicator(QWidget *parent)
    : QWidget(parent), m_progressValue(0), m_maximumValue(100), m_minimumValue(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void ProgressIndicator::setProgressValue(int value)
{
    if (value < m_minimumValue)
        value = m_minimumValue;
    if (value > m_maximumValue)
        value = m_maximumValue;

    m_progressValue = value;
    update();
}

int ProgressIndicator::progressValue() const
{
    return m_progressValue;
}

void ProgressIndicator::setMaximumValue(int value)
{
    m_maximumValue = value;
    update();
}

int ProgressIndicator::maximumValue() const
{
    return m_maximumValue;
}

void ProgressIndicator::setMinimumValue(int value)
{
    m_minimumValue = value;
    update();
}

int ProgressIndicator::minimumValue() const
{
    return m_minimumValue;
}

void ProgressIndicator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    QRectF outerRect(0, 0, side, side);
    outerRect.moveCenter(rect().center());

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::gray);
    painter.drawEllipse(outerRect);

    painter.setBrush(Qt::blue);
    int spanAngle = static_cast<int>(360 * (static_cast<double>(m_progressValue - m_minimumValue) / (m_maximumValue - m_minimumValue)));
    painter.drawPie(outerRect, 90 * 16, -spanAngle * 16);

    painter.setPen(Qt::white);
    QFont font = painter.font();
    int fontSize = static_cast<int>(side * 0.15);
    font.setPointSize(fontSize);
    painter.setFont(font);

    QString progressText = QString("%1%").arg((static_cast<double>(m_progressValue - m_minimumValue) / (m_maximumValue - m_minimumValue)) * 100, 0, 'f', 1);

    QRectF textRect = outerRect;
    textRect.adjust(10, 10, -10, -10);
    painter.drawText(textRect, Qt::AlignCenter, progressText);
}

void ProgressIndicator::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y() / 120;
    setProgressValue(m_progressValue + delta);
}
