#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_translateButton_clicked()
{
    translate();
}

void MainWindow::translate()
{
    QString currentEnding = "";
    std::vector<QString> strVec;

    //input file object
    QFile inputFile(inputFileName);

    //I try to open input file to read
    if(inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream inputStream(&inputFile);

        //I read the fist line(without an eof character) and I check a type of ending
        QString line = inputStream.readLine();
        line.append("\n");

        if(line.right(1) == "\r")
        {
            //CR+LF
            currentEnding = "\r\n";
        }
        else
        {
            //LF
            currentEnding = "\n";
        }

        strVec.push_back(line);

        //reading later lines
        while(true)
        {
            //i read line without eol character
            line = inputStream.readLine();

            //I check if I reach the end of file
            if(line.isNull())
            {
                break;
            }

            //i add eol character
            line.append("\n");

            strVec.push_back(line);
        }

        //i delete "\n" character from the last line
        if(strVec.size() > 0)
        {
            strVec[strVec.size()-1].chop(1);
        }
    }



    //I check with radioButton is checked
    QString newEnding = "";
    if(ui->crlfRadioButton->isChecked())
    {
        newEnding = "\r\n";
    }
    else
    {
        newEnding = "\n";
    }

    //translating (but without the last line)
    for(unsigned int i = 0; i < strVec.size() - 1; i++)
    {
        if(currentEnding.size() == 2)
        {
            strVec[i].chop(2);
            strVec[i].push_back(newEnding);
        }
        else if(currentEnding.size() == 1)
        {
            strVec[i].chop(1);
            strVec[i].push_back(newEnding);
        }
    }

    //translating the last line
    if(strVec[strVec.size()-1].right(1) == "\r")
    {
        strVec[strVec.size()-1].chop(1);
    }


    //output file object
    QFile outputFile(outputFileName);

    //I try to open input file to write
    if(outputFile.open(QIODevice::WriteOnly))
    {
        QTextStream outputStream(&outputFile);

        //writing
        for(std::vector<QString>::iterator it = strVec.begin(); it != strVec.end(); it++)
        {
            outputStream << *it;
        }
    }
}

void MainWindow::checkFileds()
{
	//check if both of fields are completed
    if(!ui->inputFileLineEdit->text().isEmpty() && !ui->outputFileLineEdit->text().isEmpty())
    {
        ui->translateButton->setEnabled(true);
    }
    else
    {
        ui->translateButton->setEnabled(false);
    }
}

void MainWindow::on_inputFileButton_clicked()
{
	inputFileName = QFileDialog::getOpenFileName(this, "Open file", NULL, "All files(*)");
	ui->inputFileLineEdit->setText(inputFileName);

	//check if all is ready for translating
	checkFileds();
}

void MainWindow::on_outputFileButton_clicked()
{
	outputFileName = QFileDialog::getOpenFileName(this, "Open file", NULL, "All files(*)");
	ui->outputFileLineEdit->setText(outputFileName);

	//check if all is ready for translating
	checkFileds();
}

void MainWindow::on_inputFileLineEdit_textEdited(const QString &arg1)
{
    //update output file name
    inputFileName = arg1;

	//check if "translate" button can be activated
    checkFileds();
}

void MainWindow::on_outputFileLineEdit_textChanged(const QString &arg1)
{
	//update output file name
    outputFileName = arg1;

	//check if "translate" button can be activated
    checkFileds();
}
