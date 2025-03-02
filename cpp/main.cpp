#include <iostream>        // Подключение библиотеки для ввода-вывода
#include <libpq-fe.h>     // Подключение библиотеки для работы с PostgreSQL
// #include "/opt/homebrew/opt/postgresql@14/include/postgresql@14/libpq-fe.h"
#include <string>         // Подключение библиотеки для работы со строками
#include <cstdlib>        // Подключение библиотеки для работы с функцией getenv

#include "Database.h"

//использование некоторых элементов стандартного пространства имен
using std::string; 
using std::cout;
using std::cerr;
using std::endl;
//класс и его переменные

int main() {
    Database db;
    // Открываем соединение с базой данных
    db.connect();
    // Закрываем соединение с базой данных
    db.disconnect();

    return 0; // Завершаем программу с кодом 0 (успех)
}