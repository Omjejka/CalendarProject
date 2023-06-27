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



   // connect(redact, &Redact::signalForm, this, &MainWindow::SaveButton);





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
                    loadButton(tmp,QString::fromStdString(str), countstr);
                    chk = 0;
                    }
                countstr++;
            }
        }
    }
}

void MainWindow::loadButton(QDate alpha, QString beta, int i)
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

    using namespace std;{
        int c = 0;
        string str;
        fstream file("DataBase.txt", ios::in);
        if(file.is_open()){
            while(getline(file, str, ';')){
                if (c == i-2){
                    ui->plainTextEdit->setPlainText(QString::fromStdString(str));

                }
                c++;
            }
        }
    }



    cnt++;


}

void MainWindow::SaveButton(QDate alpha, QString beta, QString gamma)
{
    using namespace std;
    ofstream file("DataBase.txt", ios::app);
    QString str = alpha.toString("dd/MM/yyyy") + ';' + beta + ';' + gamma + ';';
    if(file.is_open()){
        file << str.toStdString();
    }

    int j;
    for(int i = 0; i < cnt; i++){
        if(checkB[i] != NULL){
            if(checkB[i]->isChecked()){
                j = i;
            }
        }
    }


    for(int i=0;i<cnt;i++){
        if (checkB[i] != NULL){
            if(checkB[i]->isChecked()){
                QString tmp = checkB[i]->text().replace(" | ", ";") + ';' + ui->plainTextEdit->toPlainText() + ';';
                QString tmp2;
                using namespace std;{
                    string str;
                    fstream file("DataBase.txt", ios::in);
                    if(file.is_open()){
                        while(getline(file, str, char(1))){
                            tmp2 = QString::fromStdString(str).remove(tmp);
                        }
                        file.close();
                    }
                    fstream file1("DataBase.txt", ios::out);
                    if(file1.is_open()){
                        file1 << tmp2.toStdString();
                    }
                }
            }
        }
    }



    checkB[j]->setText(alpha.toString("dd/MM/yyyy") + " | " + beta);
    ui->plainTextEdit->setPlainText(gamma);




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
    connect(this, &MainWindow::selDate, redact, &Redact::getDate);
    emit selDate(ui->calendarWidget->selectedDate());
    connect(redact, &Redact::signalForm, this, &MainWindow::SaveButton);
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
        int count = (3 * mas) + 1;
        int c = 0;
        QString tmp = dymB->text();
        tmp.remove(0,13);
        string str;
        fstream file("DataBase.txt", ios::in);
        if(file.is_open()){
            while(getline(file, str, ';')){
                if((count % 3)){
                    if (QString::fromStdString(str) == tmp){
                        c = 1;
                    }
                }else if(c){
                    ui->plainTextEdit->setPlainText(QString::fromStdString(str));
                    c=0;
                }
                count++;

            }
        }
    }

}

void MainWindow::on_calendarWidget_selectionChanged()
{
    ui->plainTextEdit->clear();
    for(int i=0;i<cnt;i++){  // Цикл для очистки массивов. Продолжается до элемента cnt, чтобы не выйти за пределы массивов
        if (checkB[i] != NULL){ // Проверка элемента, соответственно, и всей строки на существование
            delete checkB[i]; // Освобождение памяти элемента
            checkB[i] = NULL;
        }
    }
    cnt = 0;

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
                    loadButton(tmp,QString::fromStdString(str), countstr);
                    chk = 0;
                }
                countstr++;
            }
        }
    }
}





void MainWindow::on_redactB_clicked()
{
    for(int i=0;i<cnt;i++){
        if (checkB[i] != NULL){
            if(checkB[i]->isChecked()){
                redact = new Redact;
                connect(this, &MainWindow::selDate, redact, &Redact::getDate);
                emit selDate(ui->calendarWidget->selectedDate());
                connect(redact, &Redact::signalForm, this, &MainWindow::SaveButton);
                redact->setModal(1);
                redact->show();
            }
        }
    }
}




void MainWindow::on_delB_clicked()
{
    for(int i=0;i<cnt;i++){
        if (checkB[i] != NULL){
            if(checkB[i]->isChecked()){
                QString tmp = checkB[i]->text().replace(" | ", ";") + ';' + ui->plainTextEdit->toPlainText() + ';';
                QString tmp2;
                using namespace std;{
                    string str;
                    fstream file("DataBase.txt", ios::in);
                    if(file.is_open()){
                        while(getline(file, str, char(1))){
                            tmp2 = QString::fromStdString(str).remove(tmp);
                        }
                        file.close();
                    }
                    fstream file1("DataBase.txt", ios::out);
                    if(file1.is_open()){
                        file1 << tmp2.toStdString();
                    }
                }
                delete checkB[i];
                checkB[i] = NULL;
            }
        }
    }
    ui->plainTextEdit->setPlainText("");
}

