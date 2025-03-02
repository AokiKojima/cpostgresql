
#include <iostream>
#include <libpq-fe.h>
// #include "/opt/homebrew/opt/postgresql@14/include/postgresql@14/libpq-fe.h"
#include <string>

using std::string;

class Database {
    private:
        string getEnvVar(const char* var);
        PGconn *conn;
        string conninfo();
    public:
        bool connect();
        void disconnect();
    };