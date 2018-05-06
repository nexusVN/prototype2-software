#include "SLA_display.h"
#include "ui_SLA_display.h"
#include "SLA_com.h"
#include <QRegExp>

#include <QDebug>
#include <QMessageBox>

/*
 * GLOBAL VARIABLE
 */
printerCom spiCom;
struct CoordData m_data[MAX_LAYER_ID];

/*
 * FUNCTION
 */

printerDisplay::printerDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::printerDisplay)
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
                this, SLOT(on_listItem_clicked(QListWidgetItem*)));

}

printerDisplay::~printerDisplay()
{
    delete ui;
}

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

void printerDisplay::on_listItem_clicked(QListWidgetItem* item)
{
    /*Debug*/
    qDebug() << "usb path: " << item->text();

    QString gcodefileName = QFileInfo(item->text()).fileName();
    qint64 gcodeSize = QFileInfo(item->text()).size();

    qDebug() << "file size :" << gcodeSize;

    /*Input file must be smaller than 32Mb*/
    if(QFileInfo(item->text()).size()<32000000)
    {
        /* msg box to confirm */
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
            int lineCount = 0;

            do{
                line = readfile.readLine();

                /*extract*/
                QRegExp m_regexp("\\w(\\d+)\\t\\w(\\d+)\\t\\w(\\d+)");

                if (m_regexp.indexIn(line) != -1)
                {
                    m_data[lineCount].Gcommand = (uint8_t)m_regexp.cap(1).toUShort();
                    m_data[lineCount].Xcoord = m_regexp.cap(2).toUShort();
                    m_data[lineCount].Ycoord = m_regexp.cap(3).toUShort();
                }
                lineCount++;
            }while(!line.isNull());

            mFile.close();
            qDebug() << "file read";

            for(int i=0;i<lineCount;i++)
            {
                qDebug() << "G: " << m_data[i].Gcommand << "X: " << m_data[i].Xcoord << "Y: " << m_data[i].Ycoord;
            }


            /*if valid file then*/
            /*copy */
            qDebug() << "copy file";
            qDebug() << QFile::copy(item->text(), "/home/thinhvu/usr/qtApp/ControlPanel3D_v4/3Dfile_save/" + gcodefileName);
            QMessageBox::information(this,
                                     tr("Confirm"),
                                     tr("The file load successfully"),
                                     QMessageBox::Ok
                                     );
            ui->loadstatusLabel->setText("Ready to PRINT");

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

void printerDisplay::on_removeButton_clicked()
{
    QList<QListWidgetItem*> selectedItm = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, selectedItm)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }
}

void printerDisplay::on_printButton_clicked()
{

//    uint8_t tx[] = {
//            0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6,
//            0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,\
//            0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,\
//            0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6,\
//            0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6,\
//            0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6
//        };
//    uint8_t rx[ARRAY_SIZE(tx)] = {
//            0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6,
//            0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,\
//            0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6,\
//            0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6,\
//            0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6,\
//            0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6
//    };

//    spiCom.SpiTransfer(tx, rx, sizeof(tx));

    uint8_t rx[sizeof(m_data)];
    spiCom.SpiTransfer(m_data, rx, sizeof(m_data));

    uint8_t ii;
    QStringList spiString;
//    for(ii=0;ii<ARRAY_SIZE(tx);ii++)
    for(ii=0;ii<sizeof(m_data);ii++)
    {
        if(((ii+1) % 6)==0)
        {
            spiString << QString::number(rx[ii],16).toUpper() << "\n";
        }
        else
        {
            spiString << QString::number(rx[ii],16).toUpper();
        }

    }
    ui->spilabel->setText(spiString.join(" "));
}

/* re-printing */
void printerDisplay::on_resetButton_clicked()
{

}

/* cancel current printing */
void printerDisplay::on_cancelButton_clicked()
{

}

void printerDisplay::on_commandButton_clicked()
{
    QStringList inputString, outputString;
    inputString << ui->spicommand->text();
//    spiCom.SpiTransfer(inputString, outputString, inputString.length());
}
