#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <redact.h>
#include<sortbox.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void processTextFile(const QString& filename);

public slots:
    void SaveButton(QDate alpha, QString beta, QString gamma);
    void CancelButton();
    void SortNeed(int a, int d);

private slots:
    void on_addB_clicked();
    void RedactButton(QDate alpha, QString beta, QString gamma);

    void on_calendarWidget_selectionChanged();

    void addDynamicButton(QString date, QString name = "Пустое имя", QString des = "Пустое Описание");
    void ReadTextFile();
    void uncheck();
    void Sorting();

    void DButton_Pressed();

    void on_redactB_clicked();

    void on_delB_clicked();

    void on_sortB_clicked();

private:
    Ui::MainWindow *ui;
    Redact *redact;
    SortBox sortbox;
    QPushButton *checkB[50];
    int dateSort = 1;

signals:
    void selDate(QDate alpha);
    void rejChoose(int alpha);
};


#endif // MAINWINDOW_H
