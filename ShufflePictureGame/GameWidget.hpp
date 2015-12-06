#ifndef GAMEWIDGET_HPP
#define GAMEWIDGET_HPP

#include <QWidget>
#include <QImage>
#include <QQueue>
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

signals:
    void complete_pic();
    void starting_game();

public slots:
    void gameStart();
    void gameFinish();

private:
    void OpenImage();
    void ResizeWindow();
    void InitializeSettings();

private:
    size_t     m_max_width;
    size_t     m_max_height;
    GameLogic *m_game_logic;
    QImage    *m_image;

    // для запрета кликов
    bool       m_game_is_finished;

    QQueue <QPair<size_t, size_t>> m_click_coords;

private:
    static constexpr size_t GAME_WINDOW_HEIGHT = 480;
    static constexpr size_t GAME_WINDOW_WIDTH  = 640;
};

#endif // GAMEWIDGET_HPP
