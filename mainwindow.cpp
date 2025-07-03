#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , proc(new Processor())
    , timer(new QTimer(this))
{

    ui->setupUi(this);
    ui->model_fill->setText(proc->getName());
    ui->cores_fill->setText(proc->getCores());
    ui->threads_fill->setText(proc->getThreads());
    ui->cash_fill->setText(proc->getCash());

    connect(timer, &QTimer::timeout, [this](){
        ui->freq_fill->setText(proc->getFreq());
        ui->temp_fill->setText(proc->getTemperature());
    });
    timer->start(1000);

}

MainWindow::~MainWindow()
{
    delete proc;
    delete ui;
    delete timer;
}
