#include "User.h"

User::User(int id, const std::string& name) : id(id), name(name) {
}

int User::getId() const {
    return this->id;
}

std::string User::getName() const {
    return this->name;
}
