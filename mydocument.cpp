#include "mydocument.h"


MyDocument::MyDocument()
{
    initialFileName = QString("");

    plainTextEdit = new QPlainTextEdit();
    hasFileName = false;
    initialContent= QString("");

}

// getters and setters

int MyDocument::getTabIndex() const
{
    return tabIndex;
}

void MyDocument::setTabIndex(int newTabIndex)
{
    tabIndex = newTabIndex;
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

}


const QString &MyDocument::getInitialFileName() const
{
    return initialFileName;
}

void MyDocument::setInitialFileName(const QString &newInitialFileName)
{
    initialFileName = newInitialFileName;
    hasFileName = true;
}



// Public methods

/**
 * @brief MyDocument::readFileContent
 */

void MyDocument::readFileContent()
{
    QFile file(getInitialFileName());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        //qDebug() << "readFileContent : initialFileName " << getInitialFileName();
        //qDebug() << "file " << file.exists();
        int cptLine = 0;
        QString textContent("");
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            //qDebug() << "Ligne " << ++cptLine << line;
            textContent.append(QString(line));
        }
        //qDebug() << "readFileContent : textContent " << textContent;
        hasFileName=true;
        plainTextEdit->setPlainText(textContent);
        initialContent = textContent;
    } else {
        //qDebug() << "Fail open " << initialFileName;
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
        initialContent = plainTextEdit->toPlainText();
        //qDebug() << "Save : plainTextEdit->toPlainText()" << plainTextEdit->toPlainText();
    }

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
        initialContent = plainTextEdit->toPlainText();
        // qDebug() << "Save : plainTextEdit->toPlainText()" << plainTextEdit->toPlainText();
    }

    return 0;
}

bool MyDocument::isModified()
{
    return (getPlainTextEdit()->toPlainText() != initialContent);
}



