#include <SLA_com.h>
#include <QDebug>

#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdint.h>
#include<linux/spi/spidev.h>

static struct spi_ioc_transfer spidev1_cfg;

printerCom::printerCom()
{
    bits = 8;
    mode = 3;
    speed = 500000;
    SpiConfig();
}

/**
 * CPOL indicates the initial clock polarity
 * CPOL=0: the clock starts low, the first (leading) edge is rising, and the second (trailing) edge is falling.
 * CPOL=1: the clock starts high, the first (leading) edge is falling.
 *
 * CPHA indicates the clock phase used to sample data
 * CPHA=0: sample on the leading edge
 * CPHA=1: sample on the trailing edge.
 *
 * Example: CPOL = 0; CPHA = 0 => (0,0)
 * SPI_MODE_0 (0,0): the clock starts low and sample at leading edge
 * SPI_MODE_1 (0,1): the clock starts low and sample at trailing edge
 * SPI_MODE_2 (1,0): the clock starts high and sample at leading edge
 * SPI_MODE_3 (1,1): the clock starts high and sample at trailing edge
 */
int printerCom::SpiConfig()
{
    /*
     * File handle and loop counter
     * Sending only a single char
     * 8-bits per word, SPI mode 3
     * Speed is 1 MHz
     * The following calls set up the SPI bus properties
     */
    fd_spi = open(SPI_PATH, O_RDWR);
    if (fd_spi < 0)
    {
        qDebug() << "SPI Error: Can't open device.";
        return -1;
    }

    /*
     * spi mode
     */
    if (ioctl(fd_spi, SPI_IOC_WR_MODE, &mode)==-1)
    {
        qDebug() << "SPI: Can't set SPI mode.";
        return -1;
    }

    if (ioctl(fd_spi, SPI_IOC_RD_MODE, &mode)==-1)
    {
        qDebug() << "SPI: Can't get SPI mode.";
        return -1;
    }

    /*the number of bits in each SPI transfer word*/
    if (ioctl(fd_spi, SPI_IOC_WR_BITS_PER_WORD, &bits)==-1)
    {
        qDebug() << "SPI: Can't set bits per word.";
        return -1;
    }

    /*
     * max speed WRITE
     */
    if (ioctl(fd_spi, SPI_IOC_WR_MAX_SPEED_HZ, &speed)==-1)
    {
        qDebug() << "SPI: Can't set max speed HZ";
        return -1;
    }

    /*
     * max speed READ
     */
    if (ioctl(fd_spi, SPI_IOC_RD_MAX_SPEED_HZ, &speed)==-1)
    {
        qDebug() << "SPI: Can't get max speed HZ.";
        return -1;
    }

    /*
     * Some devices may use eight bit words.
     * Others may use different word lengths,
     * such as streams of 12-bit or 20-bit digital samples.
     */
    if (ioctl(fd_spi, SPI_IOC_RD_BITS_PER_WORD, &bits)==-1)
    {
        qDebug() << "SPI: Can't get bits per word.";
        return -1;
    }

    // Check that the properties have been set
    qDebug("spiconfig fd: %d ", fd_spi);
    qDebug("SPI Mode is: %d", mode);
    qDebug("SPI Bits is: %d", bits);
    qDebug("SPI Speed is: %d", speed);

    /*
     * Initialize the spi_ioc_transfer structure kernel version 4.4.54
     */
    spidev1_cfg.tx_buf = 0;
    spidev1_cfg.rx_buf = 0;
    spidev1_cfg.pad = 0;
    spidev1_cfg.tx_nbits = 0;
    spidev1_cfg.rx_nbits = 0;
    spidev1_cfg.len = 0;
    spidev1_cfg.speed_hz = speed;
    spidev1_cfg.delay_usecs = 0;
    spidev1_cfg.bits_per_word = bits;
    spidev1_cfg.cs_change = 0;

    return 0;
}

/****************************************************************
 * Function Name : SpiTransfer
 * Description   : Performs a SPI transaction
 * Returns       : 0 is success, -1 is failure
 * Params        @transmitData: Points to the buffer containing the data
 *               to be sent
 *               @receiveData: Points to the buffer into which the
 *               received bytes are stored
 ****************************************************************/
int printerCom::SpiTransfer(struct CoordData *transmitData, uint8_t *receiveData, uint16_t dataLength)
{

    spidev1_cfg.tx_buf = (uint64_t)transmitData;
    spidev1_cfg.rx_buf = (uint64_t)receiveData;
    spidev1_cfg.len = dataLength;

    /* Perform a SPI Transaction */
    if (ioctl(fd_spi, SPI_IOC_MESSAGE(1), &spidev1_cfg)<0)
    {
        qDebug("SPI: SPI_IOC_MESSAGE Failed ");
        return -1;
    }
    return 0;
}
