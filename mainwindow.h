#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "/home/mushroom/Проекты/C++/SystemCheck/Include/processor.h"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Processor *proc;
    Ui::MainWindow *ui;
    QTimer *timer;
};
#endif // MAINWINDOW_H
