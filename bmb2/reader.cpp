#include "Reader.h"
#include <algorithm>
#include <sstream>

Reader::Reader(int id, const std::string& name, const std::string& email,
    const std::string& birthDate, const std::string& phone)
    : User(id, name, email), birthDate(birthDate), phone(phone) {
}

std::string Reader::getBirthDate() const {
    return birthDate;
}

std::string Reader::getPhone() const {
    return phone;
}

std::vector<int> Reader::getBorrowedBooks() const {
    return borrowedBooks;
}

void Reader::setBirthDate(const std::string& newBirthDate) {
    birthDate = newBirthDate;
}

void Reader::setPhone(const std::string& newPhone) {
    phone = newPhone;
}

bool Reader::canBorrowMoreBooks() const {
    return borrowedBooks.size() < MAX_BOOKS;
}

bool Reader::hasBook(int bookId) const {
    return std::find(borrowedBooks.begin(), borrowedBooks.end(), bookId) != borrowedBooks.end();
}

std::string Reader::getInfo() const {
    std::stringstream ss;
    ss << User::getInfo() << ", Birth Date: " << birthDate
        << ", Phone: " << phone << ", Borrowed Books: " << borrowedBooks.size();
    return ss.str();
}