#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, QApplication *a)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    while (ui->tabWidget->count()>0)ui->tabWidget->removeTab(0);

    // hide search bar
    hideSearchBar();
    newTab();

    application = a;

    //SLOTS
    // Application

    connect(a, SIGNAL(aboutToQuit()), this, SLOT(menuBarActionFileQuit()));

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

MainWindow::~MainWindow()
{
    delete ui;
}

// getters and setters


MyPlainTextEdit *MainWindow::getCurrentPlainTextEdit() const
{
    return static_cast<MyPlainTextEdit*>(ui->tabWidget->currentWidget());
}


// public methods


void MainWindow::hideSearchBar()
{
    ui->frameSearchBar->hide();
}


void MainWindow::showSearchBar()
{
    ui->frameSearchBar->show();

    ui->lineEditFind->setFocus();
}


int MainWindow::newTab(QString tabName)
{
    MyPlainTextEdit* newMpte = new MyPlainTextEdit();
    ui->tabWidget->addTab(newMpte,tabName);
    ui->tabWidget->setCurrentWidget(newMpte);
    newMpte->setFocus();
    majCurrentTabCaption();
    connect(newMpte, SIGNAL(cursorPositionChanged()), this, SLOT(plainTextEditCursorPositionChanged()));
    connect(newMpte, SIGNAL(textChanged()), this, SLOT(plainTextEditorTextChanged()));

    return 0;
}




void MainWindow::majLabelCursor()
{
    QTextCursor textCursor = getCurrentPlainTextEdit()->textCursor();
    int lineNumber = textCursor.blockNumber();
    int colNumber = textCursor.positionInBlock();

    QString labelText("Lig : ");
    labelText.append(QString::number(lineNumber+1));
    labelText.append(" Col : ");
    labelText.append(QString::number(colNumber+1));
    ui->label->setText(labelText);
}

void MainWindow::majCurrentTabCaption()
{
    QString caption;

    if ( getCurrentPlainTextEdit()->getHasFileName()){
        QFileInfo fi(getCurrentPlainTextEdit()->getInitialFileName());
        caption = QString(fi.fileName());
    } else {
        caption = QString("Document Sans Titre");
    }
    if (getCurrentPlainTextEdit()->isModified()) {
        caption.append("*");
    }
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),caption);
}

bool MainWindow::fileNameAlreadyOpen(QString filename)
{
    bool response = false;
    if(ui->tabWidget->count() >0)

    {
        MyPlainTextEdit* mpte;
        for (int i = 0; i<ui->tabWidget->count(); i++)
        {
            mpte=static_cast<MyPlainTextEdit*>(ui->tabWidget->widget(i));
            if (mpte->getHasFileName() && (mpte->getInitialFileName() == filename)) response = true;
        }
    }
    return response;
}

//   SLOTS



int MainWindow::menuBarActionFileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Text File"),
         //"/home/sylvain/ajc/formation/CPP_projet/documents",
         "",
         "");

    if (!fileName.isEmpty())
    {
        if(fileNameAlreadyOpen(fileName)){
            QMessageBox msgBox;
            msgBox.setText("Le fichier " + fileName + " est déjà ouvert dans l'application");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            return 1;
        }
        if (ui->tabWidget->count() >0)
        {
            if (getCurrentPlainTextEdit()->isModified() || getCurrentPlainTextEdit()->getHasFileName()) {
                newTab();
            }
        }
        else
        {
            newTab();
        }
        MyPlainTextEdit* mPte = getCurrentPlainTextEdit();
        mPte->setInitialFileName(fileName);
        mPte->readFileContent();
        majCurrentTabCaption();
        QAction *myAction = new QAction(fileName);
        connect(myAction, SIGNAL(triggered(bool)), this, SLOT(menuBarFileRecent()));
        ui->menuRecent->addAction(myAction);
    }

    return 0;
}

int MainWindow::menuBarActionFileSave()
{
    if (getCurrentPlainTextEdit()->getHasFileName()){
        getCurrentPlainTextEdit()->saveToFile();
        majCurrentTabCaption();
    }else{
        menuBarActionFileSaveAs();
    }
    return 0;
}


int MainWindow::menuBarActionFileSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save As Text File"),
         "",
         "");
    if (!fileName.isEmpty())
    {
        if(fileNameAlreadyOpen(fileName)){
            QMessageBox msgBox;
            msgBox.setText("Le fichier " + fileName + " est déjà ouvert dans l'application");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            return 1;
        }
        getCurrentPlainTextEdit()->setInitialFileName(fileName);
        getCurrentPlainTextEdit()->saveAsToFile(fileName);
        majCurrentTabCaption();
        QAction *myAction = new QAction(fileName);
        connect(myAction, SIGNAL(triggered(bool)), this, SLOT(menuBarFileRecent()));
        ui->menuRecent->addAction(myAction);
    }
    return 0;
}

int MainWindow::menuBarActionFileNew()
{
    newTab();
    majCurrentTabCaption();
    return 0;
}


void MainWindow::menuBarActionFileQuit()
{
    bool unsaved=false;
    bool close=true;
    if (ui->tabWidget->count() >0){
        for (int i=0; i< ui->tabWidget->count(); i++){
            if (static_cast<MyPlainTextEdit*>(ui->tabWidget->widget(i))->isModified()) unsaved=true;
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


void MainWindow::menuBarFileRecent()
{
    QAction *myAction = static_cast<QAction*>(sender());
    QString fileName = myAction->text();
    if(ui->tabWidget->count()>0)
    {
        if (getCurrentPlainTextEdit()->isModified() || getCurrentPlainTextEdit()->getHasFileName() ) {
            newTab();
        }
    }
    else
    {
        newTab();
    }
    getCurrentPlainTextEdit()->setInitialFileName(fileName);
    getCurrentPlainTextEdit()->readFileContent();
    majCurrentTabCaption();
}


void MainWindow::menuBarActionEditFind()
{
    showSearchBar();
}


int MainWindow::plainTextEditCursorPositionChanged()
{
    majLabelCursor();
    return 0;
}


int MainWindow::plainTextEditorTextChanged()
{
    majCurrentTabCaption();
    return 0;
}


int MainWindow::tabWidgetCurrentChanged(int )
{
    if(ui->tabWidget->count()>0)
    {
        getCurrentPlainTextEdit()->setFocus();
        majLabelCursor();
    }
    return 0;
}


void MainWindow::tabWidgetTabCloseRequested(const int index)
{
    bool suppress=true;
    int response=QMessageBox::Discard;

    if (getCurrentPlainTextEdit()->isModified()){
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

    if (suppress)
    {
        if (ui->tabWidget->count()>1)
        {
            ui->tabWidget->removeTab(index);
        } else
        {
            ui->tabWidget->clear();
        }
    }

}


void MainWindow::pushButtonCloseFindBar()
{
    hideSearchBar();
}


void MainWindow::pushButtonFindPrev()
{
    QString searchedText = ui->lineEditFind->text();
    getCurrentPlainTextEdit()->find(searchedText,QTextDocument::FindBackward);
}


void MainWindow::pushButtonFindNext()
{
    QString searchedText = ui->lineEditFind->text();

    getCurrentPlainTextEdit()->find(searchedText);
}


void MainWindow::pushButtonReplace()
{
    getCurrentPlainTextEdit()->textCursor().insertText(ui->lineEditReplace->text());


}



