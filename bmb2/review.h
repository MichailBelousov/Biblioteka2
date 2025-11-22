#pragma once

#include <string>

class Review {
private:
    int id;
    int readerId;
    int bookId;
    int rating;           // 1-10
    std::string comment;
    std::string date;

public:
    Review(int id, int readerId, int bookId, int rating,
        const std::string& comment, const std::string& date);

    int getId() const;
    int getReaderId() const;
    int getBookId() const;
    int getRating() const;
    std::string getComment() const;
    std::string getDate() const;

    void setRating(int newRating);
    void setComment(const std::string& newComment);

    bool isValidRating() const;

    std::string getReviewInfo() const;
};