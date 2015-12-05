#include <QApplication>
#include "GameWidget.hpp"
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QRect screen_size = QApplication::desktop()->screenGeometry();
    GameWidget game(screen_size.width(), screen_size.height());
    game.show();
    return app.exec();
}
