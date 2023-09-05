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
    QPlainTextEdit *plainTextEdit;

    int tabIndex;
    bool hasFileName = false;
    bool isModified = false;


public:
    MyDocument();

    // getters ans setters

    const QString &getInitialFileName() const;
    void setInitialFileName(const QString &newInitialFileName);

     QPlainTextEdit *getPlainTextEdit() const;
    void setPlainTextEdit(QPlainTextEdit *newPlainTextEdit);

    bool getHasFileName() const;
    void setHasFileName(bool newHasFileName);

    bool getIsModified() const;
    void setIsModified(bool newIsModified);

    // Methodes

    void readFileContent();
    int saveToFile();
    int saveAsToFile(QString fileName);


    int getTabIndex() const;
    void setTabIndex(int newTabIndex);
};

#endif // MYDOCUMENT_H
