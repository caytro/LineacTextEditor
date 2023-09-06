#include "mainwindow.h"



#include <QApplication>

//permet d'utiliser des une QList<QString> dans mySettings
Q_DECLARE_METATYPE(QList<QString>)

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w(nullptr, &a);

    w.show();
    return a.exec();
}
