#include "SLA_display.h"
#include "SLA_com.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    printerDisplay w;
    w.show();

    return a.exec();
}
