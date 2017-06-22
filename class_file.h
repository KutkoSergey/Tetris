#ifndef CLASS_FILE
#define CLASS_FILE
#include <iostream>
#include <fstream>
#include <cstring>
#include <QTextStream>
#include <QFile>
#include "my_exception.h"
using namespace std;
class cl_file   //класс для работы с файлами
{
private:
    char name_file[100];    //имя файла
    ifstream in;    //переменная потока ввода
    ofstream out;   //переменная потока вывода
public:
    cl_file()
    {
    }
    cl_file(char *s);   //конструктор с параметрами
    int*  read_fiedl();  //считывание данные игрового поля
    int  read_timer();  //считывание данных таймера
    void write(QString str, char *score);   //запись статистики в файл
    QString read_QString(); //считывание строковых данных
};

#endif // CLASS_FILE*/

