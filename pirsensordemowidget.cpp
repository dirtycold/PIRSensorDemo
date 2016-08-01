#include "pirsensordemowidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QDateTime>

#include <QDebug>

#include "pirsensor.h"
#include "qcustomplot.h"

PIRSensorDemoWidget::PIRSensorDemoWidget(QWidget *parent)
    : QWidget(parent)
{
    PIRSensor sensor;

    static const int refreshInterval = 50;

    QLabel *label = new QLabel;
    label->setFont (QFont ("Sans", 36));
    label->setAutoFillBackground (true);
    label->setFixedHeight (60);

    QCustomPlot *plot = new QCustomPlot;
    QCPGraph *graph;

    plot->addGraph ();
    graph = plot->graph (0);
    graph->setPen (QPen (QColor (78, 90, 178)));
    graph->setBrush (QBrush (QColor (169, 169, 254)));
    graph->setAntialiasedFill (false);

    /*
    plot->addGraph ();
    graph = plot->graph (1);
    graph->setPen (QPen (QColor (60, 140, 180)));
    graph->setLineStyle (QCPGraph::lsNone);
    graph->setScatterStyle (QCPScatterStyle::ssDisc);
    */

    plot->xAxis->setTickLabelType (QCPAxis::ltDateTime);
    plot->xAxis->setDateTimeFormat ("mm:ss");
    plot->xAxis->setAutoTickStep (false);
    plot->xAxis->setTickStep (1000 * 2 / refreshInterval);
    // plot->axisRect ()->setupFullAxesBox ();
    plot->yAxis->setRange (0, 3.3);

    /*
    QLinearGradient plotGradient;
    plotGradient.setStart (0, 0);
    plotGradient.setFinalStop (0, 350);
    plotGradient.setColorAt (0, QColor (80, 80, 80));
    plotGradient.setColorAt (1, QColor (50, 50, 50));
    plot->setBackground (plotGradient);
    */

    QVBoxLayout *layout = new QVBoxLayout (this);
    layout->addWidget (label);
    layout->addWidget (plot);



    QTimer *timer = new QTimer (this);
    timer->setInterval (refreshInterval);
    timer->setSingleShot (false);

    connect (timer, &QTimer::timeout, [=, &sensor] ()
    {
        float value = sensor.value (0);

        static const float max = 3.3;
        static const float min = 0;
        float r = value / (max - min) + min;
        int red = r * 255;
        int green = (red + 80) % 255;
        int blue = (red + 160) % 255;

        QColor color (red, green, blue);

        // qDebug () << value << r << red << green << blue;

        label->setText (QString::number (value));
        QPalette palette = label->palette ();
        palette.setColor (QPalette::Background, color);
        label->setPalette (palette);

        static const int historyRange = 30;
        static const int historyRangeTick = historyRange * 1000 / refreshInterval;

        QCPGraph *graph;
        graph = plot->graph (0);
        double key = QDateTime::currentDateTime ().toMSecsSinceEpoch () * refreshInterval / 1000;
        graph->addData (key, value);
        graph->removeDataBefore (key - historyRangeTick);
        graph->setBrush (QBrush (color));
        // graph->rescaleValueAxis ();

        /*
        graph = plot->graph (1);
        graph->addData (key, value);
        graph->removeDataBefore (key - 200);
        // graph->rescaleValueAxis ();
        */

        plot->xAxis->setRange (key + 0.25, historyRangeTick, Qt::AlignRight);
        plot->replot ();
    });

    timer->start ();
}

PIRSensorDemoWidget::~PIRSensorDemoWidget()
{

}
