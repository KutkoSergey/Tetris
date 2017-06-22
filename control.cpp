#include "control.h"
#include "Feild.h"
#include "MainWindow.h"
#include "class_file.h"
#include <QDebug>
#include <QMessageBox>
//#include "my_exception.h"
control::control( Field* model , MainWindow* view, QObject* parent ) :
    QObject( parent ), m_model( model ), m_view( view )
{
    cl_file f("timer.txt");
    STEP_TIME_INTERVAL=f.read_timer();  //присваивание значения
    connect( &m_timer, SIGNAL( timeout() ), SLOT( onStep() ) ); //
}

void control::Start()
{
    m_model->restartGame(); //вызов функции рестарта
    Resume();   //вызов функции возобновления таймера
}
void control::onStep()
{
    m_model->doStep();  //выполняет обновление состояния игры
    m_view->repaint();  //перерисовывает игровое поле
   char str_score[16];
   itoa(m_model->getScore(), str_score, 16);
    if( m_model->isGameOver() )     //условие на конец игры
    {
        QMessageBox::information(0,"score",str_score);  //вывод счета
        //запись имени игрока в файл
        QString str;
        str=input_record();
        cl_file f("statss");
        f.write(str, str_score);
        m_model->restartGame(); //вызов функции рестарта
    }
}
void control::Pause()
{
    m_timer.stop(); //останавливается таймер
}

void control::Resume()
{
    m_timer.start( STEP_TIME_INTERVAL ); //возобновляется таймер
}

void control::MoveLeft()
{
    onAction( &Field::moveelementLeft );    //вызов действия для смещения элемента влево
}

void control::MoveRight()
{
    onAction( &Field::moveelementRight );   //вызов действия для смещения элемента вправо
}

void control::Rotate()
{
    onAction( &Field::rotateItem );     //вызов действия для вращения элемента
}

void control::DropEnabled( bool enabled )
{
    onAction( enabled ? &Field::startDrop : &Field::stopDrop );//вызов действия для увеличения скорости
}

void control::onTogglePause()
{
    m_timer.isActive() ? Pause() : Resume();    //вызов действия для включения\выключения паузы
}

void control::onAction( void ( Field::*action )() )
{
    if( !m_timer.isActive() )
    {
        return;
    }
    (m_model->*action)();   //обработка игровых действий
    m_view->repaint();      //перерисовывает поле
}

