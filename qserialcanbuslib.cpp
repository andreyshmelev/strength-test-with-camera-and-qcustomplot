#include "qserialcanbuslib.h"


QSerialCANBusLib::QSerialCANBusLib(QString portname,quint16 speed, DataBits databits, Parity parity, StopBits stopbits, FlowControl flowcontrol)
{
    return;
    serial = new QSerialPort();

    serial->setPortName(portname);

    qDebug()<<(serial->portName()) << " serial->portName";

    if(serial->open(QIODevice::ReadWrite)){

        qDebug()<<(serial->portName()) << " Opened";

        if (!serial->setBaudRate(speed))
        {
            qDebug() << "Error" << serial->errorString();
        }

        if (!serial->setDataBits(databits))
        {
            qDebug() << "Error"<< serial->errorString();
        }

        if (!serial->setParity(parity))
        {
            qDebug() << "Error"<< serial->errorString();
        }

        if (!serial->setStopBits(stopbits))
        {
            qDebug() << "Error"<< serial->errorString();
        }


        if (!serial->setFlowControl(flowcontrol))
        {
            qDebug() << "Error"<< serial->errorString();
        }
    }
    else {
        qDebug() << "Error com port not opened";
    }

}


QByteArray QSerialCANBusLib::SendDataToCanBus(QByteArray data, quint16 minresponselenght, quint64 timeoutmsec )
{
    QSerialPort * serial1 = new QSerialPort();

    serial1->setPortName("ttyAMA0");

    qDebug()<<(serial1->portName()) << " serial->portName";

    if(serial1->open(QIODevice::ReadWrite)){

        qDebug()<<(serial1->portName()) << " Opened";

        if (!serial1->setBaudRate(460800))
        {
            qDebug() << serial1->errorString();
        }

        if (!serial1->setDataBits(QSerialPort::Data8))
        {
            qDebug() << serial1->errorString();
        }

        if (!serial1->setParity(QSerialPort::NoParity))
        {
            qDebug() << serial1->errorString();
        }


        serial1->setStopBits(QSerialPort::OneStop);
        serial1->setFlowControl(QSerialPort::NoFlowControl);

        QByteArray candata;

        candata.fill(0,11);

        candata[0] = 129;
        candata[2] = 129;
        candata[3] = 0;
        candata[4] = 1;

        qDebug() << candata << "candata out";

        serial1->write(candata);
        data.clear();

        int a = 0;
        while (data.length()<5)

        {
            if(serial1->waitForReadyRead(25))
            {
                if (serial1->bytesAvailable() > 0)
                {
                    data.append(serial1->readAll());
                }

                if (data.length() >= 5)
                {
                    qDebug() <<  data <<  "input data";

                    QString qstrdata = QString(data) +  "input data";
                    //                    ui->listWidget_Rx->addItem(qstrdata);
                }
                //               qDebug() <<  serial->readAll();
            }
            else
            {
                a++;
                if (a>=100)
                {
                    qDebug() << "Timeout";
                    //                    ui->listWidget_Rx->addItem("Timeout");
                    break;
                }
            }
        }
        serial1->close();
    }

    return data;
}


QByteArray QSerialCANBusLib::SendDataToCanBus(quint16 unit, quint16 command,  quint32 data,  quint16 datalenght, quint16 minresponselenght, quint64 timeoutmsec )
{
    if (timeoutmsec<25)
    {
        timeoutmsec = 25;
    }

    QSerialPort * serial1 = new QSerialPort();

  //  serial1->setPortName("COM4");
    serial1->setPortName("ttyAMA0");


    QByteArray candataout;
    QByteArray candatainput;

    serial1->open(QIODevice::ReadWrite);

    int b = 0;

    while (!serial1->isOpen())
    {

        exittimer = new QTimer();
        QEventLoop loop;

        exittimer->setInterval(timeoutmsec/10);
        exittimer->start();

        connect(exittimer, SIGNAL(timeout()), &loop, SLOT(quit()));
        loop.exec();

        if( serial1->open(QIODevice::ReadWrite) )
        {
            break;
        }
        else
        {
            b++;
            if(b==10)
            {
                candatainput.clear();
                //                    ui->listWidget_Rx->addItem("Timeout");
                candatainput.append(-2);
                return candatainput;
            }
        }
    }


    if (!serial1->setBaudRate(460800))
    {
    }

    if (!serial1->setDataBits(QSerialPort::Data8))
    {
    }

    if (!serial1->setParity(QSerialPort::NoParity))
    {
    }

    serial1->setStopBits(QSerialPort::OneStop);
    serial1->setFlowControl(QSerialPort::NoFlowControl);

    candataout.fill(0,11);

    candataout[0] = unit;
    candataout[1] = command;
    candataout[2] = datalenght;
    candataout[3] = data&0xff;
    candataout[4] = (data>>8)&0xff;
    candataout[5] = (data>>16)&0xff;
    candataout[6] = (data>>24)&0xff;

    serial1->write(candataout);
    candataout.clear();

    int a = 0;
    while (candatainput.length()<minresponselenght)

    {
        if(serial1->waitForReadyRead(timeoutmsec/10))
        {
            if (serial1->bytesAvailable() > 0)
            {
                candatainput.append(serial1->readAll());
            }

            if (candatainput.length() >= minresponselenght)
            {
                QString qstrdata = QString(candatainput) +  "input data";
            }
        }
        else
        {
            a++;
            if (a>=50)
            {
                candatainput.clear();
                break;
            }
        }
    }

    serial1->close();
    serial1->deleteLater();
    return candatainput;
}

QString QSerialCANBusLib::SendDataToCanBus(QString data, quint16 minresponselenght,  quint64 timeoutmsec )
{
    return QString("");
}