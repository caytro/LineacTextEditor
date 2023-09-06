#ifndef MYDOCUMENT_H
#define MYDOCUMENT_H

#include <QString>
#include <QFile>
#include <QList>
#include <QDebug>
#include <QTextDocument>
#include <QPlainTextEdit>
#include <QTextStream>



class MyDocument
{
    QString initialFileName;
    QString initialContent;
    QPlainTextEdit *plainTextEdit;

    int tabIndex;
    bool hasFileName = false;



public:
    MyDocument();

    // getters ans setters

    const QString &getInitialFileName() const;
    void setInitialFileName(const QString &newInitialFileName);

     QPlainTextEdit *getPlainTextEdit() const;
    void setPlainTextEdit(QPlainTextEdit *newPlainTextEdit);

    bool getHasFileName() const;
    void setHasFileName(bool newHasFileName);


    // Methodes

    void readFileContent();
    int saveToFile();
    int saveAsToFile(QString fileName);
    bool isModified();
    void setInitialContent(QString s);


    int getTabIndex() const;
    void setTabIndex(int newTabIndex);
};

#endif // MYDOCUMENT_H
