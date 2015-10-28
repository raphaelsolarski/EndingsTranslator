#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

enum EndingsType
{
    ENDINGS_TYPE_CRLF,
    ENDINGS_TYPE_LF,
    ENDINGS_TYPE_CR
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_inputFileButton_clicked();
    void on_outputFileButton_clicked();
    void on_translateButton_clicked();
    void on_inputFileLineEdit_textEdited(const QString &arg1);
    void on_outputFileLineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;     //pointer to ui
    QString inputFileName;
    QString outputFileName;
    void translate();		//method which translate file(inputFileName) to file with appropriate EoL's
    void checkFileds();		//method which check if app is ready for translation
};

#endif // MAINWINDOW_H
