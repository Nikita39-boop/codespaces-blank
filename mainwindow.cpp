#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openAndParseFile);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exitProgram);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveObjectsInFile);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::updateCurrentPage);
    connect(ui->updateButton, &QPushButton::clicked, this, &MainWindow::updateCurrentPage);
    connect(ui->updateNumButton, &QPushButton::clicked, this, &MainWindow::updateCurrentPage);
    connect(ui->addObjectButton, &QPushButton::clicked, this, &MainWindow::addObjectButtonClicked);

    groupView = new GroupView(ui->tabWidget, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openAndParseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Текстовые файлы (*.txt);;Все файлы (*.*)"));
    if (!filePath.isEmpty())
    {
        // Проверка расширения файла
        QFileInfo fileInfo(filePath);
        if (fileInfo.suffix() == "txt")
        {
            parseFile(filePath);
        }
        else
        {
            // Этот файл не является текстовым файлом
            QMessageBox::warning(this, tr("Ошибка"), tr("Выбранный файл не является текстовым файлом (.txt)"));
        }
    }
}

void MainWindow::parseFile(QString filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        this->objects.clear();
        // Загрузка значений из файла
        QTextStream in(&file);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (line.isEmpty())
            {
                continue;
            }

            QStringList parts = line.split(' ');

            if (parts.size() != 5)
            {
                qDebug() << "Invalid data: line does not have 5 fields";
                continue;
            }

            QString name = parts[0];
            bool ok = false;
            float coordinateX = parts[1].toFloat(&ok);

            if (!ok)
            {
                qDebug() << "Invalid data: cannot convert X coordinate to float";
                continue;
            }

            float coordinateY = parts[2].toFloat(&ok);

            if (!ok)
            {
                qDebug() << "Invalid data: cannot convert Y coordinate to float";
                continue;
            }

            QString type = parts[3];
            QString dateString = parts[4];

            // Преобразование даты из строки в QDateTime
            QDateTime createDate = QDateTime::fromString(dateString, "dd.MM.yyyy");

            if (!createDate.isValid())
            {
                qDebug() << "Invalid data: invalid date format";
                continue;
            }

            // Создание объекта Object и добавление в вектор
            Object object(name.toStdString(), coordinateX, coordinateY, type.toStdString(), createDate);
            this->objects.push_back(object);
        }

        file.close();

        if (groupView)
        {
            groupView->updateViewWithObjects(objects);
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл"));
    }
}

void MainWindow::updateCurrentPage(int index)
{
    if (groupView)
    {
        groupView->updateViewWithObjects(objects);
    }
}


void MainWindow::addObjectButtonClicked()
{

    QString name = ui->nameLineEdit->text();
    QString coordinateX = ui->coordinateXLineEdit->text();
    QString coordinateY = ui->coordinateYLineEdit->text();
    QString type = ui->typeLineEdit->text();
    QDateTime createDate = QDateTime::currentDateTime();

    // Проверка на пустые строки
    if (name.isEmpty() || coordinateX.isEmpty() || coordinateY.isEmpty() || type.isEmpty())
    {
        QMessageBox::warning(this, "Предупреждение", "Все поля должны быть заполнены.");
        return;
    }

    // Проверка на корректность данных
    bool okX, okY;
    float x = coordinateX.toFloat(&okX);
    float y = coordinateY.toFloat(&okY);
    if (!okX || !okY)
    {
        QMessageBox::warning(this, "Предупреждение", "Координаты должны быть числами.");
        return;
    }

    Object object(name.toStdString(), x, y, type.toStdString(), createDate);

    this->objects.push_back(object);

    if (groupView)
    {
        groupView->updateViewWithObjects(objects);
    }
}

void MainWindow::exitProgram()
{
    close();
}

void MainWindow::saveObjectsInFile()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), "", tr("Текстовые файлы (*.txt)"));
    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        for (const Object& object : this->objects)
        {
            QString name = QString::fromStdString(object.getName());
            QString coordinateX = QString::number(object.getCoordinateX());
            QString coordinateY = QString::number(object.getCoordinateY());
            QString type = QString::fromStdString(object.getType());
            QString createDate = object.getDate().toString("dd.MM.yyyy");

            out << name << " " << coordinateX << " " << coordinateY << " " << type << " " << createDate << "\n";
        }

        file.close();
    }
    else
    {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось сохранить файл"));
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Подтверждение выхода",
        tr("Вы уверены, что хотите выйти?\nВсе несохраненные данные будут утеряны.\n"),
        QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if (resBtn != QMessageBox::Yes)
    {
        event->ignore();
    } else {
        event->accept();
    }
}

