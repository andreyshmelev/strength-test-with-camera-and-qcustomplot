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

    void setupRealtimeDataDemo2(QCustomPlot *customPlot);
    bool getStart() const;
    void setStart(bool value);

public slots:
    void ShowMessageBox(QString message);

    void setupDemo(int demoIndex);
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    void realtimeDataSlot();
    void realtimeDataSlot_2();

private slots:
    void on_pushButton_clicked();

    void on_cyl1forward_clicked();

    void on_cyl1backward_clicked();

    void on_startButton_clicked();

    void on_stopbutton_clicked();

private:
    Ui::MainWindow *ui;
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
