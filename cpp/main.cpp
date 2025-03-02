#include <iostream>        // Подключение библиотеки для ввода-вывода
#include <libpq-fe.h>     // Подключение библиотеки для работы с PostgreSQL
#include <string>         // Подключение библиотеки для работы со строками
#include <cstdlib>        // Подключение библиотеки для работы с функцией getEnvVar

std::string getEnvVar(const char* var) {
    const char* value = getenv(var);
    return value ? std::string(value) : std::string();
}

int main() {
    // Получение значений переменных окружения для подключения к PostgreSQL
    std::string host = getEnvVar("POSTGRES_HOST");
    std::string port = getEnvVar("POSTGRES_PORT");
    std::string dbname = getEnvVar("POSTGRES_DB");
    std::string user = getEnvVar("POSTGRES_USER");
    std::string password = getEnvVar("POSTGRES_PASSWORD");

    // Проверка, что все необходимые переменные окружения заданы
    if (host.empty() || port.empty() || dbname.empty() || user.empty() || password.empty()) {
        std::cerr << "Environment variables are not set" << std::endl; // Сообщение об ошибке
        return 1; // Завершаем программу с кодом ошибки 1
    }

    // Формирование строки подключения к базе данных
    std::string conninfo = 
        "host=" + host + 
        " port=" + port + 
        " dbname=" + dbname + 
        " user=" + user + 
        " password=" + password;

    // Создание соединения с базой данных PostgreSQL
    PGconn *conn = PQconnectdb(conninfo.c_str());

    // Проверка статуса подключения
    if (PQstatus(conn) == CONNECTION_BAD) {
        // Если подключение не удалось, выводим сообщение об ошибке
        std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
        // Закрываем соединение, если оно было установлено
        PQfinish(conn);
        return 1; // Завершаем программу с кодом ошибки 1
    }

    // Если подключение успешно, выводим сообщение
    std::cout << "Connected to database" << std::endl;

    // Закрываем соединение с базой данных
    PQfinish(conn);
    // Сообщаем, что мы отключились от базы данных
    std::cout << "Disconnected from database" << std::endl;

    return 0; // Завершаем программу с кодом 0 (успех)
}