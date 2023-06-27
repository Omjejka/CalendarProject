#ifndef REDACT_H
#define REDACT_H

#include <QDialog>
#include <QDate>


namespace Ui {
class Redact;
}

class Redact : public QDialog
{
    Q_OBJECT

public:
    explicit Redact(QWidget *parent = nullptr);
    ~Redact();

public slots:
    void getDate(QDate alpha);

private:
    Ui::Redact *ui;

private slots:
    void on_canB_clicked();

    void on_saveB_clicked();

signals:
    void signalForm(QDate a, QString b, QString c);

};

#endif // REDACT_H
