#include "Feild.h"
#include <class_file.h>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <QMediaPlayer>
#include <element.h>
element::element( int xPoints, int yPoints ) : x( xPoints ), y( yPoints )
{

}
element element::generateelement()
{
    //вид игровых элементов
    static const std::vector< element > ITEMS = {
        element( {
            { 1, 1 },
            { 1, 1 },
        } ),
        element( {
            { 0, 2, 0, 0 },
            { 0, 2, 0, 0 },
            { 0, 2, 0, 0 },
            { 0, 2, 0, 0 },
        } ),
        element( {
            { 0, 3, 0 },
            { 0, 3, 0 },
            { 0, 3, 3 },
        } ),
        element( {
            { 0, 4, 0 },
            { 0, 4, 0 },
            { 4, 4, 0 },
        } ),
        element( {
            { 0, 5, 0 },
            { 5, 5, 5 },
            { 0, 0, 0 },
        } ),
        element( {
            { 6, 6, 0 },
            { 0, 6, 6 },
            { 0, 0, 0 },
        } ),
        element( {
            { 0, 7, 7 },
            { 7, 7, 0 },
            { 0, 0, 0 },
        } )
    };
    int type = rand() % ITEMS.size();   //генерирует случайным образом тип элемента
    return ITEMS[ type ];               //возвращает тип
}

bool element::isempty()
{
    return m_matrix.empty();    //если матрица пуска, возвращает true
}

void element::rotate()
{
    Matrix rotatedMatrix( getSizeBlocks() );
    //алгоритм вращения
    for( int i = 0; i < getSizeBlocks(); ++i )
    {
        rotatedMatrix[ i ].resize( getSizeBlocks() );
        for( int j = 0; j < getSizeBlocks(); ++j )
        {
            rotatedMatrix[ i ][ j ] = m_matrix[ j ][ getSizeBlocks() - 1 - i ];
        }
    }

    m_matrix = rotatedMatrix;
}

void element::setPosition( int xPoints, int yPoints )
{
    x = xPoints;
    y = yPoints;
}

int element::getX()
{
    return x;
}

int element::getY()
{
    return y;
}

int element::getSizeBlocks() const
{
    return m_matrix.size();     //возвращает размер вектора
}

int element::getBlockType( int innerXBlocks, int innerYBlocks ) const
{
    if( innerXBlocks < 0 || getSizeBlocks() <= innerXBlocks || innerYBlocks < 0 || getSizeBlocks() <= innerYBlocks )
    {
        return 0;
    }

    return m_matrix[ innerYBlocks ][ innerXBlocks ];
}

int element::getBlockX( int innerXBlocks ) const
{
    int innerXPoints = blocksToPoints( innerXBlocks ) + HALF_BLOCK_SIZE;
    int innerXCenterPoints = blocksToPoints( getSizeBlocks() ) / 2;
    return x - innerXCenterPoints + innerXPoints;
}

int element::getBlockY( int innerYBlocks ) const
{
    int innerYPoints = blocksToPoints( innerYBlocks ) + HALF_BLOCK_SIZE;
    int innerYCenterPoints = blocksToPoints( getSizeBlocks() ) / 2;
    return y - innerYCenterPoints + innerYPoints;
}

element::element( const Matrix& matrix )
{
    m_matrix = matrix;
}

