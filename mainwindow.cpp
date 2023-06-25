#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fstream"
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
    checkB[cnt]->setText(info(ui->calendarWidget->selectedDate()));
    checkB[cnt]->setStyleSheet("text-align: left");
    checkB[cnt]->setCheckable(1);
    ui->eventLay->setSpacing(5);
    ui->eventLay->setAlignment(Qt::AlignTop);
    ui->eventLay->addWidget(checkB[cnt]);





    connect(checkB[cnt], SIGNAL(clicked()), this, SLOT(DButton_Pressed()));

    cnt++;
}


void MainWindow::DButton_Pressed(){
    for(int i=0;i<cnt;i++){
        if (checkB[i] != NULL){
            checkB[i]->setChecked(0); //
        }
    }
    QPushButton* dymB = qobject_cast<QPushButton*>(sender());
    dymB->setChecked(1);
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


void MainWindow::on_saveB_clicked()
{
    /*)  using namespace std;
    ofstream file("Save.txt", ios::out); //Создание или открытие файла
    ofstream file1("SaveNotes.txt", ios::out);
    QString str;
    if(file.is_open()){ //Проверка на открытость файла
        for(int i=0;i<cnt;i++){
            if (checkB[i] != NULL){  //Проверка на существование
                a = checkB[i]->isChecked(); // Запись булевой переменной на состояние CheckB
                file << a << ";"; //запись в файл
                file.flush(); //Нужно
                file1.flush();
            }
        }
    } */
}


void MainWindow::on_redactB_clicked()
{
    QPushButton* dymB = qobject_cast<QPushButton*>(sender());
    redact.setModal(1);
    redact.show();


}

