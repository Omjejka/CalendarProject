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

void Redact::slot()
{

}

void Redact::on_canB_clicked()
{
    Redact::close();
}

