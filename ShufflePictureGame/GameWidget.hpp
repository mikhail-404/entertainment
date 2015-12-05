#ifndef GAMEWIDGET_HPP
#define GAMEWIDGET_HPP

#include <QWidget>
#include <QImage>
#include <QMouseEvent>
#include "GameLogic.hpp"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(size_t screen_width = 640, size_t screen_height = 480, QWidget *parent = 0);
    ~GameWidget();

    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *e);

private:
    void OpenImage();
    void ResizeWindow();

private:
    size_t     m_max_width;
    size_t     m_max_height;

    GameLogic *m_game_logic;
    QImage    *m_image;

private:
    static constexpr size_t GAME_WINDOW_HEIGHT = 480;
    static constexpr size_t GAME_WINDOW_WIDTH  = 640;
};

#endif // GAMEWIDGET_HPP
