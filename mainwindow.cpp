#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    while (ui->tabWidget->count()>0)ui->tabWidget->removeTab(0);

    myDocuments = new QList<MyDocument*>;

    // hide search bar
    hideSearchBar();
    newTab();

    //SLOTS
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

MyDocument *MainWindow::getCurrentDocument() const
{
    return currentDocument;
}

void MainWindow::setCurrentDocument(MyDocument *newCurrentDocument)
{
    currentDocument = newCurrentDocument;
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
    }

    return 0;
}

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
    MainWindow::close();

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
    //qDebug() << "TextChanged";
    majCurrentTabCaption();
    return 0;
}

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


void MainWindow::tabWidgetTabCloseRequested(const int index)
{
    qDebug() << "Close Tab " << index;
    debugOnglets();

    if (ui->tabWidget->count()>1){
        ui->tabWidget->removeTab(index);
        myDocuments->removeAt(index);
    } else {
        myDocuments->clear();
        ui->tabWidget->clear();
    }
    qDebug() << "Après Suppression : ";
    //debugOnglets();
}

void MainWindow::pushButtonCloseFindBar()
{
    hideSearchBar();
}

void MainWindow::pushButtonFindPrev()
{
    QString searchedText = ui->lineEditFind->text();
    currentDocument->getPlainTextEdit()->find(searchedText,QTextDocument::FindBackward);
}

void MainWindow::pushButtonFindNext()
{
    QString searchedText = ui->lineEditFind->text();

    currentDocument->getPlainTextEdit()->find(searchedText);
}


void MainWindow::pushButtonReplace()
{
    currentDocument->getPlainTextEdit()->textCursor().insertText(ui->lineEditReplace->text());


}



