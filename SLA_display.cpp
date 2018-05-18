#include "SLA_display.h"
#include "ui_SLA_display.h"
#include "SLA_com.h"
#include <QRegExp>
#include <QTimer>

/*
 * GLOBAL VARIABLE
 */

printerCom printerCom_o;

struct CoordData m_data[MAX_LAYER_ID];
uint16_t numPacket=0;
uint8_t packetLength;
uint8_t packetLeft;

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

    /*the 1ms timer trigger copy data packet into SPI buffer*/
    timer_1ms = new QTimer(this);
    connect(timer_1ms, SIGNAL(timeout()), &printerCom_o, SLOT(update_dataPacket()));

    /*trigger update state from communication module*/
    connect(&printerCom_o,SIGNAL(update_printerState(uint8_t)),
                this, SLOT(set_printerState(uint8_t)));

    currentRow = 0;
    inStoredPath = QCoreApplication::applicationDirPath() + "/3Dfile_stored/";
    exStoredPath = QCoreApplication::applicationDirPath() + "/usb_folder/";

    display_listWidget();
}

printerDisplay::~printerDisplay()
{
    delete ui;
}

void printerDisplay::display_listWidget()
{
    QDir dir( inStoredPath );

    QStringList filters;
    filters << "*.gcode";

    dir.setNameFilters( filters );
    QFileInfoList list = dir.entryInfoList( filters, QDir::Files);


    if (dir.count())
    {
        m_item = new QListWidgetItem[dir.count()];
        qDebug() << "exist file" << (dir.count());
        for(uint8_t ii = 0; ii<dir.count(); ii++)
        {
            (m_item+ii)->setData(Qt::UserRole, list.at(ii).filePath());
            (m_item+ii)->setText(list.at(ii).baseName());
            ui->listWidget->addItem(m_item+ii);
        }
        ui->heading_fileLoad->setText("");
    }

    else
    {
        ui->heading_fileLoad->setText("LOAD YOUR FILE");
        qDebug() << "NO exist file";
    }
    qDebug() << "App path : " << inStoredPath;

}

/****************************************************************
 * Function Name : on_button_loadFile_clicked
 * Description   : detect gcode files stored in usb
 *                  load selected files.
 * Returns       : None
 * Params        : items which inserted from usb
 ****************************************************************/
void printerDisplay::on_button_loadFile_clicked()
{

    /*
     * open browser to get file directory and its name
     * Current using usb folder as simulation for usb driver.
     */
    QStringList fileDirPath = QFileDialog::getOpenFileNames(
                        this,
                        "Select File",
                        exStoredPath,
                        "GCODE file (*.gcode)"
                        );

    /*scan the number of items in the QStringlist*/
    for(int ii=0; ii<fileDirPath.size(); ii++)
    {
        m_item = new QListWidgetItem[fileDirPath.size()];

        /*get file name*/
        QString gcodefileName = QFileInfo(fileDirPath.at(ii)).baseName();
        QString gcodefullName = QFileInfo(fileDirPath.at(ii)).fileName();

        /*Input file must be smaller than 32Mb*/
        if(QFileInfo(fileDirPath.at(ii)).size() < MAX_DATA_SIZE)
        {
            /*copy selected file into stored folder*/
            QFile::copy(fileDirPath.at(ii),inStoredPath + gcodefullName);

            QString gcodefilePath = inStoredPath + gcodefullName;

            (m_item+ii)->setData(Qt::UserRole, gcodefilePath);
            (m_item+ii)->setText(gcodefileName);
            ui->listWidget->addItem(m_item+ii);

            ui->heading_fileLoad->setText("FILE LOADED SUCCESSFULLY");
        }
        else
        {
            QMessageBox::information(this,
                                 tr("ERROR"),
                                 "The file" + gcodefileName + "must be smaller than 32MB",
                                 QMessageBox::Abort
                                 );
        }
    }
}

/****************************************************************
 * Function Name : on_button_removeFile_clicked
 * Description   : Remove selected item in list file
 * Returns       : None
 * Params        : None
 ****************************************************************/
void printerDisplay::on_button_removeFile_clicked()
{
    /*select item want to delete*/
    QList<QListWidgetItem*> selectedItm = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, selectedItm)
    {
        QString gcodefilePath = item->data(Qt::UserRole).toString();
        /*remove selected file*/
        QFile::remove(gcodefilePath);
        ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

/****************************************************************
 * Function Name : on_button_selectFileUp_clicked
 * Description   : select item in list file
 * Returns       : None
 * Params        : None
 ****************************************************************/
void printerDisplay::on_button_selectFileUp_clicked()
{
    if(currentRow == 0)
    {
        currentRow = ui->listWidget->count()-1;

    }
    else
    {
        currentRow = currentRow - 1;
    }

    ui->listWidget->setCurrentRow(currentRow);
    qDebug() << "current Row" << currentRow;

    ui->heading_fileLoad->setText("");
}

/****************************************************************
 * Function Name : on_button_selectFileDown_clicked
 * Description   : select item in list file
 * Returns       : None
 * Params        : None
 ****************************************************************/
void printerDisplay::on_button_selectFileDown_clicked()
{
    int addedItem = (ui->listWidget->count()-1);
    if(currentRow >= addedItem)
    {
        currentRow = 0;
    }
    else
    {
        currentRow = currentRow + 1;
    }

    qDebug() << "count" << addedItem;
    ui->listWidget->setCurrentRow(currentRow);
    qDebug() << "current Row" << currentRow;
}

/****************************************************************
 * Function Name : on_button_print_clicked
 * Description   : Performs a SPI transaction when print button clicked
 * Returns       : None
 * Params        : None
 ****************************************************************/
void printerDisplay::on_button_print_clicked()
{
    QListWidgetItem* item = ui->listWidget->currentItem();

    /*Debug*/
    QString gcodefilePath = item->data(Qt::UserRole).toString();
    qDebug() << "usb path: " << gcodefilePath;

    /*get file name*/
    QString gcodefileName = QFileInfo(item->text()).fileName();

    /* msg box to confirm whether file is chosen */
    int ret = QMessageBox::question(
                    this,
                    tr("Confirm"),
                    "The file: " + gcodefileName +  " shall be printed.\n"
                    "Do you want to print this file?",
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
        /*
         * extract file into data structure as well as verify valid input file
         */
        QFile mFile(gcodefilePath);

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
                numPacket++;
            }
        }while(!line.isNull());

        mFile.close();
        qDebug() << "file read";

        packetLength = numPacket / NUM_PACKET_SEND;
        packetLeft = numPacket % NUM_PACKET_SEND;
        /*Debug*/
        qDebug() << "numPacket: " << numPacket;
        for(int i=0; i<numPacket; i++)
        {
            qDebug() << "G: " << m_data[i].Gcommand << "X: " << m_data[i].Xcoord << "Y: " << m_data[i].Ycoord;
        }

        /*update state to ready when verify input file complete*/
        set_printerState(STATE_READY);
    }

    else
    {
        /* do nothing*/
    }



    if(get_printerState() == STATE_READY)
    {
        set_printerState(STATE_PRINTING);
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
 * Function Name : on_button_spiDebug_clicked
 * Description   : Performs a SPI transaction when debug button clicked
 * Returns       : None
 * Params        : None
 ****************************************************************/
void printerDisplay::on_button_spiDebug_clicked()
{
    /*define tx and rx data for debuging*/
    uint8_t tx[] = {
            0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6,
            0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,\
            0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,\
            0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6,\
            0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6,\
            0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6,\
            0x91, 0x92, 0x93, 0x94, 0x95, 0x96,\
            0x81, 0x82, 0x83, 0x84, 0x85, 0x86,\
            0x71, 0x72, 0x73, 0x74, 0x75, 0x76
        };
    uint8_t rx[ARRAY_SIZE(tx)] = {0,};

    /*invoke transmit*/
    printerCom_o.SpiTransferDebug(tx, rx, sizeof(tx));

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
    ui->output_spi->setText(spiString.join(" "));
}

/****************************************************************
 * Function Name : set_printerState
 * Description   : manage printer state
 * Returns       : None
 * Params        : uint8_t state
 ****************************************************************/
void printerDisplay::set_printerState(uint8_t state)
{
    m_state = state;

    switch (m_state)
    {
    case STATE_INIT:
        /*do nothing*/
        break;
    case STATE_READY:
        /*do nothing*/
        break;
    case STATE_PRINTING:
        qDebug()<< "STATE PRINTING";
        /*start timer 1ms*/
        timer_1ms->start(100);
        break;
    case STATE_COMPLETE:
        qDebug()<< "STATE COMPLETE";
        /*start timer 1ms*/
        timer_1ms->stop();
        break;
    default:
        break;
    }
}

uint8_t printerDisplay::get_printerState()
{
    return m_state;
}


void printerDisplay::on_button_selectTab_clicked()
{
    static uint8_t currentTab = (uint8_t)ui->tabWidget->currentIndex();
    uint8_t maxTab = (uint8_t)(ui->tabWidget->count()-1);
    if(currentTab<maxTab)
    {
        currentTab++;
    }
    else
    {
        currentTab = 0;
    }
    ui->tabWidget->setCurrentIndex(currentTab);
    qDebug() << "current tab" << currentTab;
}

void printerDisplay::on_button_connectSerialPort_clicked()
{


}
