#include <iostream>
#include "Library.h"
#include "Librarian.h"
#include "Reader.h"
#include "Book.h"
#include "Review.h"

using namespace std;

void demonstrateLibraryWorkflow() {
    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ БИБЛИОТЕКИ ===" << endl << endl;

    // Создаем библиотеку
    Library library;

    // Добавляем книги в библиотеку
    cout << "1. ДОБАВЛЕНИЕ КНИГ В БИБЛИОТЕКУ" << endl;
    cout << "=================================" << endl;
    Book book1(1, "Война и мир", "Лев Толстой", 1869, "Роман-эпопея", "978-5-17-090324-1");
    Book book2(2, "Преступление и наказание", "Федор Достоевский", 1866, "Роман", "978-5-04-100321-2");
    Book book3(3, "Мастер и Маргарита", "Михаил Булгаков", 1967, "Фантастика", "978-5-17-088808-3");
    Book book4(4, "Евгений Онегин", "Александр Пушкин", 1833, "Роман в стихах", "978-5-389-04567-8");

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);
    library.addBook(book4);

    cout << "Добавлены книги:" << endl;
    for (const auto& book : library.getAllBooks()) {
        cout << "- " << book.getBookInfo() << endl;
    }
    cout << endl;

    // Создаем библиотекаря
    cout << "2. СОЗДАНИЕ БИБЛИОТЕКАРЯ" << endl;
    cout << "========================" << endl;
    Librarian librarian(101, "Анна Ивановна", "anna@library.ru");
    librarian.setLibrary(&library);
    library.addLibrarian(librarian);
    cout << "Библиотекарь: " << librarian.getInfo() << endl << endl;

    // Новый читатель заполняет бланк
    cout << "3. РЕГИСТРАЦИЯ НОВОГО ЧИТАТЕЛЯ" << endl;
    cout << "==============================" << endl;
    Reader newReader(201, "Петр Сергеев", "peter@mail.ru", "1995-03-15", "+79161234567");
    cout << "Новый читатель заполнил бланк:" << endl;
    cout << "- Имя: " << newReader.getName() << endl;
    cout << "- Email: " << newReader.getEmail() << endl;
    cout << "- Дата рождения: " << newReader.getBirthDate() << endl;
    cout << "- Телефон: " << newReader.getPhone() << endl;

    // Библиотекарь добавляет читателя в систему
    bool readerAdded = librarian.addReaderToLibrary(newReader);
    if (readerAdded) {
        cout << "Читатель успешно добавлен в систему!" << endl;
    }
    cout << endl;

    // Читатель просматривает ассортимент
    cout << "4. ПРОСМОТР АССОРТИМЕНТА КНИГ" << endl;
    cout << "==============================" << endl;
    cout << "Доступные книги в библиотеке:" << endl;
    for (const auto& book : library.getAllBooks()) {
        if (book.isAvailable()) {
            cout << "- " << book.getTitle() << " (" << book.getAuthor() << ")" << endl;
        }
    }
    cout << endl;

    // Читатель выбирает книгу и подходит к библиотекарю
    cout << "5. ОФОРМЛЕНИЕ ВЫДАЧИ КНИГИ" << endl;
    cout << "===========================" << endl;
    cout << "Читатель выбирает 'Войну и мир'" << endl;
    int issueId = librarian.issueBookToReader(201, 1, "2024-01-15", "2024-02-15");
    cout << endl;

    // Библиотекарь проверяет статус книги
    cout << "6. ПРОВЕРКА СТАТУСА КНИГИ" << endl;
    cout << "==========================" << endl;
    Book* warAndPeace = librarian.findBook(1);
    if (warAndPeace) {
        cout << "Статус книги '" << warAndPeace->getTitle() << "': " << warAndPeace->getStatus() << endl;
    }
    cout << endl;

    // Добавляем еще одного читателя и выдаем ему книгу
    cout << "7. РАБОТА С НЕСКОЛЬКИМИ ЧИТАТЕЛЯМИ" << endl;
    cout << "==================================" << endl;
    Reader reader2(202, "Мария Петрова", "maria@mail.ru", "1990-07-20", "+79167654321");
    librarian.addReaderToLibrary(reader2);
    librarian.issueBookToReader(202, 2, "2024-01-16", "2024-02-16");
    cout << endl;

    // Читатель возвращает книгу
    cout << "8. ВОЗВРАТ КНИГИ" << endl;
    cout << "=================" << endl;
    cout << "Читатель Петр возвращает 'Войну и мир'" << endl;
    librarian.processBookReturn(issueId, "2024-02-10");
    cout << endl;

    // Читатель оставляет отзыв
    cout << "9. ЧИТАТЕЛЬ ОСТАВЛЯЕТ ОТЗЫВ" << endl;
    cout << "============================" << endl;
    Review review(1, 201, 1, 9, "Великая книга! Читается тяжеловато, но очень глубокая.", "2024-02-12");
    if (library.addReview(review)) {
        cout << "Отзыв успешно добавлен:" << endl;
        cout << review.getReviewInfo() << endl;
    }
    cout << endl;

    // Еще один отзыв от другого читателя
    Review review2(2, 202, 2, 10, "Шедевр! Обязательно к прочтению.", "2024-02-18");
    library.addReview(review2);

    // Показываем все отзывы на книги
    cout << "10. ВСЕ ОТЗЫВЫ В БИБЛИОТЕКЕ" << endl;
    cout << "============================" << endl;
    for (const auto& review : library.getAllReviews()) {
        cout << review.getReviewInfo() << endl << endl;
    }

    // Библиотекарь обновляет информацию о читателе
    cout << "11. ОБНОВЛЕНИЕ ДАННЫХ ЧИТАТЕЛЯ" << endl;
    cout << "===============================" << endl;
    librarian.updateReaderInfo(201, "Петр Сергеев", "peter.new@mail.ru", "+79169998877");
    cout << endl;

    // Поиск книг
    cout << "12. ПОИСК КНИГ" << endl;
    cout << "==============" << endl;
    cout << "Поиск по запросу 'Толстой':" << endl;
    vector<Book> foundBooks = library.findBooks("Толстой");
    for (const auto& book : foundBooks) {
        cout << "- " << book.getTitle() << endl;
    }
    cout << endl;

    // Статистика библиотеки
    cout << "13. СТАТИСТИКА БИБЛИОТЕКИ" << endl;
    cout << "==========================" << endl;
    library.generateStatistics();
    cout << endl;

    // История читателя
    cout << "14. ИСТОРИЯ ЧИТАТЕЛЯ" << endl;
    cout << "=====================" << endl;
    vector<Issue> readerHistory = library.getReaderHistory(201);
    cout << "История выдач читателя Петр:" << endl;
    for (const auto& issue : readerHistory) {
        cout << "- " << issue.getIssueInfo() << endl;
    }
    cout << endl;

    // Демонстрация обработки ошибок
    cout << "15. ОБРАБОТКА ОШИБОК" << endl;
    cout << "=====================" << endl;
    // Попытка выдать уже выданную книгу
    librarian.issueBookToReader(201, 2, "2024-02-20", "2024-03-20");
    cout << endl;

    // Попытка удалить читателя с книгами
    if (!library.removeReader(202)) {
        cout << "Нельзя удалить читателя с ID 202: у него есть книги" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    demonstrateLibraryWorkflow();
    cout << "=== ДЕМОНСТРАЦИЯ ЗАВЕРШЕНА ===" << endl;
    return 0;
}