#include "Library.h"
#include <algorithm>
#include <iostream>
#include <sstream>

Library::Library() {}

// Вспомогательные методы для поиска
Book* Library::findBookById(int bookId) {
    for (auto& book : books) {
        if (book.getId() == bookId) {
            return &book;
        }
    }
    return nullptr;
}

Reader* Library::findReaderById(int readerId) {
    for (auto& reader : readers) {
        if (reader.getId() == readerId) {
            return &reader;
        }
    }
    return nullptr;
}

Librarian* Library::findLibrarianById(int librarianId) {
    for (auto& librarian : librarians) {
        if (librarian.getId() == librarianId) {
            return &librarian;
        }
    }
    return nullptr;
}

Issue* Library::findActiveIssueById(int issueId) {
    for (auto& issue : activeIssues) {
        if (issue.getId() == issueId) {
            return &issue;
        }
    }
    return nullptr;
}

Issue* Library::findActiveIssueByBookId(int bookId) {
    for (auto& issue : activeIssues) {
        if (issue.getBookId() == bookId && !issue.getIsClosed()) {
            return &issue;
        }
    }
    return nullptr;
}

// Управление книгами
bool Library::addBook(const Book& book) {
    if (findBookById(book.getId()) != nullptr) {
        return false;
    }
    books.push_back(book);
    return true;
}

bool Library::removeBook(int bookId) {
    auto it = std::find_if(books.begin(), books.end(),
        [bookId](const Book& book) { return book.getId() == bookId; });

    if (it != books.end()) {
        if (findActiveIssueByBookId(bookId) != nullptr) {
            return false;
        }
        books.erase(it);
        return true;
    }
    return false;
}

Book* Library::getBook(int bookId) {
    return findBookById(bookId);
}

std::vector<Book> Library::getAllBooks() const {
    return books;
}

std::vector<Book> Library::findBooks(const std::string& query, bool extendedSearch) {
    std::vector<Book> result;

    for (const auto& book : books) {
        bool matches = false;

        if (book.getTitle().find(query) != std::string::npos ||
            book.getAuthor().find(query) != std::string::npos) {
            matches = true;
        }

        if (extendedSearch && !matches) {
            if (book.getGenre().find(query) != std::string::npos ||
                book.getIsbn().find(query) != std::string::npos) {
                matches = true;
            }
        }

        if (matches) {
            result.push_back(book);
        }
    }

    return result;
}

// Управление читателями
bool Library::addReader(const Reader& reader) {
    if (findReaderById(reader.getId()) != nullptr) {
        return false;
    }
    readers.push_back(reader);
    return true;
}

bool Library::removeReader(int readerId) {
    auto it = std::find_if(readers.begin(), readers.end(),
        [readerId](const Reader& reader) { return reader.getId() == readerId; });

    if (it != readers.end()) {
        if (!it->getBorrowedBooks().empty()) {
            return false;
        }
        readers.erase(it);
        return true;
    }
    return false;
}

Reader* Library::getReader(int readerId) {
    return findReaderById(readerId);
}

std::vector<Reader> Library::getAllReaders() const {
    return readers;
}

// Управление библиотекарями
bool Library::addLibrarian(const Librarian& librarian) {
    if (findLibrarianById(librarian.getId()) != nullptr) {
        return false;
    }
    librarians.push_back(librarian);
    return true;
}

Librarian* Library::getLibrarian(int librarianId) {
    return findLibrarianById(librarianId);
}

// Управление выдачами
int Library::issueBook(int readerId, int bookId, int librarianId,
    const std::string& issueDate, const std::string& dueDate) {
    Reader* reader = findReaderById(readerId);
    Book* book = findBookById(bookId);
    Librarian* librarian = findLibrarianById(librarianId);

    if (!reader || !book || !librarian) {
        return -1;
    }

    if (!book->isAvailable()) {
        return -2;
    }

    if (!reader->canBorrowMoreBooks()) {
        return -3;
    }

    int newIssueId = activeIssues.empty() ? 1 : activeIssues.back().getId() + 1;
    Issue newIssue(newIssueId, bookId, readerId, librarianId, issueDate, dueDate);

    activeIssues.push_back(newIssue);
    return newIssueId;
}

bool Library::returnBook(int issueId, const std::string& returnDate) {
    Issue* issue = findActiveIssueById(issueId);
    if (!issue || issue->getIsClosed()) {
        return false;
    }

    issue->closeIssue(returnDate);
    issueHistory.push_back(*issue);

    auto it = std::find_if(activeIssues.begin(), activeIssues.end(),
        [issueId](const Issue& iss) { return iss.getId() == issueId; });
    if (it != activeIssues.end()) {
        activeIssues.erase(it);
    }

    return true;
}

std::vector<Issue> Library::getActiveIssues() const {
    return activeIssues;
}

std::vector<Issue> Library::getIssueHistory() const {
    return issueHistory;
}

// Управление отзывами
bool Library::addReview(const Review& review) {
    if (!review.isValidRating()) {
        return false;
    }

    auto it = std::find_if(reviews.begin(), reviews.end(),
        [&review](const Review& rev) { return rev.getId() == review.getId(); });

    if (it != reviews.end()) {
        return false;
    }

    reviews.push_back(review);
    return true;
}

std::vector<Review> Library::getBookReviews(int bookId) const {
    std::vector<Review> result;
    for (const auto& review : reviews) {
        if (review.getBookId() == bookId) {
            result.push_back(review);
        }
    }
    return result;
}

std::vector<Review> Library::getAllReviews() const {
    return reviews;
}

// Статистика
void Library::generateStatistics() const {
    std::cout << "=== Library Statistics ===" << std::endl;
    std::cout << "Total Books: " << books.size() << std::endl;
    std::cout << "Available Books: " << getAvailableBooksCount() << std::endl;
    std::cout << "Borrowed Books: " << getBorrowedBooksCount() << std::endl;
    std::cout << "Total Readers: " << readers.size() << std::endl;
    std::cout << "Total Librarians: " << librarians.size() << std::endl;
    std::cout << "Active Issues: " << activeIssues.size() << std::endl;
    std::cout << "Total Reviews: " << reviews.size() << std::endl;
}

std::vector<Issue> Library::getReaderHistory(int readerId) const {
    std::vector<Issue> result;

    for (const auto& issue : activeIssues) {
        if (issue.getReaderId() == readerId) {
            result.push_back(issue);
        }
    }

    for (const auto& issue : issueHistory) {
        if (issue.getReaderId() == readerId) {
            result.push_back(issue);
        }
    }

    return result;
}

int Library::getAvailableBooksCount() const {
    int count = 0;
    for (const auto& book : books) {
        if (book.isAvailable()) {
            count++;
        }
    }
    return count;
}

int Library::getBorrowedBooksCount() const {
    int count = 0;
    for (const auto& book : books) {
        if (!book.isAvailable()) {
            count++;
        }
    }
    return count;
}

std::vector<Issue> Library::getOverdueIssues(const std::string& currentDate) const {
    std::vector<Issue> result;
    for (const auto& issue : activeIssues) {
        if (issue.isOverdue(currentDate)) {
            result.push_back(issue);
        }
    }
    return result;
}