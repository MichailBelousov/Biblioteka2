#include "Review.h"
#include <sstream>

Review::Review(int id, int readerId, int bookId, int rating,
    const std::string& comment, const std::string& date)
    : id(id), readerId(readerId), bookId(bookId), rating(rating),
    comment(comment), date(date) {
}

int Review::getId() const {
    return id;
}

int Review::getReaderId() const {
    return readerId;
}

int Review::getBookId() const {
    return bookId;
}

int Review::getRating() const {
    return rating;
}

std::string Review::getComment() const {
    return comment;
}

std::string Review::getDate() const {
    return date;
}

void Review::setRating(int newRating) {
    rating = newRating;
}

void Review::setComment(const std::string& newComment) {
    comment = newComment;
}

bool Review::isValidRating() const {
    return rating >= 1 && rating <= 10;
}

std::string Review::getReviewInfo() const {
    std::stringstream ss;
    ss << "Review ID: " << id << ", Reader ID: " << readerId
        << ", Book ID: " << bookId << ", Rating: " << rating << "/10"
        << ", Date: " << date << "\nComment: " << comment;
    return ss.str();
}