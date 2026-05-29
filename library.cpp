#include "Library.h"
#include <iostream>
#include <algorithm>

void Library::addBook(const Book& book) {
    books.push_back(book);
    std::cout << "Книга добавлена.\n";
}

bool Library::removeBook(const std::string& isbn) {
    auto it = std::find_if(books.begin(), books.end(), 
        [&isbn](const Book& b) { return b.getIsbn() == isbn; });
    
    if (it != books.end()) {
        books.erase(it);
        std::cout << "Книга удалена.\n";
        return true;
    }
    std::cout << "Книга с ISBN " << isbn << " не найдена.\n";
    return false;
}

std::vector<Book> Library::findByAuthor(const std::string& author) const {
    std::vector<Book> result;
    for (const auto& book : books) {
        if (book.getAuthor() == author) {
            result.push_back(book);
        }
    }
    return result;
}

Book* Library::findByIsbn(const std::string& isbn) {
    for (auto& book : books) {
        if (book.getIsbn() == isbn) {
            return &book;
        }
    }
    return nullptr;
}

bool Library::borrowBook(const std::string& isbn) {
    Book* book = findByIsbn(isbn);
    if (book && !book->getIsBorrowed()) {
        book->borrow();
        return true;
    }
    std::cout << "Книга не найдена или уже выдана.\n";
    return false;
}

bool Library::returnBook(const std::string& isbn) {
    Book* book = findByIsbn(isbn);
    if (book && book->getIsBorrowed()) {
        book->returnBook();
        return true;
    }
    std::cout << "Книга не найдена или не была выдана.\n";
    return false;
}

void Library::printAll() const {
    std::cout << "\n=== Все книги ===\n";
    for (const auto& book : books) {
        book.print();
    }
}

void Library::printAvailable() const {
    std::cout << "\n=== Книги в наличии ===\n";
    for (const auto& book : books) {
        if (!book.getIsBorrowed()) {
            book.print();
        }
    }
}

int Library::getTotalCount() const {
    return books.size();
}

int Library::getBorrowedCount() const {
    int count = 0;
    for (const auto& book : books) {
        if (book.getIsBorrowed()) count++;
    }
    return count;
}