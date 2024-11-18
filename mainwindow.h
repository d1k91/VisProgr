#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextCharFormat>
#include <QSettings>
#include <QTextTable>
#include <QColorDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionPaste_triggered();
    void on_actionFind_triggered();
    void on_actionReplace_triggered();
    void on_actionClear_triggered();
    void on_actionCopy_triggered();
    void on_actionUndo_triggered();
    void on_actionToggleFullScreen_triggered();

    void on_actionBold_triggered();
    void on_actionItalic_triggered();
    void on_actionSelectFont_triggered();
    void on_actionFontSize_triggered();
    void on_actionUnderline_triggered();
    void on_actionRedo_triggered();
    void closeEvent(QCloseEvent *event) override;

    void on_actionInsertTable_triggered();

    void on_actionAddColumn_triggered();

    void on_actionAddRow_triggered();

    void on_actionRemoveRow_triggered();
    void on_actionRemoveColumn_triggered();
    void on_actionDataRecovery_triggered();

    void on_actionfontColor_triggered();

    void on_actionNew_2_triggered();

private:
    Ui::MainWindow *ui;

    void updateTextFormat(const QTextCharFormat &format);
};

#endif // MAINWINDOW_H
