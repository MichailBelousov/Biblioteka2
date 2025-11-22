#pragma once

#include <string>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    int publicationYear;
    std::string genre;
    std::string status;
    std::string isbn;

public:
    Book(int id, const std::string& title, const std::string& author,
        int publicationYear, const std::string& genre, const std::string& isbn);

    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getPublicationYear() const;
    std::string getGenre() const;
    std::string getStatus() const;
    std::string getIsbn() const;

    bool isAvailable() const;
    bool changeStatus(const std::string& newStatus);

    std::string getBookInfo() const;
};