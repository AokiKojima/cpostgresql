// #include <iostream>
// #include <libpq-fe.h>

// int main() {
//     PGconn *conn = PQconnectdb("host=postgres port=5432 dbname=postgres user=postgres password=postgres");
//     if (PQstatus(conn) == CONNECTION_BAD) {
//         std::cerr << "Connection to database failed: " << PQerrorMessage(conn) << std::endl;
//         PQfinish(conn);
//         return 1;
//     }
//     std::cout << "Connected to database" << std::endl;
//     PQfinish(conn);
//     std::cout << "Disconnected from database" << std::endl;
//     return 0;
// }

#include <iostream>        // Подключение библиотеки для ввода-вывода
#include <libpq-fe.h>     // Подключение библиотеки для работы с PostgreSQL


int main() {

    const char *host = getenv("POSTGRES_HOST");
    const char *port = getenv("POSTGRES_PORT");
    const char *dbname = getenv("POSTGRES_DB");
    const char *user = getenv("POSTGRES_USER");
    const char *password = getenv("POSTGRES_PASSWORD");

    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo), "host=%s port=%s dbname=%s user=%s password=%s", host, port, dbname, user, password);
    // Создание строки подключения к базе данных PostgreSQL
    // Здесь указаны хост, порт, имя базы данных, пользователь и пароль
    // PGconn *conn = PQconnectdb("host=postgres port=5432 dbname=postgres user=postgres password=postgres");

    PGconn *conn = PQconnectdb(conninfo);

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