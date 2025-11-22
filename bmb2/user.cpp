#include "User.h"
#include <sstream>

User::User(int id, const std::string& name, const std::string& email)
    : id(id), name(name), email(email) {
}

int User::getId() const {
    return id;
}

std::string User::getName() const {
    return name;
}

std::string User::getEmail() const {
    return email;
}

void User::setName(const std::string& newName) {
    name = newName;
}

void User::setEmail(const std::string& newEmail) {
    email = newEmail;
}

std::string User::getInfo() const {
    std::stringstream ss;
    ss << "ID: " << id << ", Name: " << name << ", Email: " << email;
    return ss.str();
}