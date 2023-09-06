#include "myplaintextedit.h"

MyPlainTextEdit::MyPlainTextEdit()
{
    hasFileName = false;
    initialContent= QString("");
    initialFileName = QString("");
}
    // getters and setters


bool MyPlainTextEdit::getHasFileName() const
{
    return hasFileName;
}


void MyPlainTextEdit::setHasFileName(bool newHasFileName)
{
    hasFileName = newHasFileName;
}


const QString &MyPlainTextEdit::getInitialFileName() const
{
    return initialFileName;
}


void MyPlainTextEdit::setInitialFileName(const QString &newInitialFileName)
{
    initialFileName = newInitialFileName;
    hasFileName = true;
}



// Public methods


int MyPlainTextEdit::readFileContent()
{
    if (hasFileName){
        QFile file(initialFileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QString textContent("");
            while (!file.atEnd()) {
                QByteArray line = file.readLine();
                textContent.append(QString(line));
            }
            hasFileName=true;
            this->setPlainText(textContent);
            initialContent = textContent;
        } else {
            QMessageBox msgBox;
            msgBox.setText("L'ouverture de " + initialFileName + " a échoué");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            return 1;
        }
    } else {
        qDebug() << "MyPlainTextEdit::readFileContent() : hasFileName=false";
        return 2;
    }
    return 0;
}

int MyPlainTextEdit::saveToFile()
{
    if (hasFileName){
        QFile file(initialFileName);
        qDebug() << "Save to file :" << getInitialFileName();
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream textStream(&file);
            textStream << this->toPlainText();
            initialContent = this->toPlainText();
        } else {
            QMessageBox msgBox;
            msgBox.setText("L'enregistrement de " + initialFileName + " a échoué");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            return 1;
        }
    } else {
        qDebug() << "MyPlainTextEdit::readFileContent() : hasFileName=false";
        return 2;
    }
    return 0;
}


int MyPlainTextEdit::saveAsToFile(QString fileName)
{
    setInitialFileName(fileName);
    hasFileName=true;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream textStream(&file);
        textStream << this->toPlainText();
        initialContent = this->toPlainText();
    } else {
        QMessageBox msgBox;
        msgBox.setText("L'enregistrement de " + initialFileName + " a échoué");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();
        return 1;
    }
    return 0;
}

bool MyPlainTextEdit::isModified()
{
    return (this->toPlainText() != initialContent);
}


