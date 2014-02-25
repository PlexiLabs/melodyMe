#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qmediaplayer.h"
#include <QMovie>
#include <QFileDialog>
#include <QVideoWidget>
#include <QVideoSurfaceFormat>
#include <QLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void play();

private slots:
    void on_actionOpen_File_triggered();
    void mediaStateChanged(QMediaPlayer::State state);
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void setPosition(int position);

private:
    Ui::MainWindow *ui;
    QMediaPlayer mediaPlayer;
};

#endif // MAINWINDOW_H
