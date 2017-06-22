#ifndef TETRISVIEW_H
#define TETRISVIEW_H
#include "class_file.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QtWidgets>
#include <QDebug>
#include <QMessageBox>
#include <Feild.h>
#include <element.h>
#include <control.h>
class MainWindow : public QMainWindow //класс игрового окна
{
    Q_OBJECT
public:
    explicit MainWindow( QWidget* parent = 0 );//конструктор класса MainWindow
    ~MainWindow();//деструктор класса MainWindow
protected:
    void paintEvent( QPaintEvent* ); //функция отрисовки игрового поля
    void keyPressEvent( QKeyEvent* e );//метод, который вызывается при нажатии влавиши
    void keyReleaseEvent( QKeyEvent* e );//метод, вызывающийся при отпускании клавиши
    void drawBlock( int xPoints, int yPoints, int type, QPainter* painter ); //функция рисования блока
private:
    Field m_model; //объект класса  Field
    control* m_controller; //объект класса control
    int w; //размер игрового поля по ширине
    int h; //размер игрового поля по высоте
public slots:
    void New_game(); //слот, предназначенный для старта
    void Exit(); //слот, предназначенный для выхода из программы
    void Rules(); //слот, предназначенный для вывода правил игры
    void Records(); //слот, предназначеннй для вывода статистики
    void controll(); //слот, предназначеннй для вывода управления
};

#endif // TETRISVIEW_H
