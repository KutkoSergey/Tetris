#include "class_file.h"
#include <QString>
cl_file::cl_file(char *s)
{
    strcpy(name_file, s);
}
int*  cl_file::read_fiedl()
{
    //инициализация переменных
    int i=0;
    int ms[6];
    char name[100];
    strcpy(name,"D:/QtProjects/kursach/" );
    strcat(name, name_file);
    //открытие файла
    try
    {
       in.open(name);
       if(!in)
           throw file_exception(1, "ERROR in open file");
    }
    catch(file_exception &e)
    {
        e.show();   //сообщение об ошибке
    }
    //считывание данных
    while(!in.eof())
    {
        in >>  ms[i];
        i++;
    }

    in.close(); //закрытие файла
    return ms;

}
int cl_file::read_timer()
{
    //инициализация переменных
    int t;
    char name[100];
    strcpy(name,"D:/QtProjects/kursach/" );
    strcat(name, name_file);
    //открытие файла
    try
    {
       in.open(name);
       if(!in)
           throw file_exception(1, "ERROR in open file");
    }
    catch(file_exception &e)
    {
        e.show();
    }
    in >> t;    //считывание переменной
    in.close(); //закрытие файла
    return t;

}
void cl_file::write(QString str, char *score)
{
    char name[100];
    strcpy(name,"D:/" );
    strcat(name, name_file);
    QFile  *f=new QFile("D:/QtProjects/kursach/statss.txt"); //создание указателя QFile
        if(f->open(QIODevice::Append |QIODevice:: Text))    //открытие файла
        {
            QTextStream qtx(f); //переменная потока QTextStream
            //запись в файл данных
            qtx<<str;
            qtx<<"\t";
            qtx<<score;
            qtx<<"\n";
        }
      f->close();   //закрытие файла
}
QString cl_file::read_QString()
{
    //инициализация строки, обозначающей путь к  файлу
    char name[100];
    strcpy(name,"D:/QtProjects/kursach/" );
    strcat(name, name_file);
    QString str;    //строка QString, куда считаются данные
    QFile  *f=new QFile(name);  //создание указателя QFile
    if(f->open(QIODevice::ReadOnly |QIODevice:: Text))  //открытие файла
    {
        str=f->readAll();   //считывание всех данных в файле
    }
    f->close(); //закрытие файла
    return str;
}
