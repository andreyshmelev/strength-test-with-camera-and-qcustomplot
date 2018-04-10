#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QLayoutItem>
#include "qcustomplot.h"
#include "qserialcanbuslib.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     QVector<double> XData;
     QVector<double> YData;

     const quint32 koef = 695000/285;

    void setupRealtimeDataDemo2(QCustomPlot *customPlot);
    bool getStart() const;
    void setStart(bool value);
    bool isstarted ;
    QString filename;

    void startstop();

public slots:
    void ShowMessageBox(QString message);

    void setupDemo(int demoIndex);
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    void realtimeDataSlot();
    void realtimeDataSlot_2();



    void updatetimerbutton();



private slots:
    void on_pushButton_clicked();

    void on_cyl1forward_clicked();

    void on_cyl1backward_clicked();

    void on_startButton_clicked();

    void on_horizontalScrollBar_sliderReleased();

    void on_horizontalScrollBar_valueChanged(int value);

    void on_setvoltagebutton_clicked();

    void on_stopbutton_3_clicked();

    void on_cyl2back_clicked();

    void on_cyl2front_clicked();

    void on_cyl1back_2_clicked();

    void on_cyl1back_clicked();

    void on_sendparamsbutton_clicked();

private:
    Ui::MainWindow *ui;



    QTime myTimer;

    QTime msec100Timer;


     QList<QCamera * > cameras;
    QCamera *mCamera;
    QCamera *mCamera2;
    QCameraViewfinder *mCameraViewfinder;
    QCameraViewfinder *mCameraViewfinder2;
    QCameraImageCapture *mCameraImageCapture;
    QCameraImageCapture *mCameraImageCapture2;
    QVBoxLayout *mLayout;
    QVBoxLayout *mLayout2;

    bool start;

    QTimer dataTimer;
    QTimer dataTimer2;

    QSerialCANBusLib * sibekiCan;
};

#endif // MAINWINDOW_H
