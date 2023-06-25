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

    void addingButton(QString beta="Пусто");
private slots:
    void on_addB_clicked();

    void on_calendarWidget_selectionChanged();

    void on_saveB_clicked();

    void DButton_Pressed();

    void on_redactB_clicked();

private:
    Ui::MainWindow *ui;
    Redact *redact;

signals:
    void signal();
};


#endif // MAINWINDOW_H
