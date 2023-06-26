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



    using namespace std;{
        int countstr = 3;
        int chk = 0;
        string str;
        QDate tmp;
        fstream file("DataBase.txt", ios::in);
        if(file.is_open()){
            while(getline(file, str, ';')){
                if(!(countstr % 3)){
                    if (QDate::fromString(QString::fromStdString(str),"dd/MM/yyyy") == ui->calendarWidget->selectedDate()){
                        tmp = QDate::fromString(QString::fromStdString(str),"dd/MM/yyyy");
                        chk = 1;
                    }
                }else if(chk){
                    loadButton(tmp,QString::fromStdString(str));
                    chk = 0;
                    }
                countstr++;
            }
        }
    }
}

void MainWindow::loadButton(QDate alpha, QString beta)
{
    checkB[cnt] = new QPushButton;
    checkB[cnt]->setFixedHeight(30);
    checkB[cnt]->setStyleSheet("text-align: left");
    checkB[cnt]->setText(alpha.toString("dd/MM/yyyy") + " | " + beta);
    checkB[cnt]->setCheckable(1);
    ui->eventLay->setSpacing(5);
    ui->eventLay->setAlignment(Qt::AlignTop);
    ui->eventLay->addWidget(checkB[cnt]);

    connect(checkB[cnt], SIGNAL(clicked()), this, SLOT(DButton_Pressed()));
    for(int i=0;i<cnt;i++){
        if (checkB[i] != NULL){
            checkB[i]->setChecked(0); //
        }
    }
    checkB[cnt]->setChecked(1);
    cnt++;


}




MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addB_clicked()
{
    checkB[cnt] = new QPushButton;
    checkB[cnt]->setFixedHeight(30);
    QDate date = ui->calendarWidget->selectedDate();
    checkB[cnt]->setStyleSheet("text-align: left");
    checkB[cnt]->setText(date.toString("dd.MM") + " | " + "Пусто");
    checkB[cnt]->setCheckable(1);
    ui->eventLay->setSpacing(5);
    ui->eventLay->setAlignment(Qt::AlignTop);
    ui->eventLay->addWidget(checkB[cnt]);

    connect(checkB[cnt], SIGNAL(clicked()), this, SLOT(DButton_Pressed()));
    cnt++;

    for(int i=0;i<cnt;i++){
        if (checkB[i] != NULL){
            checkB[i]->setChecked(0); //
        }
    }
    checkB[cnt-1]->setChecked(1);


    redact = new Redact;
    redact->setModal(1);
    redact->show();
}


void MainWindow::DButton_Pressed(){
    for(int i=0;i<cnt;i++){
        if (checkB[i] != NULL){
            checkB[i]->setChecked(0); //
        }
    }
    QPushButton* dymB = qobject_cast<QPushButton*>(sender());
    dymB->setChecked(1);
    int mas = 0;
    while(dymB != *(checkB+mas)){ // Через цикл while ищем индекс кнопки
        mas++;
    }
    using namespace std;{
        int count = (3 * mas) + 2;
        string str;
        fstream file("DataBase.txt", ios::in);
        if(file.is_open()){
            while(getline(file, str, ';')){
                if (count == 0){
                    ui->plainTextEdit->setPlainText(QString::fromStdString(str));

                }
                count--;
            }
        }
    }

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
//    QPushButton* dymB = qobject_cast<QPushButton*>(sender());
    redact = new Redact;
    redact->setModal(1);
    redact->show();


}



