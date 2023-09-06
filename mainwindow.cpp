#include "mainwindow.h"
#include "ui_mainwindow.h"

///
/// \brief MainWindow::MainWindow
/// \param parent
/// \param a
///
MainWindow::MainWindow(QWidget *parent, QApplication *a)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    while (ui->tabWidget->count()>0)ui->tabWidget->removeTab(0);

    myDocuments = new QList<MyDocument*>;
    application = a;


    // hide search bar
    hideSearchBar();
    newTab();

    //SLOTS

    // main window
    connect(application, SIGNAL(aboutToQuit()), this, SLOT(menuBarActionFileQuit()));
    // Menu File
    connect(ui->actionNew, SIGNAL(triggered(bool )), this, SLOT(menuBarActionFileNew()));
    connect(ui->actionOpen, SIGNAL(triggered(bool )), this, SLOT(menuBarActionFileOpen()));
    connect(ui->actionSave, SIGNAL(triggered(bool )), this, SLOT(menuBarActionFileSave()));
    connect(ui->actionSave_As, SIGNAL(triggered(bool )), this, SLOT(menuBarActionFileSaveAs()));
    connect(ui->actionQuit, SIGNAL(triggered(bool )), this, SLOT(menuBarActionFileQuit()));

    // Menu Edit
    connect(ui->actionFind, SIGNAL(triggered(bool )), this, SLOT(menuBarActionEditFind()));

    // tabWidgets
    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tabWidgetTabCloseRequested(int)));
    connect(ui->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(tabWidgetCurrentChanged(int)));

    // searchBar
    connect(ui->pushButtonCloseFindBar, SIGNAL(clicked()), this, SLOT(pushButtonCloseFindBar()));
    connect(ui->pushButtonFindNext, SIGNAL(clicked()), this, SLOT(pushButtonFindNext()));
    connect(ui->pushButtonFindPrev, SIGNAL(clicked()), this, SLOT(pushButtonFindPrev()));
    connect(ui->pushButtonReplace, SIGNAL(clicked()), this, SLOT(pushButtonReplace()));




}
///
/// \brief MainWindow::~MainWindow
///
MainWindow::~MainWindow()
{
    delete ui;
}

// getters and setters

///
/// \brief MainWindow::getCurrentDocument
/// \return
///
MyDocument *MainWindow::getCurrentDocument() const
{
    return currentDocument;
}
///
/// \brief MainWindow::setCurrentDocument
/// \param newCurrentDocument
///
void MainWindow::setCurrentDocument(MyDocument *newCurrentDocument)
{
    currentDocument = newCurrentDocument;
}

// public methods

///
/// \brief MainWindow::hideSearchBar
///
void MainWindow::hideSearchBar()
{
    ui->frameSearchBar->hide();
}

///
/// \brief MainWindow::showSearchBar
///
void MainWindow::showSearchBar()
{
    ui->frameSearchBar->show();

    ui->lineEditFind->setFocus();
}

///
/// \brief MainWindow::newTab
/// \param tabName
/// \return
///
int MainWindow::newTab(QString tabName)
{
    MyDocument* newDocument = new MyDocument();
    myDocuments->append(newDocument);
    currentDocument = newDocument;

    ui->tabWidget->addTab(currentDocument->getPlainTextEdit(),tabName);

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);
    currentDocument->setTabIndex(ui->tabWidget->currentIndex());

    currentDocument->getPlainTextEdit()->setFocus();
    majCurrentTabCaption();
    connect(currentDocument->getPlainTextEdit(), SIGNAL(cursorPositionChanged()), this, SLOT(plainTextEditCursorPositionChanged()));
    connect(currentDocument->getPlainTextEdit(), SIGNAL(textChanged()), this, SLOT(plainTextEditorTextChanged()));

    return 0;
}

///
/// \brief MainWindow::debugOnglets
///
void MainWindow::debugOnglets(){
    if(myDocuments->count()>0)
    {
        for (int i=0;i<ui->tabWidget->count(); i++){
            qDebug() << "indice " << i;
            qDebug() << "document : " << myDocuments->at(i)->getPlainTextEdit()->toPlainText();
            ui->tabWidget->setCurrentIndex(i);
            QPlainTextEdit* qpte =  static_cast<QPlainTextEdit*>(ui->tabWidget->currentWidget());
            qDebug() << "tabWidget : " << qpte->toPlainText();
        }
    } else {
        qDebug() << "aucun element dans myDocuments";
    }
}


///
/// \brief MainWindow::majLabelCursor
///
void MainWindow::majLabelCursor()
{
    QTextCursor textCursor = currentDocument->getPlainTextEdit()->textCursor();
    int lineNumber = textCursor.blockNumber();
    int colNumber = textCursor.positionInBlock();

    QString labelText("Lig : ");
    labelText.append(QString::number(lineNumber+1));
    labelText.append(" Col : ");
    labelText.append(QString::number(colNumber+1));
    ui->label->setText(labelText);
}

///
/// \brief MainWindow::majCurrentTabCaption
///
void MainWindow::majCurrentTabCaption()
{
    QString caption;

    if ( currentDocument->getHasFileName()){
        QFileInfo fi(currentDocument->getInitialFileName());
        caption = QString(fi.fileName());
    } else {
        caption = QString("Document Sans Titre");
    }
    if (currentDocument->isModified()) {
        caption.append("*");
    }
    ui->tabWidget->setTabText(currentDocument->getTabIndex(),caption);
}

//   SLOTS


///
/// \brief MainWindow::menuBarActionFileOpen
/// \return
///
int MainWindow::menuBarActionFileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Text File"),
         //"/home/sylvain/ajc/formation/CPP_projet/documents",
         "",
         "");

    qDebug() << "Filename : " << fileName ;
    if (!fileName.isEmpty())
    {
        if (currentDocument->isModified() || currentDocument->getHasFileName()) {
            newTab();
        }

        currentDocument->setInitialFileName(fileName);
        currentDocument->readFileContent();
        majCurrentTabCaption();
        QAction *myAction = new QAction(fileName);
        connect(myAction, SIGNAL(triggered(bool)), this, SLOT(menuBarFileRecent()));
        ui->menuRecent->addAction(myAction);
    }

    return 0;
}

///
/// \brief MainWindow::menuBarActionFileSave
/// \return
///
int MainWindow::menuBarActionFileSave()
{
    if (currentDocument->getHasFileName()){
        currentDocument->saveToFile();
        majCurrentTabCaption();
    }else{
        menuBarActionFileSaveAs();
    }
    return 0;
}

///
/// \brief MainWindow::menuBarActionFileSaveAs
/// \return
///
int MainWindow::menuBarActionFileSaveAs()
{
    qDebug() <<"SaveAs";
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save As Text File"),
         "",
         "");
    if (!fileName.isEmpty())
    {
        currentDocument->setInitialFileName(fileName);
        currentDocument->saveAsToFile(fileName);
        majCurrentTabCaption();
        QAction *myAction = new QAction(fileName);
        connect(myAction, SIGNAL(triggered(bool)), this, SLOT(menuBarFileRecent()));
        ui->menuRecent->addAction(myAction);
    }
    return 0;
}

///
/// \brief MainWindow::menuBarActionFileNew
/// \return
///
int MainWindow::menuBarActionFileNew()
{
    newTab();
    majCurrentTabCaption();
    return 0;
}

///
/// \brief MainWindow::menuBarActionFileQuit
///
void MainWindow::menuBarActionFileQuit()
{
    bool unsaved=false;
    bool close=false;
    if (myDocuments->count() >0){
        for (int i=0; i<myDocuments->count(); i++){
            if (myDocuments->at(i)->isModified()) unsaved=true;
        }
    }
    if (unsaved){
        QMessageBox msgBox;
        msgBox.setText("Somme documents have been modified.");
        msgBox.setInformativeText("Do you really want to quit?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No );
        msgBox.setDefaultButton(QMessageBox::Save);
        int response = msgBox.exec();
        if (response == QMessageBox::No){
            close=false;
        }
        else {
            close=true;
        }

    }
    if (close) MainWindow::close();

}

///
/// \brief MainWindow::menuBarFileRecent
///
void MainWindow::menuBarFileRecent()
{
    QAction *myAction = static_cast<QAction*>(sender());
    QString fileName = myAction->text();
    if (currentDocument->isModified() || currentDocument->getHasFileName()) {
        newTab();
    }

    currentDocument->setInitialFileName(fileName);
    currentDocument->readFileContent();
    majCurrentTabCaption();
}

///
/// \brief MainWindow::menuBarActionEditFind
///
void MainWindow::menuBarActionEditFind()
{
    showSearchBar();
}

///
/// \brief MainWindow::plainTextEditCursorPositionChanged
/// \return
///
int MainWindow::plainTextEditCursorPositionChanged()
{
    majLabelCursor();
    return 0;
}

///
/// \brief MainWindow::plainTextEditorTextChanged
/// \return
///
int MainWindow::plainTextEditorTextChanged()
{
    //qDebug() << "TextChanged";
    majCurrentTabCaption();
    return 0;
}

///
/// \brief MainWindow::tabWidgetCurrentChanged
/// \param index
/// \return
///
int MainWindow::tabWidgetCurrentChanged(int index)
{
    if(myDocuments->count()>0)
    {
        currentDocument = myDocuments->at(index);
        currentDocument->getPlainTextEdit()->setFocus();
        majLabelCursor();
    }
    return 0;
}

///
/// \brief MainWindow::tabWidgetTabCloseRequested
/// \param index
///
void MainWindow::tabWidgetTabCloseRequested(const int index)
{
    bool suppress=true;
    int response=QMessageBox::Discard;

    if (currentDocument->isModified()){
        suppress=false;
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        response = msgBox.exec();
        if (response == QMessageBox::Cancel){
            suppress=false;
        }
        else if (response == QMessageBox::Save){
            menuBarActionFileSave();
            suppress=true;
        }
        else if (response == QMessageBox::Discard){
            suppress=true;
        }
    }

    if (suppress)    {
        if (ui->tabWidget->count()>1){
            ui->tabWidget->removeTab(index);
            myDocuments->removeAt(index);
        } else {
            myDocuments->clear();
            ui->tabWidget->clear();
        }
    }

}

///
/// \brief MainWindow::pushButtonCloseFindBar
///
void MainWindow::pushButtonCloseFindBar()
{
    hideSearchBar();
}

///
/// \brief MainWindow::pushButtonFindPrev
///
void MainWindow::pushButtonFindPrev()
{
    QString searchedText = ui->lineEditFind->text();
    currentDocument->getPlainTextEdit()->find(searchedText,QTextDocument::FindBackward);
}

///
/// \brief MainWindow::pushButtonFindNext
///
void MainWindow::pushButtonFindNext()
{
    QString searchedText = ui->lineEditFind->text();

    currentDocument->getPlainTextEdit()->find(searchedText);
}

///
/// \brief MainWindow::pushButtonReplace
///
void MainWindow::pushButtonReplace()
{
    currentDocument->getPlainTextEdit()->textCursor().insertText(ui->lineEditReplace->text());


}



