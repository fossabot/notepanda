#include "texteditor.h"

#include <QPainter>
#include <QTextBlock>
#include <QMessageBox>
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QFileDialog>

//![constructor]

TextEditor::TextEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{

}

void TextEditor::newDocument()
{
    currentFile.clear();
    TextEditor::setPlainText(QString());
}

void TextEditor::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open the file"));
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot open file: ") + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    TextEditor::setPlainText(text);
    file.close();
}

void TextEditor::save()
{
    QString fileName;

    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, tr("Save"));
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot save file: ") + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = TextEditor::toPlainText();
    out << text;
    file.close();
}

void TextEditor::saveAs()
{
    QString flieName = QFileDialog::getSaveFileName(this, tr("Save as"));
    QFile file(flieName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"), tr("Cannot save file: ") + file.errorString());
               return;
    }

    currentFile = flieName;
    setWindowTitle(flieName);
    QTextStream out(&file);
    QString text = TextEditor::toPlainText();
    out << text;
    file.close();
}
