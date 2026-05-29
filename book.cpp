#include "Book.h"
#include <iostream>

Book::Book(const std::string& title, const std::string& author, 
           int year, const std::string& isbn)
    : title(title), author(author), year(year), isbn(isbn), isBorrowed(false) {
    // Список инициализации выше — это современный C++ способ
}

std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getYear() const { return year; }
std::string Book::getIsbn() const { return isbn; }
bool Book::getIsBorrowed() const { return isBorrowed; }

void Book::borrow() {
    if (!isBorrowed) {
        isBorrowed = true;
        std::cout << "Книга \"" << title << "\" выдана на руки.\n";
    } else {
        std::cout << "Книга \"" << title << "\" уже выдана.\n";
    }
}

void Book::returnBook() {
    if (isBorrowed) {
        isBorrowed = false;
        std::cout << "Книга \"" << title << "\" возвращена.\n";
    } else {
        std::cout << "Книга \"" << title << "\" и так в библиотеке.\n";
    }
}

void Book::print() const {
    std::cout << title << " | " << author << " | " << year 
              << " | " << (isBorrowed ? "Выдана" : "В наличии") << "\n";
}