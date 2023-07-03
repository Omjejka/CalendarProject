#include "redact.h"
#include "ui_redact.h"
#include <QStyle>
#include <fstream>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

Redact::Redact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Redact)
{
    ui->setupUi(this);

}
int check = 1;
Redact::~Redact()
{
    delete ui;
}

void Redact::getDate(QDate alpha)
{
    ui->dateEd->setDate(alpha);
}

void Redact::changeRejB(int alpha)
{
    rejB = alpha;
}


void Redact::on_canB_clicked()
{
    if(rejB){
        emit cancel();
        Redact::close();
    }else{Redact::close();}
}


void Redact::on_saveB_clicked()
{
    if(rejB){
        QFile file("DataBase.txt");
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                qDebug() << "Не удалось открыть файл. Redact::on_nameEd_textEdited()";
            }

            QTextStream in(&file);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                QStringList fields = line.split(';');
                if (fields.size() >= 2)
                {
                    QString name = fields[1].trimmed();
                    if (name == ui->nameEd->text())
                    {
                        // Имя найдено
                        file.close();
                        check = 0;
                        break;
                    }
                    else check = 1;
                }
            }
        if(check == 0){
            QMessageBox::critical(nullptr, "Ошибка", "Данное имя уже существует!");
        }else{
            rejB = 0;
            QDate a = ui->dateEd->date();
            QString b = ui->nameEd->text();
            QString c = ui->desEd->toPlainText();
            emit signalForm(a,b,c); // Отправляем сигнал signalForm(QDate a, QString b, QString c)
            Redact::close();
        }
    }else{
        QDate a = ui->dateEd->date();
        QString b = ui->nameEd->text();
        QString c = ui->desEd->toPlainText();
        emit signalForm(a,b,c); // Отправляем сигнал signalForm(QDate a, QString b, QString c)
        Redact::close();
    }
}

void Redact::on_Redact_rejected()
{
    if(rejB){
        emit cancel();
        Redact::close();
    }else{Redact::close();}
}

