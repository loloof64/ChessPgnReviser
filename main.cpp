#include "gui/mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QDir>

#include <QMessageLogger>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator myappTranslator;
    QDir translationsDir;
    translationsDir.cd("translations");
    const auto path = translationsDir.absolutePath();

    auto success = myappTranslator.load(QLocale(), QString("ChessPgnReviser"), ".", QString(path));
    app.installTranslator(&myappTranslator);

    MainWindow w;
    w.show();
    return app.exec();
}
