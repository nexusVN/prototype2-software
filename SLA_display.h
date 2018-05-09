#ifndef SLA_DISPLAY_H
#define SLA_DISPLAY_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidgetItem>

#include <SLA_com.h>
#include <SLA_typedef.h>

namespace Ui {
class printerDisplay;
}

class printerDisplay : public QMainWindow
{
    Q_OBJECT

public:
    explicit printerDisplay(QWidget *parent = 0);
    ~printerDisplay();

private slots:
    void on_loadButton_clicked();
    void on_listItem_clicked(QListWidgetItem*);

    void on_removeButton_clicked();

    void on_printButton_clicked();

    void on_spiDebugButton_clicked();

    void autoDisplay3DModel();

private:
    Ui::printerDisplay *ui;
    uint8_t state;
    double counter_1s=6;
};



#endif // SLA_DISPLAY_H
