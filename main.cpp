#include "gui/mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QLibraryInfo>
#include <QDir>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/fonts/FreeSerif.ttf");

    QTranslator myappTranslator;
    QDir rootPath = QDir(QCoreApplication::applicationDirPath());

    if (myappTranslator.load(QLocale(), QLatin1String("ChessPgnReviser"), QLatin1String("."), QLatin1String(":/translations")))
            QCoreApplication::installTranslator(&myappTranslator);

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
