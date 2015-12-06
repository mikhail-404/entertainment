#include "GameLogic.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>

/*
 *
 * В конструкторе создадим некоторую таблицу, в которой будем хранить
 * идентификаторы текстур для отображения определенных кусков входного
 * изображения. Можно, конечно, воспользоваться просто массивом,
 * но так проще, т.к. не надо пересчитывать смещение (делается просто:)).
 *
 */
GameLogic::GameLogic()
{
    std::vector <std::vector <uint8_t> > temp(cRows, std::vector <uint8_t>(cColumns));
    m_pics_id.swap(temp);

    Initialize();
}

/*
 * Деструктор ничего не делает, т.к. в данном классе используем все RAII
 * Вектор векторов сам разрушится.
 *
 */
GameLogic::~GameLogic()
{
}

/*
 * Произведем инициализацию матрицы индексов текстур. Просто заполним по порядку
 * и выозвем метод перемешивания элементов.
 */
void GameLogic::Initialize()
{
    //uint8_t counter = 0;
    for(size_t i = 0; i < cRows; ++i)
        for(size_t j = 0; j < cColumns; ++j)
            m_pics_id[i][j] = static_cast<uint8_t>(i * cColumns + j);
    ShuffleIndicies();
}

/*
 * ?
 */
void GameLogic::Click(float x, float y)
{
}

/*
 * Проверять на выполнение инварианта порядка в матрице будем просто -
 * аналогично заполнению.
 */
bool GameLogic::IsComplete() const
{
    for(size_t i = 0; i < cRows; ++i)
        for(size_t j = 0; j < cColumns; ++j)
            if (m_pics_id[i][j] != i * cColumns + j)
                return false;
    return true;
}

/*
 * ?
 */
void GameLogic::Render() const
{
}

/*
 * Перезапуск игры просто вызывает начальный метод инициализации
 * и все по-новой начинается.
 */
void GameLogic::Restart()
{
    Initialize();
}

/*
 * В логику решил добавить некоторый методв, который будет обменивать заданные
 * блоки местами.
 */
void GameLogic::SwapBlocks(size_t ai, size_t aj, size_t bi, size_t bj)
{
    if (ai >= cRows || aj >= cColumns || bi >= cRows || bj >= cColumns)
        return;
    std::swap(m_pics_id[ai][aj], m_pics_id[bi][bj]);
}

/*
 * Простой геттер. Возвращаем идентификатор текстуры по заданному адресу (i, j)
 */
uint8_t GameLogic::GetTextureId(size_t i, size_t j) const
{
    return m_pics_id[i][j];
}

/*
 * Перемешивание матрицы. Достаточно примитивный способ.
 * Проходим по всей матрице и берем случайные номера строк и столбцов
 * и меняем с текущим элементом.
 *
 * P.S. На маленьких количествах блоков (<=2) матрица может быть уже упорядочена
 */
void GameLogic::ShuffleIndicies()
{
    std::srand(std::time(0));
    for(size_t i = 0; i < cRows; ++i)
        for(size_t j = 0; j < cColumns; ++j)
        {
            uint8_t rand_i = std::rand() % cRows;
            uint8_t rand_j = std::rand() % (cColumns - 1) + std::rand() % 2;
            std::swap(m_pics_id[i][j], m_pics_id[rand_i][rand_j]);
        }
}
