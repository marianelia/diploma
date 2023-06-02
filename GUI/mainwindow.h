#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSpinBox>
#include <QTextEdit>

#include "inputfiles.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void createFileDialog();
    void setPath(const QString path_from_dialog);

private slots:
    void launchProgram();
    void setCountLaunches(int count);

private:
    void runParser();
    void runGenerator();
    void buidProjectWithLib();

    void launchProcess(QString name, QStringList arguments, QString working_dir);


    //void runScripts();
	void addMenu();
    //QLabel* addNumberOfLaunchesLabel();
    QHBoxLayout* addNumberOfLaunches();

    QString path;
    QVBoxLayout* vertical_layout;
    int count_launches;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
