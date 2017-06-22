#ifndef TETRISMODEL_H
#define TETRISMODEL_H
#include "element.h"
#include <vector>
typedef std::vector< std::vector< int > > Matrix;
const int BLOCK_SIZE = 12;//размер блока
const int HALF_BLOCK_SIZE = BLOCK_SIZE / 2;//размер половины блока
int blocksToPoints( int x ); //фунцкия возвращает x*(размер блока)
class Field //клас игрового поля
{
public:
    Field(); //конструктор класса Field
    void doStep(); //функция обновление состояния игрового поля
    bool isGameOver(); //функция проверки на конец игры
    int getScore(); //функция получения счёта
    void restartGame(); //фунцкия рестарта
    const element& getItem(); //функция получения элемента
    void rotateItem(); //фукция вращения элемента
    void moveelementLeft(); //функция перемещения элемента влево
    void moveelementRight(); //функция перемещения элемента вправо
    void startDrop(); //функция устанавливает счетчик при увеличении скорости на true
    void stopDrop(); //функция устанавливает счетчик при увеличении скорости
    int getlengthBlocks(); //функция возвращает размер матрицы игрового поля по длине
    int getHeightBlocks(); //функция возвращает размер матрицы игрового поля по высоте
    int getlengthPoints(); //функция  возвращает размер игрового поля по длине
    int getHeightPoints(); // функция возвращает размер игрового поля по высоте
    int getBlockType( int xBlocks, int yBlocks ); //функция возвращает элемент игрового поля
    void moveItemX( int offsetPoints ); //функция перемещает активный элемент на блок
    bool Collisions( const element& item ) ; //функция проверки на столкновения элемента
    bool Collisions( int xPoints, int yPoints ) ; //функция проверки на столкновения блока
    void clean();//функция очистки последней строки поля
    void incScore(); //функция увеличения счета
    void incSpeed(); //функция увеличения скорости падения
private:
    int length; //количество столбцов  матрицы игрового поля по длине
    int height; //количество строк матрицы игрового поля по длине
    Matrix fieldMatrix; //матрица игрового поля
    int minimum_speed; //минимальная скорость
    int m_score; //счёт
    int m_speed; //скорость
    int maximum_speed; //максимальная скорость
    int score_for_level; //счёт для повышения уровня сложность
    bool m_dropEnabled; //счётчик, обозначающий увеличение скорости
    int maximum_contact ; //максимальное количество касания для фиксации элемента
    int contact; //количество касаний для фиксации
    element m_activeItem; //активный игровой элемент
    bool m_gameOver; //счётчик конца игры
};

#endif // TETRISMODEL_H
