#ifndef INPUTFILES_H
#define INPUTFILES_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextCodec>
#include <QFileInfo>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QProcess>

#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class InputFiles; }
QT_END_NAMESPACE


class InputFiles : public QDialog
{
    Q_OBJECT
public:
    InputFiles(QDialog *parent = 0);
    ~InputFiles();

signals:
	void pathToDir(QString path);

private slots:
    void choicePath();

private:
    QLabel* addLabelForChoicePath();
	QHBoxLayout* addLaoutForChoicePath();
	void setUtf8ForWindow();
	void createConnectionsForPath();

	QLineEdit* path_to_dir_ui;
	QPushButton* path_to_dir_button_ui;

    Ui::InputFiles *ui;
};

#endif // INPUTFILES_H
