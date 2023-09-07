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

///
/// \brief The MainWindow class
/// \details this class manages the main application window
/// \author Sylvain Nadaud
/// \date 2023
///
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



    // getters and setters

    ///
    /// \brief getCurrentPlainTextEdit
    /// \return
    ///
    MyPlainTextEdit *getCurrentPlainTextEdit() const;


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
    /// \details displays text cursor coordinates lig: col:
    ///
    void majLabelCursor();

    ///
    /// \brief majCurrentTabCaption
    /// \details displays tabTitle filename, or Document Sans Non. Add a star * if modified
    ///
    void majCurrentTabCaption();

    ///
    /// \brief fileNameAlreadyOpen
    /// \details used to prevent duplicate tabs on file open or saveAs
    /// \param filename
    /// \return
    ///
    bool fileNameAlreadyOpen(QString filename);

    ///
    /// \brief initFileRecentMenu
    /// \details load previous sessions recent files and update file recents menu on application launch, file open, and saveAs
    ///
    void initFileRecentMenu();

    ///
    /// \brief addFileRecentToMenu
    /// \param filename
    /// \param force
    ///
    void addFileRecentToMenu(QString filename,bool force=false);

    ///
    /// \brief addFileRecentToSettings
    /// \param filename
    /// \details update recents QSettings, on file open and saveAs if not already stored. Then update file recent menu
    void addFileRecentToSettings(QString filename);

    ///
    /// \brief isAlreadyInRecentSettings
    /// \details used to prevent dupicate item in recent Qsettings
    /// \param filename
    /// \return
    ///
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
