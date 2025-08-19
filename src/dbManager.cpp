#include "dbManager.h"
#include "Transaction.h"
#include <iostream>
#include <iomanip>

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
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT id, amount, category, type, transaction_date FROM transactions WHERE user_id = ?"
        ));
        pstmt->setInt(1, userId);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "\n--- All Transactions ---" << std::endl;
        std::cout << std::left << std::setw(5) << "ID"
                  << std::setw(15) << "Date"
                  << std::setw(20) << "Category"
                  << std::setw(10) << "Type"
                  << std::setw(10) << "Amount" << std::endl;
        std::cout << "------------------------------------------------------------" << std::endl;

        if (!res->next()) {
            std::cout << "No transactions found for this user." << std::endl;
        } else {
            do {
                std::cout << std::left << std::setw(5) << res->getInt("id")
                          << std::setw(15) << res->getString("transaction_date")
                          << std::setw(20) << res->getString("category")
                          << std::setw(10) << res->getString("type")
                          << std::fixed << std::setprecision(2) << res->getDouble("amount") << std::endl;
            } while (res->next());
        }
        std::cout << "------------------------------------------------------------\n" << std::endl;

    } catch (sql::SQLException &e) {
        std::cerr << "ERROR: SQL Exception in viewAllTransactions: " << e.what() << std::endl;
    }
}

void DatabaseManager::generateMonthlyReport(int userId, int month, int year) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(
            "SELECT "
            "   COALESCE(SUM(CASE WHEN type = 'income' THEN amount ELSE 0 END), 0) AS total_income, "
            "   COALESCE(SUM(CASE WHEN type = 'expense' THEN amount ELSE 0 END), 0) AS total_expense "
            "FROM transactions "
            "WHERE user_id = ? AND MONTH(transaction_date) = ? AND YEAR(transaction_date) = ?"
        ));
        pstmt->setInt(1, userId);
        pstmt->setInt(2, month);
        pstmt->setInt(3, year);

        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        std::cout << "\n--- Monthly Report for " << month << "/" << year << " ---" << std::endl;

        if (res->next()) {
            double totalIncome = res->getDouble("total_income");
            double totalExpense = res->getDouble("total_expense");
            double savings = totalIncome - totalExpense;

            std::cout << std::fixed << std::setprecision(2);
            std::cout << "Total Income:   $" << totalIncome << std::endl;
            std::cout << "Total Expenses: $" << totalExpense << std::endl;
            std::cout << "--------------------------" << std::endl;
            std::cout << "Net Savings:    $" << savings << std::endl;
        }
        std::cout << "--------------------------\n" << std::endl;

    } catch (sql::SQLException &e) {
        std::cerr << "ERROR: SQL Exception in generateMonthlyReport: " << e.what() << std::endl;
    }
}