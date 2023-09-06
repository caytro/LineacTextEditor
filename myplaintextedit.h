#ifndef MYPLAINTEXTEDIT_H
#define MYPLAINTEXTEDIT_H

#include <QPlainTextEdit>
#include <QString>
#include <QFile>
#include <QList>
#include <QDebug>
#include <QTextDocument>
#include <QTextStream>
#include <QMessageBox>


class MyPlainTextEdit : public QPlainTextEdit
{
    QString initialFileName;
    QString initialContent;
    bool hasFileName = false;

public:
    MyPlainTextEdit();

    // getters and setters

    const QString &getInitialFileName() const;
    void setInitialFileName(const QString &newInitialFileName);

    bool getHasFileName() const;
    void setHasFileName(bool newHasFileName);


    // Methodes

    int readFileContent();
    int saveToFile();
    int saveAsToFile(QString fileName);
    bool isModified();
    void setInitialContent(QString s);


    int getTabIndex() const;
    void setTabIndex(int newTabIndex);
};

#endif // MYPLAINTEXTEDIT_H
