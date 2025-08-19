#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#define _WIN32_WINNT 0x0601

#include <string>
#include <memory>

#include <mysql/jdbc.h>

class Transaction; 

class DatabaseManager {
public:
    DatabaseManager(const std::string& host, const std::string& user, const std::string& pass, const std::string& db);
    

    ~DatabaseManager();

    bool addTransaction(const Transaction& transaction);

    void viewAllTransactions(int userId);

    void generateMonthlyReport(int userId, int month, int year);

private:

    std::unique_ptr<sql::mysql::MySQL_Driver> driver;
    std::unique_ptr<sql::Connection> con;
};

#endif 
