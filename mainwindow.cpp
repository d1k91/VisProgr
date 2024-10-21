#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QInputDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QTextDocument>
#include <QSettings>
#include <QTextEdit>
#include <QTableWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCloseEvent>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isTempFileEmpty(true)
    , isContentModified(false)
{
    ui->setupUi(this);
    loadSettings();


    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);


    QTextEdit *textEdit = new QTextEdit(this);
    tabWidget->addTab(textEdit, "New File");

    connect(ui->Open, &QAction::triggered, this, &MainWindow::on_openFile_triggered);
    connect(ui->Save, &QAction::triggered, this, &MainWindow::on_saveFile_triggered);
    connect(ui->Clear, &QAction::triggered, this, &MainWindow::clearAndSave);
    connect(ui->Return, &QAction::triggered, this, &MainWindow::restoreFromTemp);
    connect(ui->actionChangeFont, &QAction::triggered, this, &MainWindow::on_fontChange_triggered);
    connect(ui->actionChangeColor, &QAction::triggered, this, &MainWindow::on_colorChange_triggered);
    connect(ui->Search, &QAction::triggered, this, &MainWindow::on_search_triggered);
    connect(ui->Replace, &QAction::triggered, this, &MainWindow::on_replace_triggered);
    connect(ui->Create, &QAction::triggered, this, &MainWindow::on_createTable_triggered);
    connect(tabWidget, &QTabWidget::currentChanged, this, &MainWindow::tabChanged);

    ui->actionChangeFont->setShortcut(QKeySequence("Ctrl+I"));
    ui->actionChangeColor->setShortcut(QKeySequence("Ctrl+O"));
    ui->Open->setShortcut(QKeySequence("Ctrl+R"));
    ui->Save->setShortcut(QKeySequence("Ctrl+S"));
    ui->Clear->setShortcut(QKeySequence("Ctrl+U"));
    ui->Return->setShortcut(QKeySequence("Ctrl+P"));
    ui->Search->setShortcut(QKeySequence("Ctrl+E"));
    ui->Replace->setShortcut(QKeySequence("Ctrl+W"));

    QLabel *backgroundLabel = new QLabel(this);
    backgroundLabel->setScaledContents(true);
    backgroundLabel->setGeometry(this->rect());
    backgroundLabel->lower();

    ui->Return->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("HTML Files (*.html);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Error"), tr("Cannot open file: %1").arg(file.errorString()));
            return;
        }
        QTextStream in(&file);
        QString htmlContent = in.readAll();
        file.close();


        QTextEdit *textEdit = new QTextEdit(this);
        textEdit->setHtml(htmlContent);
        int index = tabWidget->addTab(textEdit, QFileInfo(fileName).fileName());
        tabWidget->setCurrentIndex(index);
    }
}

void MainWindow::on_saveFile_triggered()
{
    QTextEdit *textEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if (!textEdit) return;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("HTML Files (*.html);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Error"), tr("Cannot save file: %1").arg(file.errorString()));
            return;
        }
        QTextStream out(&file);
        out << textEdit->toHtml();
        file.close();
        lastFilePath = fileName;
        isContentModified = false;

        // Обновляем имя вкладки
        tabWidget->setTabText(tabWidget->currentIndex(), QFileInfo(fileName).fileName());
    }
}

void MainWindow::saveToTempFile() {
    QTextEdit *textEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if (!textEdit) return;

    if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot write to temp file: %1").arg(tempFile.errorString()));
        return;
    }
    QTextStream out(&tempFile);
    out << textEdit->toHtml();
    tempFile.close();
    isTempFileEmpty = false;
}

void MainWindow::restoreFromTemp() {
    if (isTempFileEmpty) {
        QMessageBox::warning(this, tr("Warning"), tr("No text to restore."));
        return;
    }

    QFile file(tempFile.fileName());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot open temp file: %1").arg(file.errorString()));
        return;
    }
    QTextStream in(&file);
    QString htmlContent = in.readAll();
    file.close();

    QTextEdit *textEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if (textEdit) {
        textEdit->setHtml(htmlContent);
    }
}

void MainWindow::clearAndSave() {
    saveToTempFile();
    QTextEdit *textEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if (textEdit) {
        textEdit->clear();
    }
    ui->Return->setEnabled(true);
    isContentModified = false;
}

void MainWindow::on_fontChange_triggered() {
    QTextEdit *textEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if (!textEdit) return;

    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        QTextCursor cursor = textEdit->textCursor();
        if (!cursor.hasSelection()) {
            textEdit->setFont(font);
        } else {
            QTextCharFormat format;
            format.setFont(font);
            cursor.mergeCharFormat(format);
            textEdit->setTextCursor(cursor);
        }
        isContentModified = true;
    }
}

void MainWindow::on_colorChange_triggered() {
    QTextEdit *textEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if (!textEdit) return;

    QColor color = QColorDialog::getColor(Qt::white, this);
    if (color.isValid()) {
        textEdit->setTextColor(color);
        isContentModified = true;
    }
}

void MainWindow::on_search_triggered() {
    QTextEdit *textEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if (!textEdit) return;

    bool ok;
    QString searchText = QInputDialog::getText(this, "Search", "Enter text to search:", QLineEdit::Normal, "", &ok);

    if (ok && !searchText.isEmpty()) {
        QTextDocument *document = textEdit->document();
        QTextCursor cursor(document);

        // Ищем текст в документе
        cursor = document->find(searchText, cursor);

        if (!cursor.isNull()) {
            textEdit->setTextCursor(cursor);
        } else {
            QMessageBox::information(this, "Search", "Text not found.");
        }
    }
}

void MainWindow::on_replace_triggered() {
    QTextEdit *textEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if (!textEdit) return;

    bool ok;
    QString searchText = QInputDialog::getText(this, "Replace", "Enter text to search:", QLineEdit::Normal, "", &ok);

    if (ok && !searchText.isEmpty()) {
        QString replaceText = QInputDialog::getText(this, "Replace", "Enter text to replace with:", QLineEdit::Normal, "", &ok);

        if (ok) {
            QTextDocument *document = textEdit->document();
            QTextCursor cursor(document);

            // Ищем текст в документе
            cursor = document->find(searchText, cursor);

            if (!cursor.isNull()) {
                // Заменяем найденный текст
                cursor.insertText(replaceText);
                textEdit->setTextCursor(cursor);
            } else {
                QMessageBox::information(this, "Replace", "Text not found.");
            }
        }
    }
}

void MainWindow::on_createTable_triggered()
{
    QTextEdit *textEdit = qobject_cast<QTextEdit*>(tabWidget->currentWidget());
    if (!textEdit) return;

    bool ok;
    int rows = QInputDialog::getInt(this, tr("Input Rows"), tr("Number of rows:"), 1, 1, 100, 1, &ok);
    if (!ok) return;

    int columns = QInputDialog::getInt(this, tr("Input Columns"), tr("Number of columns:"), 1, 1, 100, 1, &ok);
    if (!ok) return;

    QString html = "<table border=\"1\">";
    for (int i = 0; i < rows; ++i) {
        html += "<tr>";
        for (int j = 0; j < columns; ++j) {
            html += "<td><div contenteditable=\"false\">&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</div></td>";
        }
        html += "</tr>";
    }
    html += "</table>";

    textEdit->append(html);
    isContentModified = true;
}

void MainWindow::tabChanged(int index) {
    Q_UNUSED(index);
    isContentModified = true;
}

void MainWindow::loadSettings() {
    QSettings settings("MyCompany", "MyApp");
    lastFilePath = settings.value("lastFilePath", "").toString();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (isContentModified) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Save Changes", "Do you want to save your changes?",
                                      QMessageBox::Save | QMessageBox::No  | QMessageBox::Cancel);
        if (reply == QMessageBox::Save) {
            on_saveFile_triggered();
        } else if (reply == QMessageBox::Cancel) {
            event->ignore();
            return;
        }
    }
    saveSettings();
    event->accept();
}

void MainWindow::saveSettings() {
    QSettings settings("MyCompany", "MyApp");
    settings.setValue("lastFilePath", lastFilePath);
}
