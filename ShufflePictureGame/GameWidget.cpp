#include "GameWidget.hpp"
#include <QFileDialog>
#include <QPainter>
#include <QDebug>

GameWidget::GameWidget(size_t screen_width, size_t screen_height, QWidget *parent)
    : QWidget(parent)
    , m_max_width(screen_width)
    , m_max_height(screen_height)
    , m_game_logic(new GameLogic())
    , m_image(nullptr)
    , m_game_is_finished(false)
{
    setWindowTitle("Перемешанная картинка");

    InitializeSettings();

    // связываем сигнал начала игры со слотом gameStart()
    // для инициализации необходимых данных
    connect(this, SIGNAL(starting_game()), SLOT(gameStart()));

    // связываем сигнал завершения игры со слотом hameFinish()
    // для обработки случая завершения
    connect(this, SIGNAL(complete_pic()), SLOT(gameFinish()));
}

GameWidget::~GameWidget()
{
    delete m_image;
}

void GameWidget::paintEvent(QPaintEvent *)
{
    if (m_image == nullptr)
        return;

    // передаем объект для рисования
    QPainter painter(this);

    // вычисляем размеры блока
    size_t w = width() / m_game_logic->cColumns;
    size_t h = height() / m_game_logic->cRows;

    // создаем новое изображение для нарезки
    QImage temp_image = m_image->scaled(width(), height(), Qt::KeepAspectRatio);
    // проходим по всем блокам изображения (перемешанного)
    for(size_t i = 0; i < m_game_logic->cRows; ++i)
        for(size_t j = 0; j < m_game_logic->cColumns; ++j)
        {
            // получаем текущую текстуру, которая находится по адресу (i, j)
            uint8_t texture_id = m_game_logic->GetTextureId(i, j);

            // вычисляем координаты начала блока на изображении
            size_t p = (texture_id / m_game_logic->cColumns) * height() / m_game_logic->cRows;
            size_t q = (texture_id % m_game_logic->cColumns) * width() / m_game_logic->cColumns;

            // вычисляем координаты на форме, куда будем рисовать определенную часть изображния
            size_t x = i * height() / m_game_logic->cRows;
            size_t y = j * width() / m_game_logic->cColumns;

            QRect rect(q, p, w, h);
            // выделяем нужную область на изображении
            QImage cropped = temp_image.copy(rect);
            // отображаем ее на форме
            painter.drawImage(y, x, cropped);
        }

    // если игра была завершена, то выведем сообщение
    if (m_game_is_finished)
    {
        QFont font = painter.font();
        font.setPointSize(width() * 0.0625);
        painter.setFont(font);
        painter.setPen(Qt::white);
        painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, "Задание выполнено!");
    }
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    // если была нажата правая кнопка мыши
    if (e->button() == Qt::RightButton)
    {
        // сигнализируем о начале новой игры
        emit starting_game();
    }

    // если игра была завершена, то игнорируем нажатия левой кнопки мыши
    if (m_game_is_finished)
        return;

    // рассчитываем размеры блоков
    int w = width() / m_game_logic->cColumns;
    int h = height() / m_game_logic->cRows;

    // получаем координаты выбранного блока
    size_t i_block = e->pos().y() / h;
    size_t j_block = e->pos().x() / w;

    // кладем в очередь
    m_click_coords.push_back(qMakePair(i_block, j_block));

    // как только в очереди накапливается больше одного элемента,
    // то это означает, что можно обменивать местами блоки
    if (m_click_coords.size() > 1)
    {
        // вытаскиваем координаты из очереди
        auto a = m_click_coords.takeFirst();
        auto b = m_click_coords.takeLast();
        // очищаем очередь
        m_click_coords.clear();
        // меняем полученный блоки местами в матрице
        m_game_logic->SwapBlocks(a.first, a.second, b.first, b.second);
        // обновляем содержимое мозаики на форме
        update();

        // если проверка окончания игры дала положительный результат
        if (m_game_logic->IsComplete())
        {
            // сигализируем об этом
            emit complete_pic();
        }
    }
}

void GameWidget::gameStart()
{
    InitializeSettings();
    // перезапускаем игру
    m_game_logic->Restart();
}

void GameWidget::gameFinish()
{
    m_game_is_finished = true;
    update();
}

void GameWidget::OpenImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть изображение"), "", tr("Images (*.png *.jpeg *.jpg)"));

    if (!fileName.isEmpty())
    {
        // если память под объект была выделена, то просто перезагружаем содержимое
        if (m_image != nullptr)
            m_image->load(fileName);
        else
            m_image = new QImage(fileName);
    }
}

void GameWidget::ResizeWindow()
{
    if (m_image == nullptr)
    {
        setFixedSize(GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
    }
    // если размер входного изображения больше размера экрана,
    // P.S. static_cast <int> чтобы валидно сравнивать (no warnings)
    else if (m_image->width() > static_cast<int>(m_max_width) || m_image->height() > static_cast<int>(m_max_height))
    {
        // расчитываем максимальынй коэффициент, на который надо разделить каждую из составляющих размера
        // чтобы входное изображение на форме поместилось на экране
        float coef = qMax(m_image->width() * 1. / m_max_width, m_image->height() * 1. / m_max_height);

        // фиксируем размер виджета
        setFixedSize(m_image->width() * 1. / coef, m_image->height() * 1. / coef);
    }
    // если поместилось, то просто фиксируем входные размеры
    else
    {
        setFixedSize(m_image->width(), m_image->height());
    }
}

void GameWidget::InitializeSettings()
{
    // открываем изображение
    OpenImage();
    // изменяем размеры формы в зависимости от входного изображения
    ResizeWindow();
    // сбрасываем флаг завершения игры
    m_game_is_finished = false;
    // очищаем очередь (вдруг, в ней что-то уже было)
    m_click_coords.clear();
    // перерисовываем форму
    update();
}
