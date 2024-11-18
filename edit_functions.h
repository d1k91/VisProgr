#ifndef EDIT_FUNCTIONS_H
#define EDIT_FUNCTIONS_H

#include <QTextEdit>

class EditFunctions {
public:
    static void findText(QTextEdit *textEdit, const QString &text);
    static void replaceText(QTextEdit *textEdit, const QString &oldText, const QString &newText);
    static void clearText(QTextEdit *textEdit);
    static void undoText(QTextEdit *textEdit);
    static void redoText(QTextEdit *textEdit);
    static void copyText(QTextEdit *textEdit);
    static void pasteText(QTextEdit *textEdit); // Добавлено объявление функции pasteText
    static void restoreText(QTextEdit *textEdit); // Добавлено объявление функции restoreText

private:
    static QString tempFilePath; // Путь к временным файлам
};

#endif // EDIT_FUNCTIONS_H
