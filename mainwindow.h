#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openFile_triggered();
    void on_saveFile_triggered();
    void clearAndSave();
    void restoreFromTemp();
    void on_fontChange_triggered();
    void on_colorChange_triggered();
    void on_search_triggered();
    void on_replace_triggered();
    void on_createTable_triggered();
    void tabChanged(int index);

private:
    Ui::MainWindow *ui;
    QTabWidget *tabWidget;
    QFile tempFile;
    bool isTempFileEmpty;
    bool isContentModified;
    QString lastFilePath;

    void loadSettings();
    void saveSettings();
    void saveToTempFile();
    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWINDOW_H
