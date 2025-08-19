#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Transaction {
public:
    Transaction(int userId, double amount, const std::string& category, const std::string& type, const std::string& date);

    int getUserId() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getType() const;
    std::string getDate() const;

private:
    int id; 
    int userId;
    double amount;
    std::string category;
    std::string type; 
    std::string date; 
};

#endif 
