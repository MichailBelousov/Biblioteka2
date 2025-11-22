#pragma once

#include "Book.h"
#include "Reader.h"
#include "Librarian.h"
#include "Issue.h"
#include "Review.h"
#include <vector>
#include <memory>
#include <string>

class Library {
private:
    std::vector<Book> books;
    std::vector<Reader> readers;
    std::vector<Librarian> librarians;
    std::vector<Issue> activeIssues;
    std::vector<Issue> issueHistory;
    std::vector<Review> reviews;

    Book* findBookById(int bookId);
    Reader* findReaderById(int readerId);
    Librarian* findLibrarianById(int librarianId);
    Issue* findActiveIssueById(int issueId);
    Issue* findActiveIssueByBookId(int bookId);

public:
    Library();

    // Управление книгами
    bool addBook(const Book& book);
    bool removeBook(int bookId);
    Book* getBook(int bookId);
    std::vector<Book> getAllBooks() const;
    std::vector<Book> findBooks(const std::string& query, bool extendedSearch = false);

    // Управление читателями
    bool addReader(const Reader& reader);
    bool removeReader(int readerId);
    Reader* getReader(int readerId);
    std::vector<Reader> getAllReaders() const;

    // Управление библиотекарями
    bool addLibrarian(const Librarian& librarian);
    Librarian* getLibrarian(int librarianId);

    // Управление выдачами
    int issueBook(int readerId, int bookId, int librarianId,
        const std::string& issueDate, const std::string& dueDate);
    bool returnBook(int issueId, const std::string& returnDate);
    std::vector<Issue> getActiveIssues() const;
    std::vector<Issue> getIssueHistory() const;

    // Управление отзывами
    bool addReview(const Review& review);
    std::vector<Review> getBookReviews(int bookId) const;
    std::vector<Review> getAllReviews() const;

    // Статистика
    void generateStatistics() const;
    std::vector<Issue> getReaderHistory(int readerId) const;
    int getAvailableBooksCount() const;
    int getBorrowedBooksCount() const;
    std::vector<Issue> getOverdueIssues(const std::string& currentDate) const;
};