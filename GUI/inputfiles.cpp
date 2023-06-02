#include "inputfiles.h"
#include "ui_inputfiles.h"

InputFiles::InputFiles(QDialog *parent) :
    QDialog(parent), ui(new Ui::InputFiles)
{
	//setUtf8ForWindow();
    ui->InputFiles::setupUi(this);
	QVBoxLayout* vertical_layout = new QVBoxLayout(ui->choice_path);
	vertical_layout->addWidget(addLabelForChoicePath());
	vertical_layout->addLayout(addLaoutForChoicePath());

	createConnectionsForPath();
}

InputFiles::~InputFiles()
{

}

void InputFiles::setUtf8ForWindow()
{
	QTextCodec* codec = QTextCodec::codecForName("UTF-8");
	QTextCodec::setCodecForLocale(codec);
}

void InputFiles::createConnectionsForPath()
{
	connect(this, SIGNAL(pathToDir(QString)), path_to_dir_ui, SLOT(setText(QString)));
}

QLabel* InputFiles::addLabelForChoicePath()
{
	QLabel *path_to_dir_label_ui = new QLabel;
	path_to_dir_label_ui->setText("Путь к библиотеке: ");
	return path_to_dir_label_ui;
}

QHBoxLayout* InputFiles::addLaoutForChoicePath()
{
	path_to_dir_ui = new QLineEdit();
	path_to_dir_ui->setEnabled(true);

	path_to_dir_button_ui = new QPushButton();
	path_to_dir_button_ui->setText("...");

	connect(path_to_dir_button_ui, SIGNAL(clicked()), this, SLOT(choicePath()));

	QHBoxLayout *horizontal_layout = new QHBoxLayout();
	horizontal_layout->addWidget(path_to_dir_ui);
	horizontal_layout->addWidget(path_to_dir_button_ui);
	return horizontal_layout;
}

void InputFiles::choicePath()
{
	QString path = QFileDialog::getExistingDirectory(
                                this, "Путь к директории файлов",
                                QDir::homePath(),
                                QFileDialog::ShowDirsOnly |
                                QFileDialog::DontResolveSymlinks);
	if (path == "")
		return;
	emit pathToDir(path);
}



