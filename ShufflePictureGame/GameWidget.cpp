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
    //QImage scale_image = m_image->scaled(width(), height(), Qt::KeepAspectRatio);
    //painter.drawImage(0, 0, scale_image);
    size_t w = width() / m_game_logic->cColumns;
    size_t h = height() / m_game_logic->cRows;

    qDebug() << "W: " << m_game_logic->cColumns << " H: " << m_game_logic->cRows;

    QImage temp_image = m_image->scaled(width(), height(), Qt::KeepAspectRatio);
    for(size_t i = 0; i < m_game_logic->cRows; ++i)
        for(size_t j = 0; j < m_game_logic->cColumns; ++j)
        {
            uint8_t texture_id = m_game_logic->GetTextureId(i, j);
            size_t p, q;
            p = (texture_id / m_game_logic->cColumns) * height() / m_game_logic->cRows;
            q = (texture_id % m_game_logic->cColumns) * width() / m_game_logic->cColumns;

            size_t x, y;
            x = i * height() / m_game_logic->cRows;
            y = j * width() / m_game_logic->cColumns;

            qDebug() << p << " " << q << " " << x << " " << y;

            QRect rect(q, p, w, h);
            QImage cropped = temp_image.copy(rect);
            painter.drawImage(y, x, cropped);
        }
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

