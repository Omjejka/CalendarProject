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
    void changeRejB(int alpha);

private:
    Ui::Redact *ui;
    int rejB;

private slots:
    void on_canB_clicked();

    void on_saveB_clicked();

    void on_Redact_rejected();

signals:
    void signalForm(QDate a, QString b, QString c);
    void cancel();

};

#endif // REDACT_H
