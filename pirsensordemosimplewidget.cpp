#include "pirsensordemosimplewidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QDateTime>

#include <QDebug>

#include "pirsensor.h"

static QTime sensorCoutStateIdleStartTime;

static const int sensorAoutId (0);
static const int sensorCoutId (1);

static const float sensorCoutThresholdHigh (3.0);
static const float sensorCoutThresholdLow (0.3);

static const QColor indicatorActiveColor (202, 103, 70); // orange
static const QColor indicatorIdleColor (116, 150, 44); // green

static const int indicatorDelay (2);

PIRSensorDemoSimpleWidget::PIRSensorDemoSimpleWidget(QWidget *parent) :
    QWidget(parent)
{
    PIRSensor sensor;

    QVBoxLayout *layout = new QVBoxLayout (this);

    QLabel *indicatorLabel = new QLabel ("Initializing...");
    QLabel *sensorAoutLabel = new QLabel;
    QLabel *sensorCoutLabel = new QLabel;

    layout->addWidget (indicatorLabel);
    layout->addWidget (sensorAoutLabel);
    layout->addWidget (sensorCoutLabel);

    indicatorLabel->setFont (QFont ("Sans", 48, 1));
    indicatorLabel->setAutoFillBackground (true);
    sensorAoutLabel->setFixedHeight (12);
    sensorCoutLabel->setFixedHeight (12);

    static const int refreshInterval (50);

    QTimer *refreshTimer = new QTimer (this);
    refreshTimer->setInterval (refreshInterval);

    connect (refreshTimer, &QTimer::timeout,
             [=, &sensor] ()
    {
        bool sensorCoutState (false);
        bool indicatorState (false);

        float sensorAoutValue = sensor.value (sensorAoutId);
        float sensorCoutValue = sensor.value (sensorCoutId);

        // qDebug () << "C-out:" << sensorCoutValue;

        QTime currentTime = QTime::currentTime ();

        if (sensorCoutValue > sensorCoutThresholdHigh)
        {
            sensorCoutState = false;
        }
        else if (sensorCoutValue < sensorCoutThresholdLow)
        {
            sensorCoutState = true;
            sensorCoutStateIdleStartTime = currentTime;
        }

        sensorAoutLabel->setText (QString ("A-out: %1").arg (sensorAoutValue));
        sensorCoutLabel->setText (QString ("C-out: %1").arg (sensorCoutState));

        if (sensorCoutStateIdleStartTime.secsTo (currentTime) >= indicatorDelay && sensorCoutState == false)
        {
            indicatorState = false;
        }
        else
        {
            indicatorState = true;
        }

        QPalette palette = indicatorLabel->palette ();
        QColor color;

        if (indicatorState)
        {
            indicatorLabel->setText ("Active");
            color = indicatorActiveColor;
        }
        else
        {
            indicatorLabel->setText ("Idle");
            color = indicatorIdleColor;
        }

        palette.setColor (QPalette::Background, color);
        indicatorLabel->setPalette (palette);
    });

    refreshTimer->start ();
}
