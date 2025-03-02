#include <iostream>        // Подключение библиотеки для ввода-вывода
#include <libpq-fe.h>     // Подключение библиотеки для работы с PostgreSQL
// #include "/opt/homebrew/opt/postgresql@14/include/postgresql@14/libpq-fe.h"
#include <string>         // Подключение библиотеки для работы со строками
#include <cstdlib>        // Подключение библиотеки для работы с функцией getenv

using std::string;
using std::cout;
using std::cerr;
using std::endl;

class Database {
private:
    string getEnvVar(const char* var);
    PGconn *conn;
    string conninfo();
public:
    bool connect();
    void disconnect();
};
// метод для получения значений переменных окружения в отдельную переменную и проверка
string Database::getEnvVar(const char* var) {
    const char* value = getenv(var);
    return value ? string(value) : string();
};
// метод для формирования строки подключения к базе данных
string Database::conninfo (){
   string conninfo = 
       "host=" + getEnvVar("POSTGRES_HOST") + 
       " port=" + getEnvVar("POSTGRES_PORT") + 
       " dbname=" + getEnvVar("POSTGRES_DB") + 
       " user=" + getEnvVar("POSTGRES_USER") + 
       " password=" + getEnvVar("POSTGRES_PASSWORD");
   return conninfo;
};
bool Database::connect() {
    PGconn *conn = PQconnectdb(conninfo().c_str());
    if (PQstatus(conn) == CONNECTION_BAD) {
        cerr << "Connection to database failed: " << PQerrorMessage(conn) << endl;
        PQfinish(conn);
        return false;
    }
    cout << "Connected to database" << endl;
    return true;
}
void Database::disconnect() {
    // Закрываем соединение с базой данных
    PQfinish(conn);
    cout << "Disconnected from database" << endl;
}

int main() {
    Database db;
    // Открываем соединение с базой данных
    db.connect();
    // Закрываем соединение с базой данных
    db.disconnect();


    return 0; // Завершаем программу с кодом 0 (успех)
}