#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edit_functions.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QFontDialog>
#include <QDebug>
#include <QSpinBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QSettings>
#include <QTextTable>
#include "graphics_editor.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Восстанавливаем предыдущие настройки
    QSettings settings("MyCompany", "MyApp");

    // Восстанавливаем размер и положение окна
    resize(settings.value("windowSize", QSize(800, 600)).toSize());
    move(settings.value("windowPosition", QPoint(200, 200)).toPoint());

    // Восстанавливаем содержимое текстового редактора
    ui->textEdit->setHtml(settings.value("documentText", "").toString());

    // Восстанавливаем шрифт
    QFont font = settings.value("font", QFont()).value<QFont>();
    ui->textEdit->setFont(font);


    // Настройка таблиц

            //->setStyleSheet("QTableWidget::item { padding: 10px; }");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings settings("MyCompany", "MyApp");

    // Сохраняем размер и положение окна
    settings.setValue("windowSize", size());
    settings.setValue("windowPosition", pos());

    // Сохраняем содержимое текстового редактора
    settings.setValue("documentText", ui->textEdit->toHtml());

    // Сохраняем шрифт
    settings.setValue("font", ui->textEdit->font());

    QMainWindow::closeEvent(event);
}

void MainWindow::on_actionBold_triggered() {
    QTextCharFormat format = ui->textEdit->currentCharFormat();
    format.setFontWeight(ui->actionBold->isChecked() ? QFont::Bold : QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::on_actionItalic_triggered() {
    QTextCharFormat format = ui->textEdit->currentCharFormat();
    format.setFontItalic(ui->actionItalic->isChecked());
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::on_actionUnderline_triggered() {
    QTextCharFormat format = ui->textEdit->currentCharFormat();
    format.setFontUnderline(ui->actionUnderline->isChecked());
    ui->textEdit->mergeCurrentCharFormat(format);
}


void MainWindow::on_actionSelectFont_triggered() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        QTextCharFormat fmt;
        fmt.setFont(font);
        updateTextFormat(fmt);
    }
}


void MainWindow::updateTextFormat(const QTextCharFormat &format) {
    QTextCursor cursor = ui->textEdit->textCursor();

    if (cursor.hasSelection()) {
        cursor.mergeCharFormat(format);
    }

    QTextEdit::ExtraSelection selection;
    selection.format = format;
    ui->textEdit->setCurrentCharFormat(format);
}



void MainWindow::on_actionFontSize_triggered() {
    QDialog dialog(this);
    dialog.setWindowTitle("Font Size");

    QSpinBox *spinBox = new QSpinBox(&dialog);
    spinBox->setRange(1, 100);
    spinBox->setValue(12); // Default font size

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(spinBox);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        int fontSize = spinBox->value();
        QTextCharFormat fmt;
        fmt.setFontPointSize(fontSize);
        updateTextFormat(fmt);
    }
}


void MainWindow::on_actionToggleFullScreen_triggered() {
    if (isFullScreen()) {
        showNormal();
    } else {
        showFullScreen();
    }
}

void MainWindow::on_actionNew_triggered() {
    if (!ui->textEdit->toPlainText().isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Warning", "Unsaved changes. Do you want to save?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            on_actionSave_triggered();
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }
    ui->textEdit->clear();
}

void MainWindow::on_actionOpen_triggered() {
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "Rich Text Format (*.rtf);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->textEdit->setHtml(in.readAll());
            file.close();
        }
    }
}

void MainWindow::on_actionSave_triggered() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "Rich Text Format (*.rtf);;All Files (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toHtml();
            file.close();
        }
    }
}

void MainWindow::on_actionPaste_triggered() {
    ui->textEdit->paste();
}


void MainWindow::on_actionFind_triggered() {
    QDialog dialog(this);
    dialog.setWindowTitle("Find");

    QLineEdit *findLineEdit = new QLineEdit(&dialog);
    QLabel *label = new QLabel("Enter text to find:", &dialog);
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(label);
    layout->addWidget(findLineEdit);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString text = findLineEdit->text();
        if (!text.isEmpty()) {
            EditFunctions::findText(ui->textEdit, text);
        }
    }
}


void MainWindow::on_actionReplace_triggered() {
    QDialog dialog(this);
    dialog.setWindowTitle("Replace");

    QLineEdit *oldTextLineEdit = new QLineEdit(&dialog);
    QLineEdit *newTextLineEdit = new QLineEdit(&dialog);
    QLabel *labelOld = new QLabel("Enter text to replace:", &dialog);
    QLabel *labelNew = new QLabel("Enter new text:", &dialog);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);

    QVBoxLayout *layout = new QVBoxLayout(&dialog);
    layout->addWidget(labelOld);
    layout->addWidget(oldTextLineEdit);
    layout->addWidget(labelNew);
    layout->addWidget(newTextLineEdit);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QString oldText = oldTextLineEdit->text();
        QString newText = newTextLineEdit->text();
        if (!oldText.isEmpty() && !newText.isEmpty()) {
            EditFunctions::replaceText(ui->textEdit, oldText, newText);
        }
    }
}

void MainWindow::on_actionClear_triggered() {
    EditFunctions::clearText(ui->textEdit);
}

void MainWindow::on_actionUndo_triggered() {
    EditFunctions::undoText(ui->textEdit);
}

void MainWindow::on_actionCopy_triggered() {
    EditFunctions::copyText(ui->textEdit);
}

void MainWindow::on_actionRedo_triggered()
{
     EditFunctions::redoText(ui->textEdit);
}

void MainWindow::on_actionInsertTable_triggered()
{
    bool ok;
    int rows = QInputDialog::getInt(this, "Вставить таблицу", "Количество строк:", 2, 1, 100, 1, &ok);
    if (ok) {
        int columns = QInputDialog::getInt(this, "Вставить таблицу", "Количество столбцов:", 2, 1, 100, 1, &ok);
        if (ok) {
            QTextCursor cursor = ui->textEdit->textCursor();
            QTextTableFormat tableFormat;
            tableFormat.setBorder(1);
            tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);
            tableFormat.setCellPadding(10);
            cursor.insertTable(rows, columns, tableFormat);
        }
    }
}

void MainWindow::on_actionAddColumn_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
     QTextTable *table = cursor.currentTable();
     if (table) {
         table->appendColumns(1);
     } else {
         QMessageBox::warning(this, "Предупреждение", "Пожалуйста, поместите курсор внутри таблицы.");
     }
}

void MainWindow::on_actionAddRow_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (table) {
        table->appendRows(1);
    } else {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, поместите курсор внутри таблицы.");
    }
}

void MainWindow::on_actionRemoveRow_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (table) {
        int row = table->cellAt(cursor).row();

        // Show a confirmation dialog before deletion
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение",
                                      QString("Вы уверены, что хотите удалить строку %1?").arg(row + 1),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            table->removeRows(row, 1);
        }
    } else {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, поместите курсор внутри таблицы.");
    }
}

void MainWindow::on_actionRemoveColumn_triggered()
{
    QTextCursor cursor = ui->textEdit->textCursor();
    QTextTable *table = cursor.currentTable();
    if (table) {
        int col = table->cellAt(cursor).column();

        // Show a confirmation dialog before deletion
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Подтверждение",
                                      QString("Вы уверены, что хотите удалить столбец %1?").arg(col + 1),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            table->removeColumns(col, 1);
        }
    } else {
        QMessageBox::warning(this, "Предупреждение", "Пожалуйста, поместите курсор внутри таблицы.");
    }
}
void MainWindow::on_actionDataRecovery_triggered() {
    // Путь к временном файлу
    QString tempFilePath = "temporary.txt"; // Убедитесь, что путь правильный

    // Открываем временный файл для чтения
    QFile file(tempFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть временный файл для восстановления данных.");
        return;
    }

    // Читаем содержимое файла
    QTextStream in(&file);
    QString recoveredText = in.readAll();
    file.close();

    // Восстанавливаем текст в QTextEdit
    ui->textEdit->setPlainText(recoveredText);

    // Показать уведомление об успешном восстановлении
    QMessageBox::information(this, "Восстановление", "Данные успешно восстановлены из временного файла.");
}

void MainWindow::on_actionfontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Выберите цвет шрифта");

       if (color.isValid()) {
           QTextCharFormat format;
           format.setForeground(color);
           updateTextFormat(format);
       }
}
void MainWindow::on_actionNew_2_triggered() {
    GraphicsEditorWindow *editorWindow = new GraphicsEditorWindow(this);
    editorWindow->show();
}

