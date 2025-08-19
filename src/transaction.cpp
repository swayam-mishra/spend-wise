#include "Transaction.h"


Transaction::Transaction(int userId, double amount, const std::string& category, const std::string& type, const std::string& date)
    : userId(userId), amount(amount), category(category), type(type), date(date), id(0) {
    // Constructor body is empty.
}

int Transaction::getUserId() const {
    return this->userId;
}

double Transaction::getAmount() const {
    return this->amount;
}

std::string Transaction::getCategory() const {
    return this->category;
}

std::string Transaction::getType() const {
    return this->type;
}

std::string Transaction::getDate() const {
    return this->date;
}
