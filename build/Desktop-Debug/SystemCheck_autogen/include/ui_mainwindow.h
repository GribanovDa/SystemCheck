/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QLabel *label;
    QLabel *cash_fill;
    QLabel *freq_text;
    QLabel *cash_text;
    QLabel *model_text;
    QLabel *cores_fill;
    QLabel *freq_fill;
    QLabel *cores_text;
    QLabel *model_fill;
    QLabel *threads_fill;
    QLabel *threads_text;
    QLabel *temp_fill;
    QLabel *temp_text;
    QLabel *cores_text_2;
    QLabel *model_fill_2;
    QLabel *label_2;
    QLabel *threads_fill_2;
    QLabel *model_text_2;
    QLabel *cores_fill_2;
    QLabel *threads_text_2;
    QScrollBar *verticalScrollBar;
    QPushButton *pushButton;
    QWidget *tab;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        label = new QLabel(tab_2);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 101, 19));
        QFont font;
        font.setFamilies({QString::fromUtf8("Droid Sans")});
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label->setTextFormat(Qt::TextFormat::AutoText);
        label->setWordWrap(false);
        cash_fill = new QLabel(tab_2);
        cash_fill->setObjectName("cash_fill");
        cash_fill->setGeometry(QRect(130, 128, 71, 19));
        freq_text = new QLabel(tab_2);
        freq_text->setObjectName("freq_text");
        freq_text->setGeometry(QRect(13, 153, 63, 19));
        cash_text = new QLabel(tab_2);
        cash_text->setObjectName("cash_text");
        cash_text->setGeometry(QRect(13, 128, 35, 19));
        model_text = new QLabel(tab_2);
        model_text->setObjectName("model_text");
        model_text->setGeometry(QRect(13, 53, 62, 19));
        cores_fill = new QLabel(tab_2);
        cores_fill->setObjectName("cores_fill");
        cores_fill->setGeometry(QRect(130, 78, 41, 19));
        freq_fill = new QLabel(tab_2);
        freq_fill->setObjectName("freq_fill");
        freq_fill->setGeometry(QRect(130, 153, 101, 19));
        cores_text = new QLabel(tab_2);
        cores_text->setObjectName("cores_text");
        cores_text->setGeometry(QRect(13, 78, 41, 19));
        model_fill = new QLabel(tab_2);
        model_fill->setObjectName("model_fill");
        model_fill->setGeometry(QRect(130, 53, 400, 19));
        threads_fill = new QLabel(tab_2);
        threads_fill->setObjectName("threads_fill");
        threads_fill->setGeometry(QRect(130, 103, 66, 19));
        threads_text = new QLabel(tab_2);
        threads_text->setObjectName("threads_text");
        threads_text->setGeometry(QRect(13, 103, 66, 19));
        temp_fill = new QLabel(tab_2);
        temp_fill->setObjectName("temp_fill");
        temp_fill->setGeometry(QRect(130, 178, 141, 19));
        temp_text = new QLabel(tab_2);
        temp_text->setObjectName("temp_text");
        temp_text->setGeometry(QRect(13, 178, 102, 19));
        cores_text_2 = new QLabel(tab_2);
        cores_text_2->setObjectName("cores_text_2");
        cores_text_2->setGeometry(QRect(15, 275, 41, 19));
        model_fill_2 = new QLabel(tab_2);
        model_fill_2->setObjectName("model_fill_2");
        model_fill_2->setGeometry(QRect(130, 250, 400, 19));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 225, 101, 19));
        label_2->setFont(font);
        label_2->setTextFormat(Qt::TextFormat::AutoText);
        label_2->setWordWrap(false);
        threads_fill_2 = new QLabel(tab_2);
        threads_fill_2->setObjectName("threads_fill_2");
        threads_fill_2->setGeometry(QRect(130, 300, 66, 19));
        model_text_2 = new QLabel(tab_2);
        model_text_2->setObjectName("model_text_2");
        model_text_2->setGeometry(QRect(15, 250, 62, 19));
        cores_fill_2 = new QLabel(tab_2);
        cores_fill_2->setObjectName("cores_fill_2");
        cores_fill_2->setGeometry(QRect(130, 275, 41, 19));
        threads_text_2 = new QLabel(tab_2);
        threads_text_2->setObjectName("threads_text_2");
        threads_text_2->setGeometry(QRect(15, 300, 66, 19));
        verticalScrollBar = new QScrollBar(tab_2);
        verticalScrollBar->setObjectName("verticalScrollBar");
        verticalScrollBar->setGeometry(QRect(760, 200, 16, 241));
        verticalScrollBar->setOrientation(Qt::Orientation::Vertical);
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(360, 360, 96, 27));
        tabWidget->addTab(tab_2, QString());
        tab = new QWidget();
        tab->setObjectName("tab");
        tabWidget->addTab(tab, QString());

        horizontalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\321\206\320\265\321\201\321\201\320\276\321\200", nullptr));
        cash_fill->setText(QCoreApplication::translate("MainWindow", "\320\232\321\215\321\210:", nullptr));
        freq_text->setText(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260:", nullptr));
        cash_text->setText(QCoreApplication::translate("MainWindow", "\320\232\321\215\321\210:", nullptr));
        model_text->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\264\320\265\320\273\321\214:", nullptr));
        cores_fill->setText(QCoreApplication::translate("MainWindow", "\320\257\320\264\320\265\321\200:", nullptr));
        freq_fill->setText(QCoreApplication::translate("MainWindow", "\320\247\320\260\321\201\321\202\320\276\321\202\320\260:", nullptr));
        cores_text->setText(QCoreApplication::translate("MainWindow", "\320\257\320\264\320\265\321\200:", nullptr));
        model_fill->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\264\320\265\320\273\321\214:", nullptr));
        threads_fill->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\202\320\276\320\272\320\276\320\262:", nullptr));
        threads_text->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\202\320\276\320\272\320\276\320\262:", nullptr));
        temp_fill->setText(QCoreApplication::translate("MainWindow", "\320\242\320\225\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\320\260:", nullptr));
        temp_text->setText(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\320\260:", nullptr));
        cores_text_2->setText(QCoreApplication::translate("MainWindow", "\320\257\320\264\320\265\321\200:", nullptr));
        model_fill_2->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\264\320\265\320\273\321\214:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\272\320\276\320\277\320\270\321\202\320\265\320\273\320\270", nullptr));
        threads_fill_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\202\320\276\320\272\320\276\320\262:", nullptr));
        model_text_2->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\264\320\265\320\273\321\214:", nullptr));
        cores_fill_2->setText(QCoreApplication::translate("MainWindow", "\320\257\320\264\320\265\321\200:", nullptr));
        threads_text_2->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\202\320\276\320\272\320\276\320\262:", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "\320\232\320\276\320\274\320\277\320\273\320\265\320\272\321\202\321\203\321\216\321\211\320\270\320\265", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "\320\241\320\270\321\201\321\202\320\265\320\274\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
