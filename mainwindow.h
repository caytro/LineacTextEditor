#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTabBar>
#include <QTextDocument>
#include <QTextCursor>
#include <QSettings>
#include <QApplication>
#include <QDebug>
#include <QFileInfo>
#include <QDialog>
#include <QMessageBox>
#include <QCloseEvent>

#include "myplaintextedit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr, QApplication *a = nullptr);



    ~MainWindow();



    // getters and setters

    MyPlainTextEdit *getCurrentPlainTextEdit() const;


    // public methods

    void hideSearchBar();

    void showSearchBar();

    int newTab(QString tabName = QString("New Tab"));

    void majLabelCursor();

    void majCurrentTabCaption();

    bool fileNameAlreadyOpen(QString filename);

    void initFileRecentMenu();

    void addFileRecentToMenu(QString filename,bool force=false);

    void addFileRecentToSettings(QString filename);

    bool isAlreadyInRecentSettings(QString filename);




private slots:
    int menuBarActionFileOpen();
    int menuBarActionFileSave();
    int menuBarActionFileSaveAs();
    int menuBarActionFileNew();
    void menuBarActionFileQuit();
    void menuBarFileRecent();
    void menuBarActionEditFind();

    int plainTextEditCursorPositionChanged();
    int plainTextEditorTextChanged();
    int tabWidgetCurrentChanged(int index);
    void tabWidgetTabCloseRequested(int index);

    void pushButtonCloseFindBar();
    void pushButtonFindNext();
    void pushButtonFindPrev();
    void pushButtonReplace();


private:
    Ui::MainWindow *ui;
    QCoreApplication *application;




};
#endif // MAINWINDOW_H
