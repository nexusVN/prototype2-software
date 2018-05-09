#ifndef SLA_TYPEDEF_H
#define SLA_TYPEDEF_H

#include <QMessageBox>
#include <QDataStream>
#include <QDebug>

#define NUM_PACKET_SEND 86          /*NUMBER OF PACKET SEND IN A PERIOD OF TIME */
#define MAX_LAYER_ID    5000        /*MAXIMUM LAYER SUPPORT*/
#define MAX_PACKET_ID	5000        /*MAXIMUM PACKET (COMMAND) SUPPORT*/
#define MAX_DATA_SIZE   32000000    /*MAXIMUM INPUT FILE SIZE SUPPORT*/

struct CoordData{
    uint16_t Xcoord;
    uint16_t Ycoord;
    uint8_t Gcommand;
};

enum printerState {
    STATE_INIT,
    STATE_READY,
    STATE_PRINTING
};

extern struct CoordData m_data[MAX_LAYER_ID];
extern uint16_t numPacket;

#endif // SLA_TYPEDEF_H
