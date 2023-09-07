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

///
/// \brief The MyPlainTextEdit class
/// \details extends QPlainTextEdit in order to store filename, load and save files
/// \author Sylvain Nadaud
/// \date 2023
///
class MyPlainTextEdit : public QPlainTextEdit
{
    QString initialFileName;
    QString initialContent;
    bool hasFileName = false;

public:
    ///
    /// \brief MyPlainTextEdit
    ///
    MyPlainTextEdit();

    // getters and setters

    ///
    /// \brief getInitialFileName
    /// \return
    ///
    const QString &getInitialFileName() const;
    ///
    /// \brief setInitialFileName
    /// \param newInitialFileName
    ///
    void setInitialFileName(const QString &newInitialFileName);

    ///
    /// \brief getHasFileName
    /// \return
    ///
    bool getHasFileName() const;
    ///
    /// \brief setHasFileName
    /// \param newHasFileName
    ///
    void setHasFileName(bool newHasFileName);


    // Methodes

    ///
    /// \brief readFileContent
    /// \return
    ///
    int readFileContent();

    ///
    /// \brief saveToFile
    /// \return
    ///
    int saveToFile();

    ///
    /// \brief saveAsToFile
    /// \param fileName
    /// \return
    ///
    int saveAsToFile(QString fileName);

    ///
    /// \brief isModified
    /// \details used to manage star* display in tab caption, and prevent exit without saving
    /// \return
    ///
    bool isModified();

    ///
    /// \brief setInitialContent
    /// \details used by isModified method
    /// \param s
    ///
    void setInitialContent(QString s);


};

#endif // MYPLAINTEXTEDIT_H
