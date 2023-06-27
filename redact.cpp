#include "redact.h"
#include "ui_redact.h"

Redact::Redact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Redact)
{
    ui->setupUi(this);
}

Redact::~Redact()
{
    delete ui;
}

void Redact::getDate(QDate alpha)
{
    ui->dateEd->setDate(alpha);
}


void Redact::on_canB_clicked()
{
    Redact::close();
}




void Redact::on_saveB_clicked()
{
    QDate a = ui->dateEd->date();
    QString b = ui->nameEd->text();
    QString c = ui->desEd->toPlainText();
    emit signalForm(a,b,c);
    Redact::close();
}

