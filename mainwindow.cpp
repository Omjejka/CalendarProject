#include "mainwindow.h"
#include "ui_mainwindow.h"

QPushButton *checkB[50];
int cnt = 0;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->eventLay->setSpacing(5); //Установка пространства
}


QString info(QDate a){
    QString name = a.toString("dd.MM") + " | " + "Пусто";
    return name;
};


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addB_clicked()
{
    checkB[cnt] = new QPushButton;
    checkB[cnt]->setFixedHeight(25);
    checkB[cnt]->setDisabled(1);
    checkB[cnt]->setText(info(ui->calendarWidget->selectedDate()));
    checkB[cnt]->setStyleSheet("text-align: left");
    ui->eventLay->setSpacing(5);
    ui->eventLay->setAlignment(Qt::AlignTop);
    ui->eventLay->addWidget(checkB[cnt]);
    cnt++;
}


void MainWindow::on_calendarWidget_selectionChanged()
{
    for(int i=0;i<cnt;i++){  // Цикл для очистки массивов. Продолжается до элемента cnt, чтобы не выйти за пределы массивов
        if (checkB[i] != NULL){ // Проверка элемента, соответственно, и всей строки на существование
            delete checkB[i]; // Освобождение памяти элемента

        }
    }
    cnt = 0;
}

