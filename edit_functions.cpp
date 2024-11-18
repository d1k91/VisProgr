#include "edit_functions.h"
#include <QClipboard>
#include <QApplication>
#include <QMessageBox>
#include <QTextCursor>
#include <QFile>
#include <QTextStream>
QString EditFunctions::tempFilePath = "temporary.txt";
void EditFunctions::findText(QTextEdit *textEdit, const QString &text) {
    if (text.isEmpty()) return;

    QString documentText = textEdit->toPlainText();
    int index = documentText.indexOf(text);
    if (index != -1) {
        textEdit->setFocus();
        QTextCursor cursor = textEdit->textCursor();
        cursor.setPosition(index);
        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, text.length());
        textEdit->setTextCursor(cursor);
        textEdit->ensureCursorVisible();
    } else {
        QMessageBox::information(textEdit, "Search", "Text not found.");
    }
}

void EditFunctions::replaceText(QTextEdit *textEdit, const QString &oldText, const QString &newText) {
    QString documentText = textEdit->toPlainText();
    documentText.replace(oldText, newText);
    textEdit->setPlainText(documentText);
}

void EditFunctions::clearText(QTextEdit *textEdit) {
    // Сохраняем текущее содержимое в временный файл
    QFile file(tempFilePath);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось сохранить текст во временный файл.");
    }

    // Очищаем текст
    textEdit->clear();
}

void EditFunctions::undoText(QTextEdit *textEdit) {
    textEdit->undo();
}

void EditFunctions::redoText(QTextEdit *textEdit) {
    textEdit->redo();
}

void EditFunctions::copyText(QTextEdit *textEdit) {
    textEdit->copy();
}

void EditFunctions::restoreText(QTextEdit *textEdit) {
    // Считываем содержимое из временного файла
    QFile file(tempFilePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        QString content = in.readAll();
        file.close();

        // Вставляем содержимое обратно в текстовое поле
        textEdit->setPlainText(content);
    } else {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось восстановить текст из временного файла.");
    }
}
