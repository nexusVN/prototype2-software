#ifndef SLA_DISPLAY_H
#define SLA_DISPLAY_H

#include <QMainWindow>
#include <QFileDialog>
#include <QListWidgetItem>
//#include <QTouchEvent>

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
    uint8_t get_printerState();
    void display_listWidget();

signals:
    void update_printerStatus(uint8_t state);

private slots:
    void on_button_loadFile_clicked();

    void on_button_removeFile_clicked();

    void on_button_print_clicked();

    void on_button_spiDebug_clicked();

    void on_button_selectFileUp_clicked();

    void on_button_selectFileDown_clicked();

    void set_printerState(uint8_t state);

    void on_button_selectTab_clicked();

    void on_button_connectSerialPort_clicked();

private:
    Ui::printerDisplay *ui;
    QTimer *timer_1ms;
    uint8_t m_state;
    QListWidgetItem *m_item;
    uint8_t currentRow;
    QString inStoredPath;
    QString exStoredPath;
};

extern printerDisplay printerDisplay_o;



#endif // SLA_DISPLAY_H
