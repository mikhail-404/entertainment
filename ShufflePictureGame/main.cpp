#include <QApplication>
#include "GameWidget.hpp"
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // получаем характеристики экрана
    QRect screen_size = QApplication::desktop()->screenGeometry();
    // передаем эти характеристики в виджет с игрой
    GameWidget game(screen_size.width(), screen_size.height());
    // отображаем виджет по центру
    game.move(QApplication::desktop()->screen()->rect().center()-game.rect().center());
    // запускаем
    game.show();

    return app.exec();
}
