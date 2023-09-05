#include "mydocument.h"





MyDocument::MyDocument()
{
    initialFileName = QString("");

    plainTextEdit = new QPlainTextEdit();
    textDocument = new QTextDocument();
    hasFileName = false;
    isModified= false;

}

// getters and setters

bool MyDocument::getIsModified() const
{
    return isModified;
}

void MyDocument::setIsModified(bool newIsModified)
{
    isModified = newIsModified;
}

bool MyDocument::getHasFileName() const
{
    return hasFileName;
}

void MyDocument::setHasFileName(bool newHasFileName)
{
    hasFileName = newHasFileName;
}

QPlainTextEdit *MyDocument::getPlainTextEdit() const
{
    return plainTextEdit;
}

void MyDocument::setPlainTextEdit(QPlainTextEdit *newPlainTextEdit)
{
    plainTextEdit = newPlainTextEdit;
    //plainTextEdit->setDocument(textDocument);
}

QTextDocument *MyDocument::getTextDocument() const
{
    return textDocument;
}

void MyDocument::setTextDocument(QTextDocument *newTextDocument)
{
    textDocument = newTextDocument;
    //plainTextEdit->setDocument(textDocument);
}

const QString &MyDocument::getInitialFileName() const
{
    return initialFileName;
}

void MyDocument::setInitialFileName(const QString &newInitialFileName)
{
    initialFileName = newInitialFileName;
}



// Public methods

/**
 * @brief MyDocument::readFileContent
 */

void MyDocument::readFileContent()
{
    QFile file(getInitialFileName());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "readFileContent : initialFileName " << getInitialFileName();
        qDebug() << "file " << file.exists();
        int cptLine = 0;
        QString textContent("");
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            qDebug() << "Ligne " << ++cptLine << line;
            textContent.append(QString(line));
        }
        qDebug() << "readFileContent : textContent " << textContent;
        isModified = false;
        hasFileName=true;
        plainTextEdit->setPlainText(textContent);
    } else {
        qDebug() << "Fail open " << initialFileName;
    }

}


int MyDocument::saveToFile()
{
    QFile file(getInitialFileName());
    qDebug() << "Save to file :" << getInitialFileName();
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        textStream << plainTextEdit->toPlainText();
        qDebug() << "Save : plainTextEdit->toPlainText()" << plainTextEdit->toPlainText();
    }
    isModified=false;
    return 0;

}

int MyDocument::saveAsToFile(QString fileName)
{
    setInitialFileName(fileName);
    hasFileName=true;
    QFile file(getInitialFileName());
    qDebug() << "Save As to file :" << getInitialFileName();
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        textStream << plainTextEdit->toPlainText();
        qDebug() << "Save : plainTextEdit->toPlainText()" << plainTextEdit->toPlainText();
    }
    isModified=false;
    return 0;
}

int MyDocument::raz()
{
    initialFileName = "";
    hasFileName = false;
    isModified = false;
    plainTextEdit->setPlainText("");
    return 0;
}

