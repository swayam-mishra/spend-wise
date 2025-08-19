#include "dbManager.h"
#include "Transaction.h" 
#include <iostream>

DatabaseManager::DatabaseManager(const std::string& host, const std::string& user, const std::string& pass, const std::string& db) {
    try {

        driver = std::unique_ptr<sql::mysql::MySQL_Driver>(sql::mysql::get_mysql_driver_instance());

        con.reset(driver->connect(host, user, pass));

        con->setSchema(db);

        std::cout << "Successfully connected to the database." << std::endl;

    } catch (sql::SQLException &e) {
        std::cerr << "ERROR: SQL Exception in DatabaseManager constructor." << std::endl;
        std::cerr << "MySQL Error Code: " << e.getErrorCode() << std::endl;
        std::cerr << "SQLState: " << e.getSQLState() << std::endl;
        std::cerr << "Message: " << e.what() << std::endl;
        exit(1); 
    }
}

DatabaseManager::~DatabaseManager() {
    try {
        if (con && !con->isClosed()) {
            con->close();
        }
        std::cout << "Database connection closed." << std::endl;
    } catch (sql::SQLException &e) {
        std::cerr << "ERROR: SQL Exception in DatabaseManager destructor: " << e.what() << std::endl;
    }
}


bool DatabaseManager::addTransaction(const Transaction& transaction) {
    try {
        
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "INSERT INTO transactions(user_id, amount, category, type, transaction_date) VALUES (?, ?, ?, ?, ?)"
        ));

        pstmt->setInt(1, transaction.getUserId());
        pstmt->setDouble(2, transaction.getAmount());
        pstmt->setString(3, transaction.getCategory());
        pstmt->setString(4, transaction.getType());
        pstmt->setString(5, transaction.getDate());

        pstmt->executeUpdate();

        std::cout << "Transaction added successfully." << std::endl;
        return true;

    } catch (sql::SQLException &e) {
        std::cerr << "ERROR: SQL Exception in addTransaction: " << e.what() << std::endl;
        return false;
    }
}


void DatabaseManager::viewAllTransactions(int userId) {
    std::cout << "Placeholder for viewAllTransactions" << std::endl;
    // We will implement this later.
}

void DatabaseManager::generateMonthlyReport(int userId, int month, int year) {
    std::cout << "Placeholder for generateMonthlyReport" << std::endl;
    // We will implement this later.
}
