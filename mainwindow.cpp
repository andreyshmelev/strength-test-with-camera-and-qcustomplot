#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCameraImageCapture>
#include <QList>
#include <QDebug>
#include <QCameraInfo>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLayoutItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    mCamera = new QCamera(this);
    mCameraViewfinder = new QCameraViewfinder(this);
    mCameraViewfinder2 = new QCameraViewfinder(this);
    //    mCameraImageCapture = new QCameraImageCapture(this);
    mLayout = new QVBoxLayout(this);
    mLayout2 = new QVBoxLayout(this);

    qDebug() << "availableCameras" << QCameraInfo::availableCameras();

    QList<QCameraInfo> camerainfos = QCameraInfo::availableCameras();

    if (camerainfos.isEmpty())
    {
        ShowMessageBox("Камеры не найдены");
    }
    else
    {
        mCamera = new QCamera(camerainfos.at(0));
        mCamera2 = new QCamera(camerainfos.at(0));
        mCameraViewfinder = new QCameraViewfinder(this);
        mCameraViewfinder2 = new QCameraViewfinder(this);
        mCameraImageCapture = new QCameraImageCapture(mCamera,this);
        mCameraImageCapture2 = new QCameraImageCapture(mCamera2,this);
        mCamera->setViewfinder(mCameraViewfinder);
        mCamera2->setViewfinder(mCameraViewfinder2);

        mLayout->addWidget(mCameraViewfinder);
        mLayout2->addWidget(mCameraViewfinder2);
//        mLayout->setMargin(0);
        ui->scrollArea->setLayout(mLayout);

//        mLayout2 = mLayout;
        ui->scrollArea_2->setLayout(mLayout2);
    }

    foreach (const QCameraInfo &cameraInfo, camerainfos) {
        //        mCamera = new QCamera(cameraInfo);
        //        cameras.append(mCamera);
        //        ui->CameraList->addItem(cameraInfo.description() + cameraInfo.deviceName());
    }

    mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);
    mCameraImageCapture2->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);

    QImageEncoderSettings encSettings;
    encSettings.setCodec("image/jpeg");
    encSettings.setResolution(800,600);

    mCameraImageCapture->setEncodingSettings(encSettings);
    mCameraImageCapture2->setEncodingSettings(encSettings);

    mCamera->setCaptureMode(QCamera::CaptureVideo);
    mCamera->start();
//    mCamera2->setCaptureMode(QCamera::CaptureVideo);
//    mCamera2->start();
}

MainWindow::~MainWindow()
{
    delete ui;
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
