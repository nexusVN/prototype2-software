#include "SLA_display.h"
#include "SLA_com.h"
#include "SLA_state.h"
#include "SLA_typedef.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    printerDisplay printerDisplay_o;
    printerDisplay_o.show();

    return a.exec();
}
