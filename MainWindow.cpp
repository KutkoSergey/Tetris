#include "MainWindow.h"
#include "class_file.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMediaPlayer>
 const int PIXELS_POINT = 2;

int modelInPixels( int x )
{
    return x * PIXELS_POINT;
}

 const int BLOCK_SIZE_PIXELS = modelInPixels( BLOCK_SIZE ); //размер блока в пикселях
 const int HALF_BLOCK_SIZE_PIXELS = BLOCK_SIZE_PIXELS / 2;

 const QColor backgroundcolor = Qt::black;  //цвет фона
 const QColor gridcolor = Qt::gray; //цвет сетки

// ********************************************************************************
MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent )
{
    //переменной w присваивается значение длины окна в пикселях
    w =  modelInPixels( m_model.getlengthPoints() );
    //переменной р присваивается значение высоты окна в пикселях
    h =  modelInPixels( m_model.getHeightPoints() );
    //создание звукового оформления
    QMediaPlayer* pPlayer=new QMediaPlayer;
    pPlayer->setMedia(QUrl::fromLocalFile("D:/dendi.mp3"));
    pPlayer->play();
    //указателя для создания меню
    QMenuBar *menu=new QMenuBar;
    QMenu* pnmu = new QMenu("&Menu");
    //добавление всплывающих меню
    pnmu->addAction("&Start_game",this,  SLOT(New_game()), Qt::CTRL + Qt::Key_S);
    pnmu->addAction("&Exit_game",this,  SLOT(Exit()), Qt::CTRL + Qt::Key_Q);
    pnmu->addAction("&Rules",this,  SLOT(Rules()), Qt::CTRL + Qt::Key_R);
    pnmu->addAction("&Records",this,  SLOT(Records()), Qt::CTRL + Qt::Key_T);
    pnmu->addAction("&Controll",this,  SLOT(controll()), Qt::CTRL + Qt::Key_C);
    pnmu->addSeparator();
    menu->addMenu(pnmu);
    setMenuBar(menu);
    m_controller = new control( &m_model, this, this );
    resize( w, h ); //размер окна
}

MainWindow::~MainWindow()
{
}
void MainWindow::paintEvent( QPaintEvent* )
{
    QPainter painter( this );   //указатель для рисования
    painter.fillRect( 0, 0, w, h, backgroundcolor );    //очистка поля
    painter.setPen( gridcolor );    //установка цвета пера на серый
    //рисование сетки
    for( int x = BLOCK_SIZE_PIXELS; x < w; x += BLOCK_SIZE_PIXELS )
    {
        painter.drawLine( x, 0, x, h );
    }
    for( int y = BLOCK_SIZE_PIXELS; y < h; y += BLOCK_SIZE_PIXELS )
    {
        painter.drawLine( 0, y, w, y );
    }
    //рисование поля матрицы
    for( int x = 0; x < m_model.getlengthBlocks(); ++x )
    {
        for( int y = 0; y < m_model.getHeightBlocks(); ++y )
        {
            drawBlock( blocksToPoints( x ) + HALF_BLOCK_SIZE, blocksToPoints( y ) + HALF_BLOCK_SIZE, m_model.getBlockType( x, y ), &painter );
        }
    }
    //рисование активного игрового элемента
    const element& item = m_model.getItem();
    for( int x = 0; x < item.getSizeBlocks(); ++x )
    {
        for( int y = 0; y < item.getSizeBlocks(); ++y )
        {
            drawBlock( item.getBlockX( x ), item.getBlockY( y ), item.getBlockType( x, y ), &painter );
        }
    }
}

void MainWindow::keyPressEvent( QKeyEvent* e )
{
    switch( e->key() )
    {
    case Qt::Key_Left:  //нажатие клавишы Left
        m_controller->MoveLeft();   //вызов слота для перемещения элементы влево
        break;
    case Qt::Key_Right: //нажатие клавишы Right
        m_controller->MoveRight();  //вызов слота для перемещения элементы вправо
        break;
    case Qt::Key_Up:    //нажатие клавишы Up
        m_controller->Rotate(); //вызов слота для перемещения элементы вправо
        break;
    case Qt::Key_Down:  //нажатие клавишы Down
        m_controller->DropEnabled( true );  //вызов слота для перемещения ускорения падения
        break;
    case Qt::Key_Space: //нажатие клавишы Space
        m_controller->onTogglePause();  //вызов слота для включения\выключения паузы
        break;
    default:
        QWidget::keyPressEvent( e );
    }
}

void MainWindow::keyReleaseEvent( QKeyEvent* e )
{
    switch( e->key() )
    {
    case Qt::Key_Down:  //нажатие клавишы Down
        m_controller->DropEnabled( false );
        break;
    default:
        QWidget::keyReleaseEvent( e );
    }
}

void MainWindow::drawBlock( int xP, int yP, int type , QPainter* painter )
{
    //вектор для хранения цветов
    const std::vector< QColor > COLOR_TABLE =
    {
        Qt::white,
        Qt::yellow,
        Qt::green,
        Qt::red,
        Qt::cyan,
        Qt::magenta,
        Qt::lightGray
    };
    if( type <= 0 || COLOR_TABLE.size() < type )
    {
        return;
    }
    //координаты центра блока
    int x = modelInPixels( xP ) - HALF_BLOCK_SIZE_PIXELS;
    int y = modelInPixels( yP ) - HALF_BLOCK_SIZE_PIXELS;
    //рисование блока
    painter->fillRect( x, y, BLOCK_SIZE_PIXELS, BLOCK_SIZE_PIXELS, COLOR_TABLE[ type - 1 ] );
}
void MainWindow::New_game()
{
     m_controller->Start();
}
void MainWindow::Exit()
{
     QApplication::quit();
}
void MainWindow::Rules()
{
    QString str;    //строка для вывода
    cl_file f("rules.txt");
    str=f.read_QString();   //присваивание правил игры строке str
    //вывод окна с правилами игры
    QMessageBox msg(this);
    msg.setText("Rules");
    msg.setInformativeText(str);
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setDefaultButton(QMessageBox::Ok);
    msg.exec();
}
void MainWindow::controll()
{
    QString str;     //строка для вывода
    cl_file f("controll.txt");
    str=f.read_QString();   //присваивание управления игры строке str
    //вывод окна с управлением игры
    QMessageBox msg(this);
    msg.setText("controll");
    msg.setInformativeText(str);
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setDefaultButton(QMessageBox::Ok);
    msg.exec();
}
void MainWindow::Records()
{
    QString str;    //строка для вывода
    cl_file f("statss.txt");
    str=f.read_QString();   //присваивание статистики строке str
    QMessageBox msg(this);
    //вывод окна статистики
    msg.setText("Records");
    msg.setInformativeText(str);
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setDefaultButton(QMessageBox::Ok);
    msg.exec();
}
