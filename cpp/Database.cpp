#include <iostream>        // Подключение библиотеки для ввода-вывода
#include <libpq-fe.h>     // Подключение библиотеки для работы с PostgreSQL
// #include "/opt/homebrew/opt/postgresql@14/include/postgresql@14/libpq-fe.h"
#include <string>         // Подключение библиотеки для работы со строками
#include <cstdlib>        // Подключение библиотеки для работы с функцией getenv

//заголовочный файл
#include "Database.h"

using std::string;
using std::cout;
using std::cerr;
using std::endl;

// метод для получения значений переменных окружения в отдельную переменную и проверка
string Database::getEnvVar(const char* var) {
    const char* value = getenv(var);
    return value ? string(value) : string();
};
// метод для формирования строки подключения к базе данных
string Database::conninfo(){
   string conninfo = 
       "host=" + getEnvVar("POSTGRES_HOST") + 
       " port=" + getEnvVar("POSTGRES_PORT") + 
       " dbname=" + getEnvVar("POSTGRES_DB") + 
       " user=" + getEnvVar("POSTGRES_USER") + 
       " password=" + getEnvVar("POSTGRES_PASSWORD");
   return conninfo;
};
bool Database::connect() {
    conn = PQconnectdb(conninfo().c_str());
    if (PQstatus(conn) == CONNECTION_BAD) {
        cerr << "Connection to database failed: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        // conn = nullptr; // Обнуляем указатель
        return false;
    }
    cout << "Connected to database" << endl;
    return true;
}
void Database::disconnect() {
    if (conn) {
        PQfinish(conn);
        conn = nullptr; // Обнуляем указатель после завершения
        cout << "Disconnected from database" << endl;
    } else {
        cout << "No connection to disconnect" << endl;
    }
}