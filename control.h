#ifndef TETRISCONTROLLER_H
#define TETRISCONTROLLER_H

#include <QObject>
#include <QTimer>
class MainWindow;
class Field;
class control:  QObject //класс управления и визуализации
{
    Q_OBJECT

public:
    control(Field *model, MainWindow *view, QObject* parent = 0 );//конструктор класса control

public slots:
    void Start(); //слот для начала игры
    void Pause();//слот для паузы
    void Resume();//слот для продолжения
    void onStep();//обновления состояния игры
    void MoveLeft();//слот для движения элемента влево
    void MoveRight();//слот для движения элемента вправо
    void Rotate(); //слот для вращения элемента
    void DropEnabled( bool enabled );//слот для ускорения падения элемента
    void onTogglePause(); //слот для включения паузы/рестарта
private:
    void onAction( void ( Field::*action )() );//обработка игровых действий

private:
    Field* m_model; // переменная игрового поля
    MainWindow* m_view; // переменная визуализации игрового поля
    QTimer m_timer; // переменная таймера
    int STEP_TIME_INTERVAL; //интервал таймера
};

#endif // TETRISCONTROLLER_H
