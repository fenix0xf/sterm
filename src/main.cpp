#include <QApplication>
#include <ui_main.h>

int main(int argc, char* argv[])
{
    QApplication   app(argc, argv);
    QMainWindow    mainWindow{};
    Ui::MainWindow ui{};

    ui.setupUi(&mainWindow);
    mainWindow.show();
    return app.exec();
}
