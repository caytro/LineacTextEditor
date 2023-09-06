#include "mydocument.h"

///
/// \brief MyDocument::MyDocument
///
MyDocument::MyDocument()
{
    initialFileName = QString("");

    plainTextEdit = new QPlainTextEdit();
    hasFileName = false;
    initialContent= QString("");

}

// getters and setters

///
/// \brief MyDocument::getTabIndex
/// \return
///
int MyDocument::getTabIndex() const
{
    return tabIndex;
}

///
/// \brief MyDocument::setTabIndex
/// \param newTabIndex
///
void MyDocument::setTabIndex(int newTabIndex)
{
    tabIndex = newTabIndex;
}

///
/// \brief MyDocument::getHasFileName
/// \return
///
bool MyDocument::getHasFileName() const
{
    return hasFileName;
}

///
/// \brief MyDocument::setHasFileName
/// \param newHasFileName
///
void MyDocument::setHasFileName(bool newHasFileName)
{
    hasFileName = newHasFileName;
}

///
/// \brief MyDocument::getPlainTextEdit
/// \return
///
QPlainTextEdit *MyDocument::getPlainTextEdit() const
{
    return plainTextEdit;
}

void MyDocument::setPlainTextEdit(QPlainTextEdit *newPlainTextEdit)
{
    plainTextEdit = newPlainTextEdit;

}

///
/// \brief MyDocument::getInitialFileName
/// \return
///
const QString &MyDocument::getInitialFileName() const
{
    return initialFileName;
}

///
/// \brief MyDocument::setInitialFileName
/// \param newInitialFileName
///
void MyDocument::setInitialFileName(const QString &newInitialFileName)
{
    initialFileName = newInitialFileName;
    hasFileName = true;
}



// Public methods

///
/// \brief MyDocument::readFileContent
///
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

///
/// \brief MyDocument::saveToFile
/// \return
///
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

///
/// \brief MyDocument::saveAsToFile
/// \param fileName
/// \return
///
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

///
/// \brief MyDocument::isModified
/// \return
///
bool MyDocument::isModified()
{
    return (getPlainTextEdit()->toPlainText() != initialContent);
}



