#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionNew, SIGNAL(triggered(bool )), this, SLOT(menuBarActionFileNew()));
    connect(ui->actionOpen, SIGNAL(triggered(bool )), this, SLOT(menuBarActionFileOpen()));
    connect(ui->actionSave, SIGNAL(triggered(bool )), this, SLOT(menuBarActionFileSave()));
    connect(ui->actionSave_As, SIGNAL(triggered(bool )), this, SLOT(menuBarActionFileSaveAs()));
    connect(ui->actionQuit, SIGNAL(triggered(bool )), this, SLOT(menuBarActionFileQuit()));
    connect(ui->plainTextEdit, SIGNAL(cursorPositionChanged()), this, SLOT(plainTextEditCursorPositionChanged()));
    connect(ui->plainTextEdit, SIGNAL(textChanged()), this, SLOT(plainTextEditorTextChanged()));


    myDocuments = new QList<MyDocument>;
    currentDocument = new MyDocument();
    currentDocument->setPlainTextEdit(ui->plainTextEdit);
    myDocuments->append(*currentDocument);
    ui->tabWidget->setTabText(0,"Document Sans Titre");
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

int MainWindow::menuBarActionFileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,
         tr("Open Text File"),
         //"/home/sylvain/ajc/formation/CPP_projet/documents",
         "",
         tr("Text Files (*.txt *.h *.cpp)"));

    qDebug() << "Filename : " << fileName ;
    if (!fileName.isEmpty())
    {
        currentDocument->setInitialFileName(fileName);
        currentDocument->setPlainTextEdit(ui->plainTextEdit);
        currentDocument->readFileContent();
        ui->tabWidget->setTabText(0,fileName);
    }

    return 0;
}

int MainWindow::menuBarActionFileSave()
{
    if (currentDocument->getHasFileName()){
        currentDocument->saveToFile();
        ui->tabWidget->setTabText(0,currentDocument->getInitialFileName());
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
         "/home/sylvain/ajc/formation/CPP_projet/documents",
         tr("Text Files (*.txt *.h *.cpp)"));
    if (!fileName.isEmpty())
    {
        currentDocument->setInitialFileName(fileName);
        currentDocument->saveAsToFile(fileName);
        ui->tabWidget->setTabText(0,fileName);
    }
    return 0;
}

int MainWindow::menuBarActionFileNew()
{
    if (currentDocument->getIsModified()){
        qDebug() << "File New : File is Modified !";
        return 1;
        // demander save ?
    }
    currentDocument->raz();
    ui->tabWidget->setTabText(0,"Document Sans Titre");
    return 0;
}

void MainWindow::menuBarActionFileQuit()
{
    MainWindow::close();

}

int MainWindow::plainTextEditCursorPositionChanged()
{
    QTextCursor textCursor = ui->plainTextEdit->textCursor();
    int lineNumber = textCursor.blockNumber();
    int colNumber = textCursor.positionInBlock();

    QString labelText("Lig : ");
    labelText.append(QString::number(lineNumber+1));
    labelText.append(" Col : ");
    labelText.append(QString::number(colNumber+1));
    ui->label->setText(labelText);

    return 0;
}

int MainWindow::plainTextEditorTextChanged()
{
    currentDocument->setIsModified(true);
    if (currentDocument->getHasFileName()){
        ui->tabWidget->setTabText(0,currentDocument->getInitialFileName() + "*");
    } else {
        ui->tabWidget->setTabText(0,"Document Sans Titre*");
    }

}



