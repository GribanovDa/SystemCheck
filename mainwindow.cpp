#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGroupBox>
#include <QFormLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , proc(new Processor())
    , timer(new QTimer(this))
    , disks(new HardDisk())
    , ram(new RAM())
{
    ui->setupUi(this);

    // Creating content window and main layout
    QWidget *contentWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);

    // Creating refresh nutton
    QPushButton *refreshButton = new QPushButton("Обновить страницу");                      //TODO refresh function
    refreshButton->setContentsMargins(10, 10, 0, 0);
    mainLayout->addWidget(refreshButton);


    // Information about processor
    QGroupBox *processorGroup = new QGroupBox("Информация о процессоре");
    processorGroup->setStyleSheet("QGroupBox {"
                                  "   font: bold 12pt 'Arial';"  // Font
                                  "   margin-top: 25px;"         // Indentation
                                  "}");
    QFormLayout *processorLayout = new QFormLayout();

    processorLayout->addRow("Модель:", new QLabel(proc->getName()));
    processorLayout->addRow("Ядра:", new QLabel(proc->getCores()));
    processorLayout->addRow("Потоки:", new QLabel(proc->getThreads()));
    processorLayout->addRow("Кэш:", new QLabel(proc->getCash()));

    QLabel *freqLabel = new QLabel(proc->getFreq());
    QLabel *tempLabel = new QLabel(proc->getTemperature());
    processorLayout->addRow("Частота:", freqLabel);
    processorLayout->addRow("Температура:", tempLabel);

    processorGroup->setLayout(processorLayout);
    mainLayout->addWidget(processorGroup);

    // Information about disks
    QGroupBox *disksGroup = new QGroupBox("Информация о дисках");
    disksGroup->setStyleSheet("QGroupBox {"
                                "   font: bold 12pt 'Arial';"  // Font
                                "   margin-top: 25px;"         // Indentation
                                "}");
    QVBoxLayout *disksLayout = new QVBoxLayout();

    const QVector<HardDisk::DiskInfo>& disksInfo = disks->getDisksInfo();
    for(int i = 0; i < disksInfo.size(); i++) {
        QGroupBox *diskGroup = new QGroupBox(QString("Диск %1").arg(i+1));
        QFormLayout *diskLayout = new QFormLayout();

        diskLayout->addRow("Модель:", new QLabel(disksInfo[i].name));
        diskLayout->addRow("Тип:", new QLabel(disksInfo[i].type));
        diskLayout->addRow("Объем:", new QLabel(QString::number(disksInfo[i].volumeGB) + " ГБ"));

        diskGroup->setLayout(diskLayout);
        disksLayout->addWidget(diskGroup);
    }

    disksGroup->setLayout(disksLayout);
    mainLayout->addWidget(disksGroup);

    // Information about RAM
    QGroupBox *RAMGroup = new QGroupBox("Оперативная память");
    RAMGroup->setStyleSheet("QGroupBox {"
                                  "   font: bold 12pt 'Arial';"  // Font
                                  "   margin-top: 25px;"         // Indentation
                                  "}");
    QFormLayout *RAMLayout = new QFormLayout();

    QLabel *MemFreeLabel = new QLabel(proc->getFreq());
    QLabel *SwapFreeLabel = new QLabel(proc->getTemperature());

    RAMLayout->addRow("Всего оперативной памяти:", new QLabel(ram->getMemTotal()));
    RAMLayout->addRow("Свободно:", MemFreeLabel);
    RAMLayout->addRow("Объем раздела swap:", new QLabel(ram->getSwapTotal()));
    RAMLayout->addRow("Свободно от объема swap:", SwapFreeLabel);

    RAMGroup->setLayout(RAMLayout);
    mainLayout->addWidget(RAMGroup);

    // Add a stretching element to push the content up
    mainLayout->addStretch();

    // Создаем QScrollArea и устанавливаем contentWidget в нее
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true); // Important for correct display

    // Create a QScrollArea and set the contentWidget to it
    setCentralWidget(scrollArea);

    // Setting up a timer for updating information
    connect(timer, &QTimer::timeout, [this, freqLabel, tempLabel, MemFreeLabel, SwapFreeLabel](){
        freqLabel->setText(proc->getFreq());
        tempLabel->setText(proc->getTemperature());
        MemFreeLabel->setText(ram->getMemFree());
        SwapFreeLabel->setText(ram->getSwapFree());
    });
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete proc;
    delete ui;
    delete timer;
    delete disks;
}

