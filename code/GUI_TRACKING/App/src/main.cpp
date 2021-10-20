#include "itemlist.h"
#include "mainwindow.h"
#include "mainmenu.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainMenu menu;
    menu.show();

    return app.exec();
}
