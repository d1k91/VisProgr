#include "file_funct.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QTextDocument>

bool createFile(QString& filePath) {
    filePath = QFileDialog::getSaveFileName(nullptr, "Create New File", "", "Rich Text Format (*.rtf);;All Files (*)");
    if (filePath.isEmpty()) {
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Warning", "Cannot create file: " + file.errorString());
        return false;
    }

    file.close();
    return true;
}

bool openFile(QString& filePath, QString& content) {
    filePath = QFileDialog::getOpenFileName(nullptr, "Open File", "", "Rich Text Format (*.rtf);;All Files (*)");
    if (filePath.isEmpty()) {
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Warning", "Cannot open file: " + file.errorString());
        return false;
    }

    QTextDocument doc;
    doc.setPlainText(content);
    content = doc.toHtml();
    file.close();
    return true;
}


bool saveFile(const QString& filePath, const QString& content) {
    if (filePath.isEmpty()) {
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Warning", "Cannot save file: " + file.errorString());
        return false;
    }

    QTextDocument doc;
    doc.setHtml(content);

    QTextStream out(&file);
    out << doc.toHtml();
    file.close();
    return true;
}
