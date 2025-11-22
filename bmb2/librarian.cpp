#include "Librarian.h"
#include "Library.h"
#include <sstream>
#include <iostream>

Librarian::Librarian(int id, const std::string& name, const std::string& email)
    : User(id, name, email), library(nullptr) {
}

void Librarian::setLibrary(Library* lib) {
    library = lib;
}

// Управление читателями
bool Librarian::addReaderToLibrary(const Reader& reader) {
    if (!library) {
        std::cout << "Ошибка: Библиотека не установлена для библиотекаря" << std::endl;
        return false;
    }
    std::cout << "Библиотекарь " << name << " добавляет нового читателя: " << reader.getName() << std::endl;
    return library->addReader(reader);
}

bool Librarian::removeReaderFromLibrary(int readerId) {
    if (!library) {
        std::cout << "Ошибка: Библиотека не установлена для библиотекаря" << std::endl;
        return false;
    }
    return library->removeReader(readerId);
}

bool Librarian::updateReaderInfo(int readerId, const std::string& newName,
    const std::string& newEmail, const std::string& newPhone) {
    if (!library) {
        std::cout << "Ошибка: Библиотека не установлена для библиотекаря" << std::endl;
        return false;
    }

    Reader* reader = library->getReader(readerId);
    if (!reader) {
        std::cout << "Ошибка: Читатель с ID " << readerId << " не найден" << std::endl;
        return false;
    }

    reader->setName(newName);
    reader->setEmail(newEmail);
    reader->setPhone(newPhone);

    std::cout << "Данные читателя обновлены: " << reader->getInfo() << std::endl;
    return true;
}

// Оформление выдачи и возврата
int Librarian::issueBookToReader(int readerId, int bookId, const std::string& issueDate,
    const std::string& dueDate) {
    if (!library) {
        std::cout << "Ошибка: Библиотека не установлена для библиотекаря" << std::endl;
        return -1;
    }

    Book* book = library->getBook(bookId);
    Reader* reader = library->getReader(readerId);

    if (!book) {
        std::cout << "Ошибка: Книга с ID " << bookId << " не найдена" << std::endl;
        return -1;
    }

    if (!reader) {
        std::cout << "Ошибка: Читатель с ID " << readerId << " не найден" << std::endl;
        return -1;
    }

    if (!book->isAvailable()) {
        std::cout << "Ошибка: Книга '" << book->getTitle() << "' недоступна для выдачи" << std::endl;
        return -1;
    }

    if (!reader->canBorrowMoreBooks()) {
        std::cout << "Ошибка: Читатель " << reader->getName() << " достиг лимита книг" << std::endl;
        return -1;
    }

    std::cout << "Библиотекарь " << name << " оформляет выдачу:" << std::endl;
    std::cout << "Книга: " << book->getTitle() << " (ID: " << bookId << ")" << std::endl;
    std::cout << "Читатель: " << reader->getName() << " (ID: " << readerId << ")" << std::endl;
    std::cout << "Срок возврата: " << dueDate << std::endl;

    int issueId = library->issueBook(readerId, bookId, this->id, issueDate, dueDate);

    if (issueId > 0) {
        std::cout << "Выдача успешно оформлена. ID выдачи: " << issueId << std::endl;
        // Обновляем статус книги
        book->changeStatus("borrowed");
    }
    else {
        std::cout << "Ошибка оформления выдачи" << std::endl;
    }

    return issueId;
}

bool Librarian::processBookReturn(int issueId, const std::string& returnDate) {
    if (!library) {
        std::cout << "Ошибка: Библиотека не установлена для библиотекаря" << std::endl;
        return false;
    }

    // Находим выдачу
    std::vector<Issue> activeIssues = library->getActiveIssues();
    Issue* targetIssue = nullptr;
    int issueIndex = -1;

    for (int i = 0; i < activeIssues.size(); i++) {
        if (activeIssues[i].getId() == issueId) {
            targetIssue = &activeIssues[i];
            issueIndex = i;
            break;
        }
    }

    if (!targetIssue) {
        std::cout << "Ошибка: Выдача с ID " << issueId << " не найдена" << std::endl;
        return false;
    }

    // Получаем информацию о книге и читателе
    Book* book = library->getBook(targetIssue->getBookId());
    Reader* reader = library->getReader(targetIssue->getReaderId());

    if (book && reader) {
        std::cout << "Библиотекарь " << name << " оформляет возврат:" << std::endl;
        std::cout << "Книга: " << book->getTitle() << std::endl;
        std::cout << "Читатель: " << reader->getName() << std::endl;
        std::cout << "Дата возврата: " << returnDate << std::endl;

        if (targetIssue->isOverdue(returnDate)) {
            std::cout << "ВНИМАНИЕ: Книга возвращена с просрочкой!" << std::endl;
        }
    }

    bool success = library->returnBook(issueId, returnDate);

    if (success && book) {
        // Обновляем статус книги
        book->changeStatus("available");
        std::cout << "Возврат успешно оформлен." << std::endl;
    }
    else {
        std::cout << "Ошибка оформления возврата." << std::endl;
    }

    return success;
}

// Управление статусом книг
bool Librarian::updateBookStatus(int bookId, const std::string& newStatus) {
    if (!library) {
        std::cout << "Ошибка: Библиотека не установлена для библиотекаря" << std::endl;
        return false;
    }

    Book* book = library->getBook(bookId);
    if (!book) {
        std::cout << "Ошибка: Книга с ID " << bookId << " не найдена" << std::endl;
        return false;
    }

    if (book->changeStatus(newStatus)) {
        std::cout << "Статус книги '" << book->getTitle() << "' изменен на: " << newStatus << std::endl;
        return true;
    }
    else {
        std::cout << "Ошибка: Неверный статус '" << newStatus << "'" << std::endl;
        return false;
    }
}

// Поиск информации
Book* Librarian::findBook(int bookId) {
    if (!library) return nullptr;
    return library->getBook(bookId);
}

Reader* Librarian::findReader(int readerId) {
    if (!library) return nullptr;
    return library->getReader(readerId);
}

std::string Librarian::getInfo() const {
    std::stringstream ss;
    ss << User::getInfo() << " (Библиотекарь)";
    return ss.str();
}