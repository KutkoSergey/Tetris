#ifndef ELEMENT
#define ELEMENT
#include "Feild.h"
#include <vector>
typedef std::vector< std::vector< int > > Matrix;
class element //класс игрового элемента
{
public:
    element( int xPoints = 0, int yPoints = 0 ); //конструктор класса element
    static element generateelement();//фунцция генерирования элемента
    bool isempty();//фунцкия проверки наличия игрового элемента
    void rotate(); //функция вращение элемента
    void setPosition( int xPoints, int yPoints ); //функция установки позиции элемента
    int getX();//фунцкия получения координаты Х
    int getY();//фунцкия получения координаты У
    int getSizeBlocks() const; //фунцкия возвращает размер матрицы элемента
    int getBlockType( int , int ) const; //фунцкия возвращает тип элемента
    int getBlockX( int ) const; //фунцкия получения координаты блока Х
    int getBlockY( int ) const; //фунцкия получения координаты блока Н
    explicit element( const Matrix& matrix ); //конструктор класса element
private:
    int x; //координата Х элемента
    int y; //координата У элемента
    Matrix m_matrix; //матрица игрового элемента
};
#endif // ELEMENT

