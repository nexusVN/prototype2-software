#ifndef SLA_DISPLAY_H
#define SLA_DISPLAY_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidgetItem>

#include <SLA_com.h>

#define MAX_LAYER_ID    5000
#define MAX_PACKET_ID	5000

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

    void on_resetButton_clicked();

    void on_cancelButton_clicked();

    void on_commandButton_clicked();

private:
    Ui::printerDisplay *ui;
};

struct CoordData{
    uint16_t Xcoord;
    uint16_t Ycoord;
    uint8_t Gcommand;
};

extern struct CoordData m_data[MAX_LAYER_ID];

#endif // SLA_DISPLAY_H
