#include "GameWidget.hpp"
#include <QFileDialog>
#include <QPainter>
#include <QDebug>

GameWidget::GameWidget(size_t screen_width, size_t screen_height, QWidget *parent)
    : QWidget(parent)
    , m_max_width(screen_width)
    , m_max_height(screen_height)
{
    OpenImage();
    //ResizeWindow();
    //setFixedSize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    setFixedSize(m_image->width(), m_image->height());
    m_game_logic = new GameLogic(width(), height());
}

GameWidget::~GameWidget()
{
    delete m_image;
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QImage scale_image = m_image->scaled(width(), height(), Qt::KeepAspectRatio);
    painter.drawImage(0, 0, scale_image);
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    qDebug() << e->pos().x() << " " << e->pos().y();
}

void GameWidget::OpenImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть изображение"), "/home", tr("Images (*.png *.jpeg *.jpg)"));
    m_image = new QImage(fileName);
}

void GameWidget::ResizeWindow()
{
    if (m_image->width() > m_max_width && m_image->height() > m_max_height)
    {
        float coef_w = m_image->width() * 1. / m_max_width;
        float coef_h = m_image->height() * 1. / m_max_height;
        setFixedSize(m_image->width() / (coef_w + 1), m_image->height() / (coef_h + 1));
    }
}

