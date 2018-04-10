#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCameraImageCapture>
#include <QList>
#include <QDebug>
#include <QCameraInfo>
#include <QVBoxLayout>
#include <QLayoutItem>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(250, 250, 800, 400);

    mCameraViewfinder = new QCameraViewfinder(this);
    //    mCameraImageCapture = new QCameraImageCapture(this);
    mLayout = new QVBoxLayout(this);
    mLayout2 = new QVBoxLayout(this);

    qDebug() << "availableCameras" << QCameraInfo::availableCameras();

    QList<QCameraInfo> camerainfos = QCameraInfo::availableCameras();

    //    ShowMessageBox(QString("Найдено %1 камеры").arg(camerainfos.length()));

    if (camerainfos.length()==0)
    {
        //        qApp->closeAllWindows();
        //        qApp->exit();
    }

    else

    {

        if (camerainfos.length()==1)
            mCamera = new QCamera(camerainfos.at(0), this);

        else
            if (camerainfos.length()==2)
                mCamera = new QCamera(camerainfos.at(1), this);


        mCameraViewfinder = new QCameraViewfinder(this);
        mCameraImageCapture = new QCameraImageCapture(mCamera,this);
        mCamera->setViewfinder(mCameraViewfinder);
        mLayout->addWidget(mCameraViewfinder);
        ui->scrollArea->setLayout(mLayout);

        foreach (const QCameraInfo &cameraInfo, camerainfos) {
        }

        mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);

        QImageEncoderSettings encSettings;
        encSettings.setCodec("image/jpeg");
        encSettings.setResolution(1600,1200);

        mCameraImageCapture->setEncodingSettings(encSettings);

        mCamera->setCaptureMode(QCamera::CaptureVideo);
        mCamera->start();

        if (camerainfos.length()>1)
        {


            mCameraViewfinder2 = new QCameraViewfinder(this);

            mCamera2 = new QCamera(camerainfos.at(0), this);
            mCameraViewfinder2 = new QCameraViewfinder(this);
            mCameraImageCapture2 = new QCameraImageCapture(mCamera2,this);
            mCamera2->setViewfinder(mCameraViewfinder2);
            mLayout2->addWidget(mCameraViewfinder2);
            //            ui->scrollArea_2->setLayout(mLayout2);

            foreach (const QCameraInfo &cameraInfo, camerainfos) {
            }

            mCameraImageCapture2->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);

            QImageEncoderSettings encSettings2;
            encSettings2.setCodec("image/jpeg");
            encSettings2.setResolution(1600,1200);

            mCameraImageCapture2->setEncodingSettings(encSettings2);

            mCamera2->setCaptureMode(QCamera::CaptureVideo);
            mCamera2->start();


        }
    }

    sibekiCan = new QSerialCANBusLib("COM8",460800,QSerialPort::Data8,QSerialPort::NoParity,QSerialPort::OneStop,QSerialPort::NoFlowControl);
    setupDemo(0);

    isstarted = 0;

//    connect(&msec100Timer, SIGNAL(timeout()), this, SLOT(updatetimerbutton()));

//    //    msec100Timer.start(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDemo(int demoIndex)
{
    setupRealtimeDataDemo(ui->customPlot);
    ui->customPlot->replot();
}

void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{

#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
    //  demoName = "Real Time Data Demo";

    // include this section to fully disable antialiasing for higher performance:

    /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */

    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    customPlot->graph(0)->setAntialiasedFill(false);
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(Qt::red));
    customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

    customPlot->addGraph(); // blue dot
    customPlot->graph(2)->setPen(QPen(Qt::blue));
    customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    customPlot->addGraph(); // red dot
    customPlot->graph(3)->setPen(QPen(Qt::red));
    customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setTickStep(2);
    customPlot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    dataTimer.start(25); // Interval 0 means to refresh as fast as possible
}


void MainWindow::setupRealtimeDataDemo2(QCustomPlot *customPlot)
{
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    QMessageBox::critical(this, "", "You're using Qt < 4.7, the realtime data demo needs functions that are available with Qt 4.7 to work properly");
#endif
    //  demoName = "Real Time Data Demo";

    // include this section to fully disable antialiasing for higher performance:
    /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */
    customPlot->addGraph(); // blue line
    customPlot->graph(0)->setPen(QPen(Qt::blue));
    customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));

    //  103,158,210
    //  192,231,230
    customPlot->graph(0)->setAntialiasedFill(false);
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(Qt::red));



    customPlot->addGraph(); // blue line
    //  customPlot->graph(0)->setPen(QPen(Qt::blue));
    //  customPlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    //  customPlot->graph(0)->setAntialiasedFill(false);
    //  customPlot->addGraph(); // red line
    //  customPlot->graph(1)->setPen(QPen(Qt::red));
    //  customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));


    customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));

    customPlot->addGraph(); // blue dot
    customPlot->graph(2)->setPen(QPen(Qt::blue));
    customPlot->graph(2)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(2)->setScatterStyle(QCPScatterStyle::ssDisc);
    customPlot->addGraph(); // red dot
    customPlot->graph(3)->setPen(QPen(Qt::red));
    customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);

    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");
    customPlot->xAxis->setAutoTickStep(false);
    customPlot->xAxis->setTickStep(2);
    customPlot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
    dataTimer2.start(5000); // Interval 0 means to refresh as fast as possible

}

void MainWindow::ShowMessageBox(QString message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setInformativeText(message);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setStyleSheet("QMessageBox{background-color: rgb(103,158,210);color: white;}QPushButton \
    {\
                             background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E25303, stop: 0.1 #E25303, stop: 0.49 #E25303, stop: 0.5 #E25303, stop: 1 #E25306);\
                             border-style: outset;\
                             border-width: 2px;\
                             border-radius: 10px;\
                             border-color: beige;\
                             font: bold 14px; color: white;\
                             padding: 6px;\
                         }\
                         ");
                         int ret = msgBox.exec();
}


void MainWindow::realtimeDataSlot()
{

    double result;

    // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    double key = 0;
#else
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/10000.0;
#endif
    static double lastPointKey = 0;


    QByteArray data;


    data = sibekiCan->SendDataToCanBus(0, 0 , 0 , 0, 6, 150);


//    qDebug() << data << " graph data";

    if (data.isEmpty())
    {
        ui->message->setText("Response timeout");
//        result= (double) -1;
    }


    if ( ( data.at(0) == 1) && (data.at(1) == 7)  )
    {

        {
            ui->message->clear();

            quint8 data0 = (quint8) data.at(2);
            quint8 data1 = (quint8) data.at(3);
            quint8 data2 = (quint8) data.at(4);
            quint8 data3 = (quint8) data.at(5);
            result =  (data3<<24) + (data2<<16) + (data1<<8) + data0;

            if (result<0)
                result = -1;

            ui->message->setText(QString("Result is: %1").arg(result));

            if (result>=0)
            {
                XData.append(key);
                YData.append(result);
            }


//            qDebug () << "data is  " << data[2]<< data[3]<< data[4]<< data[5] ;
//            qDebug () << "result is  " << result;
        }
    }



    //    result= (double) 444;

    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
        //          double value0 = (double)result; //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
        //        double value0 = (key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
        //        double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
        // add data to lines:

        {


            if (isstarted) {


                QFile file( this->filename );
                if ( file.open(QIODevice::Append|QIODevice::Text) )
                {
                    QTextStream stream( &file );


//                    QString sss = QString("%1,%2\n").arg(QDateTime::currentDateTime().toString("hhmmss"),  QString::number(result));
                    QString sss = QString("%1\n").arg(QString::number(result));

                    stream << sss;
                }
                else
                {    qDebug() << "file closed";
                }
                file.close();
            }


        }


        ui->customPlot->graph(0)->setData(XData,YData);
        //                ui->customPlot->graph(0)->addData(key, result);
        // rescale value (vertical) axis to fit the current data:
        ui->customPlot->graph(0)->rescaleValueAxis();
        ui->customPlot->graph(0)->rescaleAxes(false);
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->customPlot->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        ui->statusBar->showMessage(
                    QString("%1 FPS, Total Data points: ")
                    .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                    .arg(ui->customPlot->graph(0)->data()->count())
                    , 0);
        lastFpsKey = key;
        frameCount = 0;
    }
}


void MainWindow::realtimeDataSlot_2()
{

    return;
}

void MainWindow::updatetimerbutton()
{

}

void MainWindow::on_pushButton_clicked()
{

}

bool MainWindow::getStart() const
{
    return start;
}

void MainWindow::setStart(bool value)
{
    start = value;
}

void MainWindow::on_cyl1forward_clicked()
{
    QByteArray data = sibekiCan->SendDataToCanBus(1, 2,2,0, 1, 150);

}

void MainWindow::on_cyl1backward_clicked()
{

    QByteArray data = sibekiCan->SendDataToCanBus(1, 1,1,0, 1, 150);
    qDebug() << data<<" data";

}
void MainWindow::startstop()
{
    if (isstarted == false)
    {


        myTimer.start();
        // do something..

//        this->filename =  QString("C:/Qt/LOG.txt").arg( QDateTime::currentDateTime().toString() );

        this->filename =  QString("C:/LOG%1.csv").arg( QDateTime::currentDateTime().toString("yyMMddhhmmss")) ;

       qDebug() << "try to Open a new file";
        QFile file( this->filename );
        if ( file.open(QIODevice::ReadWrite) )
        {
            qDebug() << "Opened new file";
        }
        file.close();
        isstarted = true;
        ui->startButton->setText("Стоп");



        QByteArray data = sibekiCan->SendDataToCanBus(1, 1,1,0, 6, 150);


    }
    else
    {

        ui->customPlot->graph(0)->clearData();


        ui->customPlot->graph(1)->clearData();


        ui->customPlot->graph(2)->clearData();


        isstarted = false;
        ui->startButton->setText("Старт");


        QByteArray data = sibekiCan->SendDataToCanBus(1, 1,0,0, 6, 150);

    }

    int nMilliseconds = myTimer.elapsed();
}

void MainWindow::on_startButton_clicked()
{
  startstop();
}

void MainWindow::on_horizontalScrollBar_sliderReleased()
{
    float a = (float)  (ui->horizontalScrollBar->value());
ui->voltvalue->setText(QString::number( a/100    ) + " V");
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    float a = (float)  (ui->horizontalScrollBar->value());
ui->voltvalue->setText(QString::number( a/100    ) + " V");
}

void MainWindow::on_setvoltagebutton_clicked()
{
    QByteArray data;

    quint32 a = (quint32)  (ui->horizontalScrollBar->value());
    data = sibekiCan->SendDataToCanBus(1, 4, a, 0, 6, 500);
    qDebug() << "voltage " << data ;
}

void MainWindow::on_stopbutton_3_clicked()
{

}

void MainWindow::on_cyl2back_clicked()
{
    QByteArray data = sibekiCan->SendDataToCanBus(1, 2, 3, 0, 6, 100);
}

void MainWindow::on_cyl2front_clicked()
{

    QByteArray  data = sibekiCan->SendDataToCanBus(1, 2, 1, 0, 6, 100);
}

void MainWindow::on_cyl1back_2_clicked()
{

    QByteArray data = sibekiCan->SendDataToCanBus(1, 2, 0, 0, 6, 100);
}

void MainWindow::on_cyl1back_clicked()
{

    QByteArray data = sibekiCan->SendDataToCanBus(1, 2, 2, 0, 6, 100);
}

void MainWindow::on_sendparamsbutton_clicked()
{
    QByteArray data ;

//    QTimer::singleShot(100, this);


    quint32 maxforse = (quint32)  (ui->MaxForseSpinBox->value());
    data = sibekiCan->SendDataToCanBus(1, 3, maxforse, 0, 6, 100);

qDebug() << data << "maxforse" ;

    quint32 worktime = (quint32)  (ui->worktimespinBox->value()*10);
    data = sibekiCan->SendDataToCanBus(1, 5, worktime, 0, 6, 100);


    qDebug() << data << "worktime" ;

    quint32 holdtime = (quint32)  (ui->holdtimespinBox->value()*10);
    data = sibekiCan->SendDataToCanBus(1, 6, holdtime, 0, 6, 100);



    qDebug() << data << "holdtime" ;
}
