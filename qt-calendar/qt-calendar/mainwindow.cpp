#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTimerEvent>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    m_nTimerId = startTimer(1000);
    QString strDate = QTime::currentTime().toString("hh:mm:ss");
    ui->labelCurrentTime->setText(strDate);
}

MainWindow::~MainWindow()
{
    killTimer(m_nTimerId);
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *e)
{
    if (m_nTimerId == e->timerId()) {
        QString strDate = QTime::currentTime().toString("hh:mm:ss");
        ui->labelCurrentTime->setText(strDate);
    }
}

void MainWindow::on_btnCurrendDate_clicked()
{
    ui->widgetCalendar->setCurrentDate();
}
