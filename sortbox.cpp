#include "sortbox.h"
#include "ui_sortbox.h"

SortBox::SortBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::SortBox)
{
    ui->setupUi(this);
}

SortBox::~SortBox()
{
    delete ui;
}

void SortBox::on_okB_clicked()
{
    int a = 0;
    int d = 1;
    if(ui->AZcheck->isChecked()){ a = 0;}
    if(ui->ZAcheck->isChecked()){ a = 1;}
    if(ui->allRB->isChecked()){ d = 0;}
    if(ui->todayRB->isChecked()){ d = 1;}
    if(ui->weekRB->isChecked()){ d = 2;}
    if(ui->monthRB->isChecked()){ d = 3;}
    emit sendinfo(a,d);
    this->hide();

}

