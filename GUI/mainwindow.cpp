#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	addMenu();
    count_launches = 0;
    vertical_layout = new QVBoxLayout(ui->visualize_launches);
    vertical_layout->addLayout(addNumberOfLaunches());
    vertical_layout->addWidget(ui->launches);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QHBoxLayout* MainWindow::addNumberOfLaunches()
{
    QLabel* count_launches_label_ui = new QLabel();
    count_launches_label_ui->setText("Количество запусков: ");
    QSpinBox* count_launches_box_ui = new QSpinBox();
    //count_launches_box_ui->setMinimum(1);
    QPushButton* count_launches_button_ui = new QPushButton();
    count_launches_button_ui->setText("Запустить");

    connect(count_launches_box_ui, SIGNAL(valueChanged(int)), this, SLOT(setCountLaunches(int)));
    connect(count_launches_button_ui, SIGNAL(clicked()), this, SLOT(launchProgram()));

    QHBoxLayout* h_layout = new QHBoxLayout();
    h_layout->addWidget(count_launches_label_ui);
    h_layout->addWidget(count_launches_box_ui);
    h_layout->addWidget(count_launches_button_ui);
    return h_layout;
}

void MainWindow::setCountLaunches(int count)
{
    count_launches = count;
}

void MainWindow::addMenu()
{
	QMenuBar* menu_bar = menuBar();
	menu_bar->addAction("Указать путь", this, SLOT(createFileDialog()));
}

void MainWindow::createFileDialog()
{
	InputFiles* input_files = new InputFiles();
    connect(input_files, SIGNAL(pathToDir(QString)), this, SLOT(setPath(QString)));

    input_files->show();
    int click_ok = input_files->exec();

    if (click_ok != QDialog::Accepted)
        return;

    runParser();
    runGenerator();
    buidProjectWithLib();
}

void MainWindow::setPath(const QString path_from_dialog)
{
    path = path_from_dialog;
}

void MainWindow::launchProcess(QString name, QStringList arguments, QString working_dir)
{
    QProcess *process = new QProcess(this);
    process->setWorkingDirectory(working_dir);
    /*connect(process, &QProcess::readyReadStandardOutput, [=]() {
        QByteArray data = process->readAllStandardOutput();
        QString output(data); qDebug() << output;
    });*/
    process->start(name, arguments);
    if (!process->waitForStarted()) {
        qDebug("Could not start process");
        return;
    }
    if (!process->waitForFinished()) {
        qDebug("Could not finish process");
        return;
    }
}

void MainWindow::launchProgram()
{
    qDebug() << count_launches;
    QVBoxLayout* v_layuot_for_launches = new QVBoxLayout(ui->launches);

    for (int i = 1; i <= count_launches; ++i)
    {
        QTextEdit* output_text = new QTextEdit();

        QProcess *process = new QProcess(this);
        process->setWorkingDirectory("../project_build");
        connect(process, &QProcess::readyReadStandardOutput, [=]() {
            QByteArray data = process->readAllStandardOutput();
            QString output(data); output_text->setText(output);
            //qDebug() << output;
        });
        process->start("./project");
        if (!process->waitForStarted()) {
            qDebug("Could not start process");
            return;
        }
        if (!process->waitForFinished()) {
            qDebug("Could not finish process");
            return;
        }
        output_text->setReadOnly(true);
        v_layuot_for_launches->addWidget(output_text);
        output_text->show();
    }
}

void MainWindow::runParser()
{
    QStringList arguments;
    arguments << "../parser/main.py" << path;
    launchProcess("/bin/python3", arguments, ".");
}

void MainWindow::runGenerator()
{
    QStringList arguments;
    arguments << "../generator/main.py" << path;
    launchProcess("/bin/python3", arguments, ".");
}

void MainWindow::buidProjectWithLib()
{
    QStringList argument_for_cmake;
    argument_for_cmake << ".";
    qDebug() << path + "/cmake",
    launchProcess("cmake", argument_for_cmake, path);
    launchProcess("cmake", argument_for_cmake, "..");
    launchProcess("make", QStringList(), "..");
}
