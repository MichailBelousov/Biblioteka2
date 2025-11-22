#include "Book.h"
#include <sstream>

Book::Book(int id, const std::string& title, const std::string& author,
    int publicationYear, const std::string& genre, const std::string& isbn)
    : id(id), title(title), author(author), publicationYear(publicationYear),
    genre(genre), status("available"), isbn(isbn) {
}

int Book::getId() const {
    return id;
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

int Book::getPublicationYear() const {
    return publicationYear;
}

std::string Book::getGenre() const {
    return genre;
}

std::string Book::getStatus() const {
    return status;
}

std::string Book::getIsbn() const {
    return isbn;
}

bool Book::isAvailable() const {
    return status == "available";
}

bool Book::changeStatus(const std::string& newStatus) {
    if (newStatus == "available" || newStatus == "borrowed" || newStatus == "reserved") {
        status = newStatus;
        return true;
    }
    return false;
}

std::string Book::getBookInfo() const {
    std::stringstream ss;
    ss << "ID: " << id << ", Title: " << title << ", Author: " << author
        << ", Year: " << publicationYear << ", Genre: " << genre
        << ", ISBN: " << isbn << ", Status: " << status;
    return ss.str();
}