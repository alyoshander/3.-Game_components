#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include <vector>
#include <string>

class Library {
private:
    std::vector<Book> books;  // композиция: библиотека содержит книги

public:
    // Добавление/удаление
    void addBook(const Book& book);
    bool removeBook(const std::string& isbn);
    
    // Поиск
    std::vector<Book> findByAuthor(const std::string& author) const;
    Book* findByIsbn(const std::string& isbn);  // возвращает указатель или nullptr
    
    // Выдача/возврат
    bool borrowBook(const std::string& isbn);
    bool returnBook(const std::string& isbn);
    
    // Просмотр
    void printAll() const;
    void printAvailable() const;
    
    // Статистика
    int getTotalCount() const;
    int getBorrowedCount() const;
};

#endif