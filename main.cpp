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
    QDir translationsDir;
    const auto path = translationsDir.absolutePath();

    myappTranslator.load(QLocale(), QString("ChessPgnReviser"), ".", QString(path));
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
