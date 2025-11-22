#include "Issue.h"
#include <sstream>

Issue::Issue(int id, int bookId, int readerId, int librarianId,
    const std::string& issueDate, const std::string& dueDate)
    : id(id), bookId(bookId), readerId(readerId), librarianId(librarianId),
    issueDate(issueDate), dueDate(dueDate), returnDate(""), isClosed(false) {
}

int Issue::getId() const {
    return id;
}

int Issue::getBookId() const {
    return bookId;
}

int Issue::getReaderId() const {
    return readerId;
}

int Issue::getLibrarianId() const {
    return librarianId;
}

std::string Issue::getIssueDate() const {
    return issueDate;
}

std::string Issue::getDueDate() const {
    return dueDate;
}

std::string Issue::getReturnDate() const {
    return returnDate;
}

bool Issue::getIsClosed() const {
    return isClosed;
}

void Issue::closeIssue(const std::string& returnDate) {
    this->returnDate = returnDate;
    isClosed = true;
}

bool Issue::isOverdue(const std::string& currentDate) const {
    if (isClosed) {
        return returnDate > dueDate;
    }
    return currentDate > dueDate;
}

std::string Issue::getIssueInfo() const {
    std::stringstream ss;
    ss << "Issue ID: " << id << ", Book ID: " << bookId
        << ", Reader ID: " << readerId << ", Librarian ID: " << librarianId
        << ", Issue Date: " << issueDate << ", Due Date: " << dueDate
        << ", Status: " << (isClosed ? "Closed" : "Active");
    if (isClosed) {
        ss << ", Return Date: " << returnDate;
    }
    return ss.str();
}