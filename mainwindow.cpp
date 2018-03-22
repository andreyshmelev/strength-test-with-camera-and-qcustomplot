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

    ShowMessageBox(QString("Найдено %1 камеры").arg(camerainfos.length()));

    if (camerainfos.length()==0)
    {
//        qApp->closeAllWindows();
//        qApp->exit();
    }

    else

    {

        mCamera = new QCamera(camerainfos.at(0), this);
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

            mCamera2 = new QCamera(camerainfos.at(1), this);
            mCameraViewfinder2 = new QCameraViewfinder(this);
            mCameraImageCapture2 = new QCameraImageCapture(mCamera2,this);
            mCamera2->setViewfinder(mCameraViewfinder2);
            mLayout2->addWidget(mCameraViewfinder2);
            ui->scrollArea_2->setLayout(mLayout2);

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




//    setupDemo(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDemo(int demoIndex)
{
    setupRealtimeDataDemo(ui->customPlot);
    ui->customPlot->replot();
    setupRealtimeDataDemo2(ui->customPlot_2);
    ui->customPlot_2->replot();
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
    dataTimer.start(0); // Interval 0 means to refresh as fast as possible

    qDebug() << "seeeeetuuuuuuuup";
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
    customPlot->graph(0)->setBrush(QBrush(QColor(103,158,210)));

    //  103,158,210
    //  192,231,230
    customPlot->graph(0)->setAntialiasedFill(false);
    customPlot->addGraph(); // red line
    customPlot->graph(1)->setPen(QPen(QColor(192,231,230)));


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
    connect(&dataTimer2, SIGNAL(timeout()), this, SLOT(realtimeDataSlot_2()));
    dataTimer2.start(0); // Interval 0 means to refresh as fast as possible

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
    // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    double key = 0;
#else
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
    static double lastPointKey = 0;


//    QByteArray data = sibekiCan->SendDataToCanBus(ui->unit->value(), ui->command->value(),ui->data->value(),ui->DataLenght->value(), 11, 0);

//    if (data.isEmpty())
//    {
////        ui->listWidget_Rx->addItem("Response timeout");
////        ui->listWidget_Rx->scrollToBottom();
//        return;
//    }

//    if (data.at(0) == -2)
//    {
////        ui->listWidget_Rx->addItem("Serial Port Open Timeout");
////        ui->listWidget_Rx->scrollToBottom();
//        return;
//    }
//    int data0 = data.at(3);
//    int data1 = data.at(4);
//    int data2 = data.at(5);
//    int data3 = data.at(6);

//    int result = (data3<<24) + (data2<<16) + (data1<<8) + data0;



    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
        double value0 = qSin(key); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
        double value1 = qCos(key); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
        // add data to lines:
        ui->customPlot->graph(0)->addData(key, value0);
        ui->customPlot->graph(1)->addData(key, value1);
        // set data of dots:
        ui->customPlot->graph(2)->clearData();
        ui->customPlot->graph(2)->addData(key, value0);
        ui->customPlot->graph(3)->clearData();
        ui->customPlot->graph(3)->addData(key, value1);
        // remove data of lines that's outside visible range:
        ui->customPlot->graph(0)->removeDataBefore(key-8);
        ui->customPlot->graph(1)->removeDataBefore(key-8);
        // rescale value (vertical) axis to fit the current data:
        ui->customPlot->graph(0)->rescaleValueAxis();
        ui->customPlot->graph(1)->rescaleValueAxis(true);
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
                    QString("%1 FPS, Total Data points: %2")
                    .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                    .arg(ui->customPlot->graph(0)->data()->count()+ui->customPlot->graph(1)->data()->count())
                    , 0);
        lastFpsKey = key;
        frameCount = 0;
    }
}


void MainWindow::realtimeDataSlot_2()
{
    // calculate two new data points:
#if QT_VERSION < QT_VERSION_CHECK(4, 7, 0)
    double key = 0;
#else
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
#endif
    static double lastPointKey = 0;
    if (key-lastPointKey > 0.01) // at most add point every 10 ms
    {
        double value0 = qSin(key*4); //qSin(key*1.6+qCos(key*1.7)*2)*10 + qSin(key*1.2+0.56)*20 + 26;
        double value1 = qCos(key*4); //qSin(key*1.3+qCos(key*1.2)*1.2)*7 + qSin(key*0.9+0.26)*24 + 26;
        // add data to lines:
        ui->customPlot_2->graph(0)->addData(key, value0);
        ui->customPlot_2->graph(1)->addData(key, value1);
        // set data of dots:
        ui->customPlot_2->graph(2)->clearData();
        ui->customPlot_2->graph(2)->addData(key, value0);
        ui->customPlot_2->graph(3)->clearData();
        ui->customPlot_2->graph(3)->addData(key, value1);
        // remove data of lines that's outside visible range:
        ui->customPlot_2->graph(0)->removeDataBefore(key-8);
        ui->customPlot_2->graph(1)->removeDataBefore(key-8);
        // rescale value (vertical) axis to fit the current data:
        ui->customPlot_2->graph(0)->rescaleValueAxis();
        ui->customPlot_2->graph(1)->rescaleValueAxis(true);
        lastPointKey = key;
    }
    // make key axis range scroll with the data (at a constant range size of 8):
    ui->customPlot_2->xAxis->setRange(key+0.25, 8, Qt::AlignRight);
    ui->customPlot_2->replot();

    // calculate frames per second:
    static double lastFpsKey;
    static int frameCount;
    ++frameCount;
    if (key-lastFpsKey > 2) // average fps over 2 seconds
    {
        ui->statusBar->showMessage(
                    QString("%1 FPS, Total Data points: %2")
                    .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
                    .arg(ui->customPlot_2->graph(0)->data()->count()+ui->customPlot_2->graph(1)->data()->count())
                    , 0);
        lastFpsKey = key;
        frameCount = 0;
    }
}
