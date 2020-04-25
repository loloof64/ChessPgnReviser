#include "gui/mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QLibraryInfo>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator myappTranslator;
    QDir rootPath = QDir(QCoreApplication::applicationDirPath());

    myappTranslator.load(QLocale(), QString("ChessPgnReviser"), ".", rootPath.relativeFilePath("../share/translations"));
    app.installTranslator(&myappTranslator);

    QTranslator qtTranslator;
    qtTranslator.load(QLocale::system(),
                    "qt", "_",
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QTranslator qtBaseTranslator;
    qtBaseTranslator.load("qtbase_" + QLocale::system().name(),
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtBaseTranslator);

    MainWindow w;
    w.show();
    return app.exec();
}
