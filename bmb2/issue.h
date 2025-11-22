#pragma once

#include <string>

class Issue {
private:
    int id;
    int bookId;
    int readerId;
    int librarianId;
    std::string issueDate;
    std::string dueDate;
    std::string returnDate;
    bool isClosed;

public:
    Issue(int id, int bookId, int readerId, int librarianId,
        const std::string& issueDate, const std::string& dueDate);

    int getId() const;
    int getBookId() const;
    int getReaderId() const;
    int getLibrarianId() const;
    std::string getIssueDate() const;
    std::string getDueDate() const;
    std::string getReturnDate() const;
    bool getIsClosed() const;

    void closeIssue(const std::string& returnDate);
    bool isOverdue(const std::string& currentDate) const;

    std::string getIssueInfo() const;
};