#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mediaPlayer(0, QMediaPlayer::VideoSurface)
{
    ui->setupUi(this);

    QVideoWidget *videoWidget = new QVideoWidget;

    //set button icons
    ui->playpauseBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->stopBtn->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    //disable play button on startup
    ui->playpauseBtn->setEnabled(false);

    //setup video tab layout
    QVBoxLayout *videoTabLayout = new QVBoxLayout;
    videoTabLayout->addWidget(videoWidget);

    //add video widget to video tab
    ui->videoTab->setLayout(videoTabLayout);

    //set slider initial range
    ui->postitionSlider->setRange(0,0);

    //add video output
    mediaPlayer.setVideoOutput(videoWidget);

    //connect slots
    connect(ui->playpauseBtn, SIGNAL(clicked()), this, SLOT(play()));
    connect(&mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this,
            SLOT(mediaStateChanged(QMediaPlayer::State)));

    connect(&mediaPlayer, SIGNAL(positionChanged(qint64)), this,
            SLOT(positionChanged(qint64)));

    connect(&mediaPlayer, SIGNAL(durationChanged(qint64)), this,
            SLOT(durationChanged(qint64)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::play()
{
    switch(mediaPlayer.state()) {

    case QMediaPlayer::PlayingState:
        mediaPlayer.pause();
        break;
    default:
        mediaPlayer.play();
        break;

    }
}

void MainWindow::mediaStateChanged(QMediaPlayer::State state)
{
    switch(state) {

    case QMediaPlayer::PlayingState:
        ui->playpauseBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        ui->playpauseBtn->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void MainWindow::positionChanged(qint64 position)
{
    ui->postitionSlider->setValue(position);
}

void MainWindow::durationChanged(qint64 duration)
{
    ui->postitionSlider->setRange(0, duration);
}

void MainWindow::setPosition(int position)
{
    mediaPlayer.setPosition(position);
}


void MainWindow::on_actionOpen_File_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath());

    if(!filename.isEmpty()) {
        mediaPlayer.setMedia(QUrl::fromLocalFile(filename));
        ui->playpauseBtn->setEnabled(true);
    }
}

