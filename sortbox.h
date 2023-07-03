#ifndef SORTBOX_H
#define SORTBOX_H

#include <QGroupBox>

namespace Ui {
class SortBox;
}

class SortBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit SortBox(QWidget *parent = nullptr);
    ~SortBox();

private slots:
    void on_okB_clicked();

private:
    Ui::SortBox *ui;
signals:
    void sendinfo(int a, int d);
};

#endif // SORTBOX_H
