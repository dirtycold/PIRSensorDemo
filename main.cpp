#include "pirsensordemowidget.h"
#include "pirsensordemosimplewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // PIRSensorDemoWidget w;
    PIRSensorDemoSimpleWidget w;
    w.show();

    return a.exec();
}
