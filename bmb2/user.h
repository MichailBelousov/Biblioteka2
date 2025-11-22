#pragma once

#include <string>

class User {
protected:
    int id;
    std::string name;
    std::string email;

public:
    User(int id, const std::string& name, const std::string& email);
    virtual ~User() = default;

    int getId() const;
    std::string getName() const;
    std::string getEmail() const;

    void setName(const std::string& newName);
    void setEmail(const std::string& newEmail);

    virtual std::string getInfo() const;
};