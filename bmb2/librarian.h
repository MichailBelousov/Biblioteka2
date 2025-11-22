#pragma once

#include "User.h"
#include "Book.h"
#include "Reader.h"
#include "Issue.h"
#include <string>

class Library;

class Librarian : public User {
private:
    Library* library;

public:
    Librarian(int id, const std::string& name, const std::string& email);

    void setLibrary(Library* lib);

    // Управление читателями
    bool addReaderToLibrary(const Reader& reader);
    bool removeReaderFromLibrary(int readerId);
    bool updateReaderInfo(int readerId, const std::string& newName,
        const std::string& newEmail, const std::string& newPhone);

    // Оформление выдачи и возврата
    int issueBookToReader(int readerId, int bookId, const std::string& issueDate,
        const std::string& dueDate);
    bool processBookReturn(int issueId, const std::string& returnDate);

    // Управление книгами (только статус)
    bool updateBookStatus(int bookId, const std::string& newStatus);

    // Поиск информации
    Book* findBook(int bookId);
    Reader* findReader(int readerId);

    std::string getInfo() const override;
};