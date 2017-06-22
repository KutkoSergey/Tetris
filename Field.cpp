#include "Feild.h"
#include <class_file.h>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <numeric>
int blocksToPoints( int x )
{
    return x * BLOCK_SIZE;
}

// ********************************************************************************
Field::Field() : m_dropEnabled( false )
{
    cl_file f("data.txt");
    int *ms;
    ms=new int[6];
    ms=f.read_fiedl();
    //инициализвация данных
    length=ms[0];
    height=ms[1];
    maximum_speed = ms[2];
    minimum_speed = ms[3];
    maximum_contact=ms[4];
    score_for_level=ms[5];
    restartGame();  //фукнция рестарта игры
}

const element& Field::getItem()
{
    return m_activeItem;    //возвращает матрицу активного игрового элемента
}

void Field::doStep()
{
    if( m_activeItem.isempty() )    //если активного элемента нету
    {
        contact = 0;    //обнуляется счетчик касаний
        m_activeItem = element::generateelement();  //генерируется новый элемент
        int xPoints = blocksToPoints( getlengthBlocks() / 2 );
        // Если элемент состоит из нечетного числа блоков, то выравнивается по сетке
        if( m_activeItem.getSizeBlocks() % 2 == 1 )
        {
            xPoints += HALF_BLOCK_SIZE;
        }
        m_activeItem.setPosition( xPoints, 0 ); //установка позиции на начальную
        if( Collisions( m_activeItem ) )
        {
            m_gameOver = true;
        }
    }
    //если конец игры, то выходит из функции
    if( isGameOver() )
    {
        return;
    }
    int speed = m_dropEnabled ? maximum_speed : m_speed;    //инициализация скорости
    //инициализация текущего игрового элемента
    element item = m_activeItem;
    //устанавливает позицию элемента в поле
    item.setPosition( m_activeItem.getX(), m_activeItem.getY() + speed );
    if( !Collisions( item ) )
    {
        m_activeItem = item;
        // Если столкновений нет, то сбрасываем счетчик касаний
        contact = 0;
    } else
    {
        while( Collisions( item ) )
        {
            item.setPosition( item.getX(), item.getY() - 1 );
        }

        if( maximum_contact < contact )
        {
             // Если количество касаний превысило предел, то элемент фиксируется
            m_activeItem = element();
            //фиксация каждого блока элемента
            for( int xBlocks = 0; xBlocks < item.getSizeBlocks(); ++xBlocks ) {
                for( int yBlocks = 0; yBlocks < item.getSizeBlocks(); ++yBlocks ) {
                    int blockType = item.getBlockType( xBlocks, yBlocks );
                    if( blockType != 0 )    //если блок не пустой
                    {
                        int xPoints = item.getBlockX( xBlocks );    //получение координаты Х
                        int yPoints = item.getBlockY( yBlocks );    //получение координаты Y
                        // Фиксация  тип блока в ячейке матрицы игрового поля
                        fieldMatrix[ yPoints / BLOCK_SIZE ][  xPoints / BLOCK_SIZE ] = blockType;
                    }
                }
            }
            clean();    //функция очистки заполненных строк
        }\
        //если нет, то счетчик касаний увеличивается
        else
        {
            m_activeItem = item;
            ++contact;
        }
    }
}

bool Field::isGameOver()
{
    return m_gameOver;
}

int Field::getScore()
{
    return m_score;
}

void Field::restartGame()
{
    m_activeItem = element();

    fieldMatrix.clear();    //удаление всех элементов из вектора
    fieldMatrix.resize( getHeightBlocks() );    //установка размера матрицы по высоте
    //установка размера матрицы по длине
    for(std::vector< int >& row : fieldMatrix)
    {
        row.resize( getlengthBlocks() );
    }
    m_speed = minimum_speed;       //установка скорости на минимальную
    m_score = 0;    //обнуление счета
    m_gameOver = false; //установка переменной конца игры на false
}

void Field::rotateItem()
{
    element item = m_activeItem;    //дополнительная переменная элемента
    item.rotate();  //функция вращения элемента
    if( !Collisions( item ) )   //если нету столкновения
    {
         //игровому элементу присваивается элемент после вращения
        m_activeItem = item;
        return;
    }
}

void Field::moveelementLeft()
{
    moveItemX( -BLOCK_SIZE );
}

void Field::moveelementRight()
{
    moveItemX( BLOCK_SIZE );
}

void Field::moveItemX( int offsetPoints )
{
    element item = m_activeItem;   //дополнительная переменная элемента
    //устанавливает позицию игрового элемента левее/правее
    item.setPosition( item.getX() + offsetPoints, item.getY() );
    if( !Collisions( item ) )    //если нету столкновения
    {
        //игровому элементу присваивается элемент после движения
        m_activeItem = item;
    }
}

void Field::startDrop()
{
    m_dropEnabled = true;   //счетчик скорости на true
}

void Field::stopDrop()
{
    m_dropEnabled = false;  //счетчик скорости на false
}

int Field::getlengthBlocks()
{
    return length;
}

int Field::getHeightBlocks()
{
    return height;
}

int Field::getlengthPoints()
{
    return blocksToPoints( getlengthBlocks() );
}

int Field::getHeightPoints()
{
    return blocksToPoints( getHeightBlocks() );
}

int Field::getBlockType( int xBlocks, int yBlocks )
{
    const int BORDER_BLOCK_TYPE = -1;   //переменная, обозначающая позиция за полем
    if( xBlocks < 0 || getlengthBlocks() <= xBlocks || getHeightBlocks() <= yBlocks )
    {
        return BORDER_BLOCK_TYPE;
    }
    else
        if( yBlocks < 0 )
        {
            return 0;
        }
    return fieldMatrix[ yBlocks ][ xBlocks ]; //возврат значения элемента матрицы поля
}

bool Field::Collisions( const element& item )
{
    for( int xBlocks = 0; xBlocks < item.getSizeBlocks(); ++xBlocks )
    {
        for( int yBlocks = 0; yBlocks < item.getSizeBlocks(); ++yBlocks )
        {
            //если значения блока не -1 и есть столкновение с другим блоков
            if(item.getBlockType(xBlocks, yBlocks) > 0 && Collisions(item.getBlockX(xBlocks), item.getBlockY(yBlocks)))
            {
                return true;    //возвращает true
            }
        }
    }
    return false;
}

bool Field::Collisions( int xPoints, int yPoints )
{
    int xBlocks = ( xPoints < 0 ) ? -1 : xPoints / BLOCK_SIZE;  //координата игрового поля Х
    int yTopPoints = yPoints - HALF_BLOCK_SIZE;     //координата игрового поля У верхней границы
    if( getBlockType( xBlocks, yTopPoints / BLOCK_SIZE ) )  //если блок занят, то есть столкновение
    {
        return true;
    }
    int yBottomPoints = yPoints + HALF_BLOCK_SIZE; //координата игрового поля У нижней границы
    if( yTopPoints % BLOCK_SIZE != 0 && getBlockType( xBlocks, yBottomPoints / BLOCK_SIZE ) )
    {
        return true;
    }

    return false;
}

void Field::clean()
{
    for( int i = height - 1; i >= 0; --i )
    {
        // Для каждого ряда начиная с последнего
                // Считаем количество заполненных блоков
        int counter = std::accumulate(
            fieldMatrix[ i ].begin(),
            fieldMatrix[ i ].end(),
            0,
            []( int a, int b ) { return ( b == 0 ) ? a : a + 1; }
        );

        if( counter == 0 )
        {
            // Если все блоки пустые, то выше идти смысла нет
            return;
        }
        else
            if( counter == getlengthBlocks() )
        {
            // Иначе если все блоки заполнены, то удаляется строка
            fieldMatrix.erase(fieldMatrix.begin() + i );
            std::vector< int > v( getlengthBlocks() );
            fieldMatrix.insert(fieldMatrix.begin(), v );
            // А еще наращиваем количество набранных очков
            incScore();
            ++i;
        }
    }
}

void Field::incScore()
{
    ++m_score;  //увеличение счета
    if( m_score % score_for_level == 0 )
    {
        incSpeed(); //функция увеличения скорости
    }
}

void Field::incSpeed()
{
    if( m_speed < maximum_speed )   //если скорость не максимальная
    {
        ++m_speed;   //увеличивается скорость
    }
}
