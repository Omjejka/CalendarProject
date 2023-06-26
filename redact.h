#ifndef REDACT_H
#define REDACT_H

#include <QDialog>

namespace Ui {
class Redact;
}

class Redact : public QDialog
{
    Q_OBJECT

public:
    explicit Redact(QWidget *parent = nullptr);
    ~Redact();

private:
    Ui::Redact *ui;

private slots:
    void on_canB_clicked();

    void on_saveB_clicked();

};

#endif // REDACT_H
