#pragma once

#include "User.h"
#include <string>
#include <vector>

class Reader : public User {
private:
    std::string birthDate;
    std::string phone;
    std::vector<int> borrowedBooks;
    static const int MAX_BOOKS = 5;

public:
    Reader(int id, const std::string& name, const std::string& email,
        const std::string& birthDate, const std::string& phone);

    std::string getBirthDate() const;
    std::string getPhone() const;
    std::vector<int> getBorrowedBooks() const;

    void setBirthDate(const std::string& newBirthDate);
    void setPhone(const std::string& newPhone);

    bool canBorrowMoreBooks() const;
    bool hasBook(int bookId) const;

    std::string getInfo() const override;
};