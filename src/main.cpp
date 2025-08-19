#include <iostream>
#include <limits>
#include <fstream>
#include "dbManager.h"
#include "Transaction.h"

// Function Prototypes
void displayMenu();
void handleAddTransaction(DatabaseManager& db, int userId);
void handleViewTransactions(DatabaseManager& db, int userId);
void handleGenerateReport(DatabaseManager& db, int userId);

// A simple function to read config from a .ini file
std::string getConfigValue(const std::string& key) {
    std::ifstream configFile("config.ini");
    // Error Handling: Check if the file was successfully opened.
    if (!configFile.is_open()) {
        return "";
    }

    std::string line;
    while (std::getline(configFile, line)) {
        size_t delimiterPos = line.find("=");
        if (delimiterPos != std::string::npos) {
            std::string currentKey = line.substr(0, delimiterPos);
            currentKey.erase(0, currentKey.find_first_not_of(" \t"));
            currentKey.erase(currentKey.find_last_not_of(" \t") + 1);

            if (currentKey == key) {
                std::string value = line.substr(delimiterPos + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);
                return value;
            }
        }
    }
    return "";
}


int main() {
    std::string host = getConfigValue("host");
    std::string user = getConfigValue("user");
    std::string pass = getConfigValue("password");
    std::string db_name = getConfigValue("database_name");

    if (host.empty() || user.empty() || db_name.empty()) {
        std::cerr << "Error: Could not read database configuration from config.ini." << std::endl;
        std::cerr << "Please ensure config.ini exists and has host, user, password, and database_name." << std::endl;
        return 1;
    }

    DatabaseManager db(host, user, pass, db_name);
    
    // Hardcode the user ID. 
    // The sample user created in schema.sql has ID = 1.
    int currentUserId = 1; 
    int choice = 0;

    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = -1; 
            continue;
        }

        switch (choice) {
            case 1:
                handleAddTransaction(db, currentUserId);
                break;
            case 2:
                handleViewTransactions(db, currentUserId);
                break;
            case 3:
                handleGenerateReport(db, currentUserId);
                break;
            case 4:
                std::cout << "Exiting application." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}

void displayMenu() {
    std::cout << "\n--- Personal Finance Tracker ---" << std::endl;
    std::cout << "1. Add Transaction" << std::endl;
    std::cout << "2. View All Transactions" << std::endl;
    std::cout << "3. Generate Monthly Report" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "--------------------------------" << std::endl;
}

void handleAddTransaction(DatabaseManager& db, int userId) {
    double amount;
    std::string category, type, date;
    int typeChoice;

    std::cout << "Enter amount: ";
    std::cin >> amount;
    std::cout << "Enter category (e.g., Food, Salary): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::getline(std::cin, category);
    std::cout << "Enter type (1 for Income, 2 for Expense): ";
    std::cin >> typeChoice;
    type = (typeChoice == 1) ? "income" : "expense";
    std::cout << "Enter date (YYYY-MM-DD): ";
    std::cin >> date;

    Transaction newTransaction(userId, amount, category, type, date);
    db.addTransaction(newTransaction);
}

void handleViewTransactions(DatabaseManager& db, int userId) {
    db.viewAllTransactions(userId);
}

void handleGenerateReport(DatabaseManager& db, int userId) {
    int month, year;
    std::cout << "Enter month (1-12): ";
    std::cin >> month;
    std::cout << "Enter year (e.g., 2024): ";
    std::cin >> year;
    db.generateMonthlyReport(userId, month, year);
}
