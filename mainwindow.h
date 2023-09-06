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

#include "mydocument.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///
    /// \brief MainWindow
    /// \param parent
    /// \param a
    ///
    MainWindow(QWidget *parent = nullptr, QApplication *a = nullptr);


    ~MainWindow();

    ///
    /// \brief settings
    /// \return
    ///

    ///
    /// \brief settings
    /// \return
    ///
    QSettings settings();

    ///
    /// \brief messageBox
    ///
    QMessageBox *messageBox;

    ///
    /// \brief application
    ///
    QApplication *application;

    // getters and setters
    ///
    /// \brief getCurrentDocument
    /// \return
    ///
    MyDocument *getCurrentDocument() const;
    ///
    /// \brief setCurrentDocument
    /// \param newCurrentDocument
    ///
    void setCurrentDocument(MyDocument *newCurrentDocument);

    // public methods
    ///
    /// \brief hideSearchBar
    ///
    void hideSearchBar();
    ///
    /// \brief showSearchBar
    ///
    void showSearchBar();
    ///
    /// \brief newTab
    /// \param tabName
    /// \return
    ///
    int newTab(QString tabName = QString("New Tab"));
    ///
    /// \brief majLabelCursor
    ///
    void majLabelCursor();
    ///
    /// \brief majCurrentTabCaption
    ///
    void majCurrentTabCaption();
    ///
    /// \brief debugOnglets
    ///
    void debugOnglets();



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
    QList<MyDocument*> *myDocuments;
    MyDocument *currentDocument;

};
#endif // MAINWINDOW_H
