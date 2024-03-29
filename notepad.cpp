#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    this->currentFile.clear();
    ui->textEdit->setText(QString());
}

void Notepad::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,  "Warning!!", "Cannot open file: " + file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText((text));
    file.close();
}

void Notepad::on_actionSave_as_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(filename);
    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = filename;
    setWindowTitle(filename);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer name in your network");
    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected) {
        QMessageBox::warning(this, "Warning", "Cannot access printer");
        return;
    }
    ui->textEdit->print(&printer);
}

void Notepad::on_actionExit_triggered()
{
    QApplication::quit();
}

void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}
