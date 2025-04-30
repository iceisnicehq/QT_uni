#include "spiralprogressindicator.h"
#include <QPainterPath>

SpiralProgressIndicator::SpiralProgressIndicator(QWidget *parent)
    : QWidget(parent), m_progressValue(0), m_maximumValue(100), m_minimumValue(0), m_targetValue(0)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(&m_animationTimer, &QTimer::timeout, this, &SpiralProgressIndicator::animateProgress);
    m_animationTimer.start(16); // ~60 FPS
}

void SpiralProgressIndicator::setProgressValue(int value)
{
    m_targetValue = qBound(m_minimumValue, value, m_maximumValue);
}

int SpiralProgressIndicator::progressValue() const
{
    return m_progressValue;
}

void SpiralProgressIndicator::setMaximumValue(int value)
{
    m_maximumValue = value;
    update();
}

int SpiralProgressIndicator::maximumValue() const
{
    return m_maximumValue;
}

void SpiralProgressIndicator::setMinimumValue(int value)
{
    m_minimumValue = value;
    update();
}

int SpiralProgressIndicator::minimumValue() const
{
    return m_minimumValue;
}

void SpiralProgressIndicator::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    QRectF outerRect(0, 0, side, side);
    outerRect.moveCenter(rect().center());

    double progressRatio = static_cast<double>(m_progressValue - m_minimumValue) / (m_maximumValue - m_minimumValue);

    QPen pen;
    pen.setWidth(4);
    QConicalGradient gradient(outerRect.center(), 0);
    gradient.setColorAt(0.0, Qt::blue);
    gradient.setColorAt(1.0, Qt::red);
    pen.setBrush(gradient);
    painter.setPen(pen);

    int numTurns = 3; // Number of spiral turns
    double angleStep = 360.0 / (numTurns * 100); // Angle step per unit progress

    QPainterPath spiralPath;
    QPointF center = outerRect.center();
    double radiusStep = side / (2.0 * numTurns * 100);

    for (int i = 0; i <= progressRatio * numTurns * 100; ++i)
    {
        double angle = i * angleStep;
        double radius = i * radiusStep;
        double x = center.x() + radius * qCos(qDegreesToRadians(angle));
        double y = center.y() - radius * qSin(qDegreesToRadians(angle));

        if (i == 0)
            spiralPath.moveTo(x, y);
        else
            spiralPath.lineTo(x, y);
    }

    painter.drawPath(spiralPath);

    // Draw progress text
    painter.setPen(Qt::black);
    QFont font = painter.font();
    font.setPointSize(static_cast<int>(side * 0.1));
    painter.setFont(font);

    QString progressText = QString("%1%").arg(progressRatio * 100, 0, 'f', 1);
    painter.drawText(outerRect, Qt::AlignCenter, progressText);
}

void SpiralProgressIndicator::wheelEvent(QWheelEvent *event)
{
    int delta = event->angleDelta().y() / 120;
    setProgressValue(m_targetValue + delta);
}

void SpiralProgressIndicator::animateProgress()
{
    if (m_progressValue != m_targetValue)
    {
        int step = (m_targetValue > m_progressValue) ? 1 : -1;
        m_progressValue += step;
        update();
    }
}
