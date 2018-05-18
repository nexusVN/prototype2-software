#ifndef SPICOM_H
#define SPICOM_H

#include <SLA_typedef.h>

#define SPI_PATH "/dev/spidev1.0"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

using namespace std;

class printerCom: public QObject
{
    Q_OBJECT

public:
   printerCom();  // Constructor
   int SpiConfig();
   int SpiTransfer(struct CoordData *transmitData,  uint16_t *receiveData, uint16_t dataLength);
   int SpiTransferDebug(uint8_t *transmitData, uint8_t *receiveData, uint16_t dataLength);

signals:
    void update_printerState(uint8_t state);

public slots:
    void update_dataPacket();

private:
    int fd_spi;
    uint8_t bits;
    uint8_t mode;
    uint32_t speed;
};

extern printerCom printerCom_o;

#endif // SPICOM_H
