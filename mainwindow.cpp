#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fstream"
#include <QStyle>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QStringList>
#include <algorithm>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QApplication::setStyle("WindowsXP");
    ui->setupUi(this);
    ui->eventLay->setSpacing(5); //Установка пространства
    setFixedWidth(750);
    for (int i = 0; i < 50; ++i)
    {
        checkB[i] = nullptr;
    }
    connect(&sortbox, &SortBox::sendinfo, this,&MainWindow::SortNeed);
    ReadTextFile();
}


void MainWindow::SaveButton(QDate date, QString name, QString des) // Сохранение кнопки в Базе данных
{
    QFile file("DataBase.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << date.toString("dd/MM/yyyy") << ";" << name << ";" << des.replace("\n", "#@#") << "\n";
            file.close();
        }
        for(int i = 0; i<50; ++i){
            if (checkB[i] != nullptr && checkB[i]->isChecked()) {
                QString buttonText = date.toString("dd/MM/yyyy") + " | " + name;
                checkB[i]->setText(buttonText);
                ui->plainTextEdit->setPlainText(des.replace("#@#","\n"));
            }
        }
}

void MainWindow::CancelButton()
{
        for (int i = 0; i < 50; i++)
        {
            QPushButton* button = checkB[i];
            if (button && button->isChecked()){
                delete checkB[i];
                checkB[i] = nullptr;
                ui->plainTextEdit->clear();
            }
        }
}

void MainWindow::SortNeed(int a = 0, int d = 1)
{
        dateSort = d;
        MainWindow::on_calendarWidget_selectionChanged();
}

void MainWindow::RedactButton(QDate alpha, QString beta, QString gamma)
{
    for (int i = 0; i < 50; i++)
        {
            QPushButton* button = checkB[i];
            QString oldLine;
            if (button && button->isChecked()) // Ищем выбранную кнопку
            {
                QStringList parts1 = button->text().split(" | "); // Записываем из кнопки дату и имя
                QString datefB = parts1[0];
                QString namefB = parts1[1];
                QFile file("DataBase.txt");
                if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                    // Обработка ошибки открытия файла, если не удалось открыть
                    qDebug() << "Ошибка в редактБатон";
                }

                QTextStream in(&file);
                while (!in.atEnd()) { //Цикл, чтобы найти линию, которую надо удалить и заменить новой
                    QString line = in.readLine();
                    QStringList parts = line.split(";");
                    if (parts.size() >= 3 && parts[0] == datefB && parts[1] == namefB) {
                        oldLine = line;
                        break;
                    }
                }
                QString fileContent;
                QString newLine = alpha.toString("dd/MM/yyyy") + ';' + beta + ';' + gamma.replace("\n", "#@#");;
                in.seek(0);
                while (!in.atEnd()) { //Записываем в QString весь текстовый файл
                    QString line2 = in.readLine();

                    if (line2 == oldLine) {
                        // Заменяем строку на новую строку
                        fileContent += newLine + "\n";
                    } else {
                        fileContent += line2 + "\n";
                    }
                }

                checkB[i]->setText(alpha.toString("dd/MM/yyyy") + " | " + beta); // Переименовываем кнопку, выделяем, переписываем описание
                ui->plainTextEdit->setPlainText(gamma);
                uncheck();
                checkB[i]->setChecked(true);

                // Переписываем файл
                file.seek(0);
                file.write(fileContent.toUtf8());
                file.resize(file.pos());
                file.close();

            }
        }
}



MainWindow::~MainWindow() // Базовый деструктор
{
    delete ui;
}


void MainWindow::on_addB_clicked() // Нажатие на кнопку "Добавить"
{
    QString alpha = ui->calendarWidget->selectedDate().toString("dd/MM/yyyy");
    addDynamicButton(alpha);
    redact = new Redact;
    connect(this, &MainWindow::selDate, redact, &Redact::getDate); // Соединяем Сигнал selDate из mainwindow(this) со слотом getDate из redact
    connect(this, &MainWindow::rejChoose,redact, &Redact::changeRejB);
    connect(redact, &Redact::cancel,this,&MainWindow::CancelButton);
    emit rejChoose(1);
    emit selDate(ui->calendarWidget->selectedDate()); // Отправляем сигнал selDate(QDate alpha)
    connect(redact, &Redact::signalForm, this, &MainWindow::SaveButton); // Соединяем сигнал signalForm из redact со слотом SaveButton из mainwindow(this)
    redact->setModal(1);
    redact->show();

}


void MainWindow::DButton_Pressed() // Обработка нажатия на кнопку-событие
{
    uncheck();
    QPushButton* dymB = qobject_cast<QPushButton*>(sender());
    dymB->setChecked(1);
    if (dymB)
    {
        for (int i = 0; i < 50; ++i)
        {
            if (checkB[i] == dymB)
            {
                QFile file("DataBase.txt"); // Путь к вашему текстовому документу
                    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        qDebug() << "Не удалось открыть файл";
                        return;
                    }

                    int index = checkB[i]->text().indexOf(" | ");
                    QString name = checkB[i]->text().mid(index + 3);

                    QTextStream in(&file);
                    while (!in.atEnd())
                    {
                        QString line = in.readLine();
                        QStringList parts = line.split(';');
                        if (parts.size() == 3 && parts[1] == name)
                        {
                            QString description = parts[2];
                            ui->plainTextEdit->setPlainText(description.replace("#@#", "\n"));
                            break;
                        }
                    }

                    file.close();
                break;
            }
        }
    }
}

void MainWindow::on_calendarWidget_selectionChanged() // Смена набора кнопок при смене даты на календаре
{
    Sorting();
    ui->plainTextEdit->clear();
    for (int i = 0; i < 50; ++i)
     {
         if (checkB[i] != nullptr)
         {
             delete checkB[i];
             checkB[i] = nullptr;
         }
     }

    ReadTextFile();
}


void MainWindow::on_redactB_clicked()
{
    for(int i=0;i<50;i++){
        if (checkB[i] != nullptr && checkB[i]->isChecked()){
                redact = new Redact;
                connect(this, &MainWindow::selDate, redact, &Redact::getDate);
                connect(this, &MainWindow::rejChoose,redact, &Redact::changeRejB);
                connect(redact, &Redact::cancel,this,&MainWindow::CancelButton);
                emit selDate(ui->calendarWidget->selectedDate());
                emit rejChoose(0);
                connect(redact, &Redact::signalForm, this, &MainWindow::RedactButton);
                redact->setModal(1);
                redact->show();
        }
    }
}




void MainWindow::on_delB_clicked() // Удаление кнопки-события
{
    for(int i = 0; i<50; ++i){
        if (checkB[i] != nullptr && checkB[i]->isChecked()) {
                // Чтение данных из файла и удаление строки
                QFile file("DataBase.txt");
                if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
                    QTextStream in(&file);
                    QString line;
                    QStringList lines;
                    while (!in.atEnd()) {
                        line = in.readLine();
                        QStringList parts = line.split(";");
                        if (parts.size() >= 3) {
                            QString dateName = parts[0] + " | " + parts[1];
                            if (dateName != checkB[i]->text()) {
                                lines.append(line);
                            }
                        }
                    }
                    file.resize(0); // Очистка файла
                    for (const QString& l : lines) {
                        in << l << '\n'; // Запись оставшихся строк в файл
                    }
                    file.close();
                }

                delete checkB[i]; // Удаление кнопки checkB[i]
                checkB[i] = nullptr; // Обнуление указателя

                ui->plainTextEdit->clear(); // Очистка plaintextedit
        }
    }
}

void MainWindow::addDynamicButton(QString date, QString name, QString des) // Добавление кнопки-события
{
    for (int i = 0; i < 50; i++) {
        if (checkB[i] == nullptr) {
        checkB[i] = new QPushButton;
        checkB[i]->setFixedHeight(30);
        checkB[i]->setStyleSheet("text-align: left");
        checkB[i]->setText(date + " | " + name);
        checkB[i]->setCheckable(true);
        ui->eventLay->setSpacing(5);
        ui->eventLay->setAlignment(Qt::AlignTop);
        ui->eventLay->addWidget(checkB[i]);
        ui->plainTextEdit->setPlainText(des.replace("#@#", "\n"));

        connect(checkB[i], SIGNAL(clicked()), this, SLOT(DButton_Pressed()));

        uncheck();
        checkB[i]->setChecked(true);
        break; // Выходим из цикла, после создания первой доступной кнопки
        }
    }
}


void MainWindow::ReadTextFile() // Чтения файла и добавление кнопок на форму
{
    QFile file("DataBase.txt");

    // Проверяем, удалось ли открыть файл для чтения
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Ошибка открытия файла.";
        return;
    }

    redact = new Redact;


    QTextStream in(&file);
    while (!in.atEnd())
    {
        // Читаем строку из файла
        QString line = in.readLine();

        // Разделение строки на составляющие с помощью разделителя ";"
        QStringList parts = line.split(';');

        // Проверяем, что строка имеет правильный формат (три части)
        if (parts.size() != 3)
        {
            qDebug() << "Ошибка формата строки:" << line;
            continue;
        }

        // Получаем отдельные составляющие строки
        QString dateStr = parts[0];
        QString name = parts[1];
        QString description = parts[2];

        QDate sortDate = ui->calendarWidget->selectedDate();
        QDate weekDate = sortDate.addDays(7);
        QDate monthDate = sortDate.addMonths(1);
        QDate frmstr = QDate::fromString(dateStr, "dd/MM/yyyy");
//        qDebug() << (sortDate <= monthDate);
        qDebug() << (sortDate <= QDate::fromString(dateStr, "dd/MM/yyyy"));

                switch (dateSort) {
                case 0: //
                    addDynamicButton(dateStr, name, description);
                    break;
                case 1: // Сегодня
                    if(sortDate == frmstr){
                    addDynamicButton(dateStr, name, description);}
                    break;
                case 2: // Неделя
                    if(sortDate <= frmstr && frmstr <= weekDate){
                    addDynamicButton(dateStr, name, description);}
                    break;
                case 3: // Месяц
                    if(sortDate <= frmstr && frmstr <= monthDate){
                    addDynamicButton(dateStr, name, description);}
                    break;
                }

    }

    // Закрываем файл после окончания работы с ним
    file.close();
}

void MainWindow::uncheck() // Снятие выделения с кнопок
{
    for(int i=0;i<50;i++){
        if (checkB[i] != NULL){
            checkB[i]->setChecked(0); //
        }
    }
}

void MainWindow::Sorting()
{
    QFile file("DataBase.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Ошибка открытия файла.";
        return;
    }
    QStringList strList;
    QTextStream in(&file);
    while (!in.atEnd())
    {
        // Читаем строку из файла
        QString line = in.readLine();

        strList << line;
    }
    file.close();
    std::sort(strList.begin(), strList.end());
    QFile file1("DataBase.txt");
    file1.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate);
    foreach (const QString& str, strList) {
        QTextStream stream(&file);
        stream << str << "\n";
        file1.close();
    }

}

void MainWindow::on_sortB_clicked()
{
    sortbox.show();
}

