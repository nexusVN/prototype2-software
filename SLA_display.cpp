#include "SLA_display.h"
#include "ui_SLA_display.h"
#include "SLA_com.h"
#include <QRegExp>
#include <QTimer>

/*
 * GLOBAL VARIABLE
 */
printerCom spiCom;
struct CoordData m_data[MAX_LAYER_ID];
uint16_t numPacket;

/*
 * FUNCTION
 */

printerDisplay::printerDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::printerDisplay)
{
    ui->setupUi(this);

    /*remove title bar*/
    setWindowFlags( Qt::CustomizeWindowHint );

    /*initialize state for printer*/
    uint8_t state = STATE_INIT;    

    /*the 1ms timer trigger copy data packet into SPI buffer*/
    if(STATE_PRINTING == state)
    {
        /* 1 ms trigger copy packet data */
        QTimer *timer_1ms = new QTimer(this);
        connect(timer_1ms, SIGNAL(timeout()), &spiCom, SLOT(updateDataPacket()));
        /*start timer 1ms*/
        timer_1ms->start(1);
    }

    /*demo idea*/
    QTimer *timer_1000ms = new QTimer(this);
    connect(timer_1000ms, SIGNAL(timeout()),this, SLOT(autoDisplay3DModel()));
    timer_1000ms->start(1000);

    /*invoke function on_listItem_clicked() when double click item in listWidget  */
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                this, SLOT(on_listItem_clicked(QListWidgetItem*)));

}

printerDisplay::~printerDisplay()
{
    delete ui;
}

/*demo idea*/
void printerDisplay::autoDisplay3DModel()
{
    if(counter_1s == 6)
    {
        ui->label->setPixmap(QPixmap(":/Pics/Pic_1.png"));
    }
    else if (counter_1s == 5)
    {
        ui->label->setPixmap(QPixmap(":/Pics/Pic_2.png"));
    }
    else if(counter_1s == 4)
    {
        ui->label->setPixmap(QPixmap(":/Pics/Pic_3.png"));
    }
    else if(counter_1s == 3)
    {
        ui->label->setPixmap(QPixmap(":/Pics/Pic_4.png"));
    }
    else if(counter_1s == 2)
    {
        ui->label->setPixmap(QPixmap(":/Pics/Pic_5.png"));
    }
    else if(counter_1s == 1)
    {
        ui->label->setPixmap(QPixmap(":/Pics/Pic_6.png"));
    }
    else
    {
        counter_1s = 6;
    }
    counter_1s--;
}

/****************************************************************
 * Function Name : on_loadButton_clicked
 * Description   : detect gcode files stored in usb
 *                  load selected files.
 * Returns       : None
 * Params        : items which inserted from usb
 ****************************************************************/
void printerDisplay::on_loadButton_clicked()
{
    /*
     * open browser to get file directory and its name
     * Current using usb folder as simulation for usb driver.
     */
    QStringList fileDir = QFileDialog::getOpenFileNames(
                        this,
                        "Open File",
                        "/home/thinhvu/usr/qtApp/ControlPanel3D_v4/usb_folder",
                        "GCODE file (*.gcode)"
                        );


    /* Display folder name only by using QFileInfo.filename */
    for(int indexFile=0; indexFile<fileDir.size();indexFile++)
    {
        //ui->listWidget->addItem(QFileInfo(fileDir.at(indexFile)).fileName());
        ui->listWidget->addItem(fileDir.at(indexFile));
    }
}

/****************************************************************
 * Function Name : on_listItem_clicked
 * Description   :  list all inserted items from usb,
 *                  verify valid input
 *                  extract into data structure
 * Returns       : None
 * Params        : items which inserted from usb
 ****************************************************************/
void printerDisplay::on_listItem_clicked(QListWidgetItem* item)
{
    /*Debug*/
    qDebug() << "usb path: " << item->text();

    /*get file name*/
    QString gcodefileName = QFileInfo(item->text()).fileName();
    /*get file size*/
    qint64 gcodeSize = QFileInfo(item->text()).size();

    qDebug() << "file size :" << gcodeSize;

    /*Input file must be smaller than 32Mb*/
    if(QFileInfo(item->text()).size() < MAX_DATA_SIZE)
    {
        /* msg box to confirm whether file is chosen */
        int ret = QMessageBox::question(
                        this,
                        tr("Confirm"),
                        "The file: " + gcodefileName +  " shall be selected.\n"
                        "Do you want to load this file?",
                        QMessageBox::Yes,
                        QMessageBox::No
                        );
        /*
         * if confirm is yes
         * Then copy selected file to default folder
         * Since copy command cannot overwrite, checking existed file and removing is a must.
         */
        if (QMessageBox::Yes == ret)
        {
            if (QFile::exists("/home/thinhvu/usr/qtApp/ControlPanel3D_v4/3Dfile_save/"+ gcodefileName))
            {
                qDebug() << "file existed, remove file";
                QFile::remove("/home/thinhvu/usr/qtApp/ControlPanel3D_v4/3Dfile_save/"+ gcodefileName);
            }

            /*
             * extract file into data structure as well as verify valid input file
             */
            QFile mFile(item->text());

            if(!mFile.open(QFile::ReadOnly | QFile::Text))
            {
                qDebug() << "could not open file for reading";
                return;
            }

            QTextStream readfile(&mFile);
            QString line;

            do{
                line = readfile.readLine();

                /*extract*/
                QRegExp m_regexp("\\w(\\d+)\\t\\w(\\d+)\\t\\w(\\d+)");

                if (m_regexp.indexIn(line) != -1)
                {
                    m_data[numPacket].Gcommand = (uint8_t)m_regexp.cap(1).toUShort();
                    m_data[numPacket].Xcoord = m_regexp.cap(2).toUShort();
                    m_data[numPacket].Ycoord = m_regexp.cap(3).toUShort();
                }
                numPacket++;
            }while(!line.isNull());

            mFile.close();
            qDebug() << "file read";

            /*Debug*/
            for(int i=0; i<numPacket; i++)
            {
                qDebug() << "G: " << m_data[i].Gcommand << "X: " << m_data[i].Xcoord << "Y: " << m_data[i].Ycoord;
            }


            /*if valid file then*/
            /* copy for later use */
            qDebug() << "copy file";
            qDebug() << QFile::copy(item->text(), "/home/thinhvu/usr/qtApp/ControlPanel3D_v4/3Dfile_save/" + gcodefileName);
            QMessageBox::information(this,
                                     tr("Confirm"),
                                     tr("The file load successfully"),
                                     QMessageBox::Ok
                                     );
            ui->loadstatusLabel->setText("Ready to PRINT");

            /*update state to ready when verify input file complete*/
            state = STATE_READY;

            /*otherwise message errors*/
        }

        else
        {
            /* do nothing*/
        }
    }

    else
    {
        QMessageBox::information(this,
                             tr("ERROR"),
                             tr("The file load must be smaller than 32MB"),
                             QMessageBox::Abort
                             );
    }

}

/****************************************************************
 * Function Name : on_removeButton_clicked
 * Description   : Remove selected item in list file
 * Returns       : None
 * Params        : None
 ****************************************************************/
void printerDisplay::on_removeButton_clicked()
{
    /*select item want to delete*/
    QList<QListWidgetItem*> selectedItm = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, selectedItm)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

/****************************************************************
 * Function Name : on_printButton_clicked
 * Description   : Performs a SPI transaction when print button clicked
 * Returns       : None
 * Params        : None
 ****************************************************************/
void printerDisplay::on_printButton_clicked()
{
    if(state == STATE_READY)
    {
        state = STATE_PRINTING;
    }
    else
    {
        qDebug() << "size of 1 packet" << sizeof(m_data[0]);
        QMessageBox::information(this,
                             tr("ERROR"),
                             tr("Please, select printing file"),
                             QMessageBox::Abort
                             );
    }
}

/****************************************************************
 * Function Name : on_spiDebugButton_clicked
 * Description   : Performs a SPI transaction when debug button clicked
 * Returns       : None
 * Params        : None
 ****************************************************************/
void printerDisplay::on_spiDebugButton_clicked()
{
    /*define tx and rx data for debuging*/
    uint8_t tx[] = {
            0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6,
            0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,\
            0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,\
            0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6,\
            0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6,\
            0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6
        };
    uint8_t rx[ARRAY_SIZE(tx)] = {0,};

    /*invoke transmit*/
    spiCom.SpiTransferDebug(tx, rx, sizeof(tx));

    /*receive tx packet and display*/
    uint8_t ii;
    QStringList spiString;
    for(ii=0;ii<ARRAY_SIZE(tx);ii++)
    {
        /*if detect element 6th then make a new line*/
        if(((ii+1) % 6)==0)
        {
            /*convert received data into hex type*/
            spiString << QString::number(rx[ii],16).toUpper() << "\n";
        }
        else
        {
            spiString << QString::number(rx[ii],16).toUpper();
        }

    }
    /*display purpose: join string with space*/
    ui->spilabel->setText(spiString.join(" "));
}
