#ifndef QSERIALCANBUSLIB_H
#define QSERIALCANBUSLIB_H

// Important info
// Add "QT       += serialport" into *.pro file
// install serial port "sudo apt-get install libqt5serial*"

#include <QObject>
#include <QtCore>
#include <QSerialPort>
#include <QSerialPortInfo>


class QSerialCANBusLib : public QSerialPort

{
    Q_OBJECT

public:



    explicit QSerialCANBusLib(QString portname,quint16 speed, DataBits databits, Parity parity, StopBits stopbits, FlowControl flowcontrol);

//    static quint16 Baud460800 = 460800;


signals:

private:
     QSerialPort * serial ;
     QByteArray inputbytedata;
     QByteArray outputbytedata;
     QTimer * tmr;
      QTimer * exittimer;

public slots:

     QString SendDataToCanBus(QString data,  quint16 minresponselenght, quint64 timeoutmsec);
     QByteArray SendDataToCanBus(QByteArray data, quint16 minresponselenght,  quint64 timeoutmsec);

     QByteArray SendDataToCanBus(quint16 unit, quint16 command, quint32 data,  quint16 datalenght, quint16 minresponselenght, quint64 timeoutmsec);
};

#endif // QSERIALCANBUSLIB_H
