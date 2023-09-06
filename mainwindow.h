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

#include "mydocument.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // getters and setters

    MyDocument *getCurrentDocument() const;
    QString defaultDir ="~";
    void setCurrentDocument(MyDocument *newCurrentDocument);
    int newTab(QString tabName = QString("New Tab"));
    void majLabelCursor();
    void majCurrentTabCaption();
    void debugOnglets();

private slots:
    int menuBarActionFileOpen();
    int menuBarActionFileSave();
    int menuBarActionFileSaveAs();
    int menuBarActionFileNew();
    void menuBarActionFileQuit();
    int plainTextEditCursorPositionChanged();
    int plainTextEditorTextChanged();
    int tabWidgetCurrentChanged(int index);
    void tabWidgetTabCloseRequested(int index);


private:
    Ui::MainWindow *ui;
    QList<MyDocument*> *myDocuments;
    MyDocument *currentDocument;
};
#endif // MAINWINDOW_H
