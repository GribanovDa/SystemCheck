#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGroupBox>
#include <QFormLayout>
#include <QScrollArea>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , proc(new Processor())
    , timer(new QTimer(this))
    , disks(new HardDisk())
{
    ui->setupUi(this);

    // Создаем основной виджет и layout
    QWidget *contentWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);

    // Добавляем информацию о процессоре (как в предыдущем примере)
    QGroupBox *processorGroup = new QGroupBox("Информация о процессоре");
    processorGroup->setStyleSheet("QGroupBox {"
                                  "   font: bold 12pt 'Arial';"  // Комбинированное задание шрифта
                                  "   margin-top: 25px;"         // Отступ сверху
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

    // Добавляем информацию о дисках
    QGroupBox *disksGroup = new QGroupBox("Информация о дисках");
    disksGroup->setStyleSheet("QGroupBox {"
                                "   font: bold 12pt 'Arial';"  // Комбинированное задание шрифта
                                "   margin-top: 25px;"         // Отступ сверху
                                "}");
    QVBoxLayout *disksLayout = new QVBoxLayout();

    const QVector<HardDisk::DiskInfo>& disksInfo = disks->getDisksInfo();
    for(int i = 0; i < disksInfo.size(); i++) {
        QGroupBox *diskGroup = new QGroupBox(QString("Диск %1").arg(i+1));
        QFormLayout *diskLayout = new QFormLayout();

        diskLayout->addRow("Модель:", new QLabel(disksInfo[i].name));
        diskLayout->addRow("Тип:", new QLabel(disksInfo[i].type));
        diskLayout->addRow("Объем (ГБ):", new QLabel(QString::number(disksInfo[i].volumeGB)));

        diskGroup->setLayout(diskLayout);
        disksLayout->addWidget(diskGroup);
    }

    disksGroup->setLayout(disksLayout);
    mainLayout->addWidget(disksGroup);

    // Добавляем растягивающий элемент, чтобы прижать контент кверху
    mainLayout->addStretch();

    // Создаем QScrollArea и устанавливаем contentWidget в нее
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(contentWidget);
    scrollArea->setWidgetResizable(true); // Важно для корректного отображения

    // Устанавливаем scrollArea как центральный виджет
    setCentralWidget(scrollArea);

    // Настраиваем таймер для обновления информации
    connect(timer, &QTimer::timeout, [this, freqLabel, tempLabel](){
        freqLabel->setText(proc->getFreq());
        tempLabel->setText(proc->getTemperature());
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

