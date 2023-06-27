#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <redact.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadButton(QDate alpha, QString beta, int i);

public slots:
    void SaveButton(QDate alpha, QString beta, QString gamma);

private slots:
    void on_addB_clicked();

    void on_calendarWidget_selectionChanged();

    void DButton_Pressed();

    void on_redactB_clicked();

private:
    Ui::MainWindow *ui;
    Redact *redact;

signals:
    void selDate(QDate alpha);
};


#endif // MAINWINDOW_H
