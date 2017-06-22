#include "my_exception.h"
QString input_record()
{
    while(1)
   {
        try
        {
           bool bOk;
            QString str = QInputDialog::getText( 0,
                                                 "Input",
                                                 "Name:",
                                                 QLineEdit::Normal,
                                                 "Tarja",
                                                 &bOk
                                                );
        //проверка на английские символы
        for(int i=0;str[i]!='\0';i++)
        {
            if((str[i]<'a' ||str[i]>'z')&&(str[i]<'A'||str[i]>'Z'))
                throw record_exception(2,"ERROR in Input name");
        }
        return str;
        }
        catch(record_exception & o)
        {
           o.show();
        }
    }
}
file_exception::file_exception(int c, char *s)
{
    code=c;
    strcpy(str_error, s);
}
void file_exception::show()
{
    //присваивание строке информации с ошибкой
    char  str[1000];
    char cod[2];
    itoa(code, cod, 2);
    strcat(str, "ERROR CODE ");
    strcat(str, cod);
    strcat(str, "\n");
    strcat(str, "Reason: ");
    strcat(str, str_error);
    //вывод окна с ошибкой
    QMessageBox::information(0,"File",str);
}
record_exception::record_exception(int c, char *s)
{
    code=c;
    strcpy(str_error, s);
}

void record_exception::show()
{
    //присваивание строке информации с ошибкой
     char  str[1000];
     char cod[2];
     itoa(code, cod, 2);
     strcat(str, "ERROR CODE ");
     strcat(str, cod);
     strcat(str, "\n");
     strcat(str, "Reason: ");
     strcat(str, str_error);
     QMessageBox::information(0,"Records",str);
}

