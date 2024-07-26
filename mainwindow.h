#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "Object.h"
#include "Groupview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openAndParseFile();
    void parseFile(QString filePath);

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void updateCurrentPage(int index);
    void addObjectButtonClicked();
    void exitProgram();
    void saveObjectsInFile();

private:
    Ui::MainWindow *ui;
    GroupView *groupView;
    std::vector<Object> objects;
};
#endif // MAINWINDOW_H
