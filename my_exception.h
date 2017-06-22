#ifndef ME_EXCEPTION
#define ME_EXCEPTION
#include <QMessageBox>
#include <QInputDialog>
#include <QString>
#include "control.h"
#include <iostream>
using namespace std;
class my_exception //класс для работы с исключениями
{
protected:
    int code;   //код ошибки
    char str_error[50]; //причина ошибки
public:
    my_exception() {}   //конструктор
    virtual ~my_exception() {}  //детруктор
};
class file_exception : public my_exception //класс для исключения с файлами
{
public:
    file_exception()    //конструктор
    {
    }
    file_exception(int c, char *s); //конструктор с параметрами
    void show();    //вывод сообщения ошибки
};
class record_exception:public my_exception  //класс для исключений со строкой
{
public:
    record_exception()  //конструктор
    {
    }
     record_exception(int c, char *s);  //конструктор с параметрами
     void show();   //вывод сообщения ошибки
};
QString  input_record();    //функция проверки ввода строки
#endif // ME_EXCEPTION

