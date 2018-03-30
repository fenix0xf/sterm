
#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char* argv[])
{
    QApplication app{argc, argv};
    MainWindow   mainWindow{};

    app.setQuitOnLastWindowClosed(true);

    mainWindow.show();
    return app.exec();
}
