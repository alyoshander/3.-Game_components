#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    int year;
    std::string isbn;
    bool isBorrowed;  // true = на руках, false = в библиотеке

public:
    // Конструктор
    Book(const std::string& title, const std::string& author, 
         int year, const std::string& isbn);
    
    // Геттеры (только чтение)
    std::string getTitle() const;
    std::string getAuthor() const;
    int getYear() const;
    std::string getIsbn() const;
    bool getIsBorrowed() const;
    
    // Действия
    void borrow();   // выдать на руки
    void returnBook(); // вернуть в библиотеку
    
    // Для отладки
    void print() const;
};

#endif