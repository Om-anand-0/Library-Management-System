#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Book {
public:
    int id;
    std::string title;
    std::string author;
    bool isIssued;

    Book(int id, std::string title, std::string author)
        : id(id), title(title), author(author), isIssued(false) {}

    void display() const {
        std::cout << "ID: " << id << ", Title: " << title << ", Author: " << author 
                  << ", " << (isIssued ? "Issued" : "Available") << std::endl;
    }
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(int id, const std::string& title, const std::string& author) {
        books.emplace_back(id, title, author);
        std::cout << "Book added: " << title << std::endl;
    }

    void removeBook(int id) {
        auto it = std::remove_if(books.begin(), books.end(), [id](const Book& book) {
            return book.id == id;
        });
        if (it != books.end()) {
            std::cout << "Book removed: " << it->title << std::endl;
            books.erase(it, books.end());
        } else {
            std::cout << "Book not found with ID: " << id << std::endl;
        }
    }

    void issueBook(int id) {
        for (auto& book : books) {
            if (book.id == id) {
                if (!book.isIssued) {
                    book.isIssued = true;
                    std::cout << "Book issued: " << book.title << std::endl;
                } else {
                    std::cout << "Book is already issued: " << book.title << std::endl;
                }
                return;
            }
        }
        std::cout << "Book not found with ID: " << id << std::endl;
    }

    void returnBook(int id) {
        for (auto& book : books) {
            if (book.id == id) {
                if (book.isIssued) {
                    book.isIssued = false;
                    std::cout << "Book returned: " << book.title << std::endl;
                } else {
                    std::cout << "Book was not issued: " << book.title << std::endl;
                }
                return;
            }
        }
        std::cout << "Book not found with ID: " << id << std::endl;
    }

    void displayBooks() const {
        std::cout << "Library Books:" << std::endl;
        for (const auto& book : books) {
            book.display();
        }
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Remove Book\n";
        std::cout << "3. Issue Book\n";
        std::cout << "4. Return Book\n";
        std::cout << "5. Display Books\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 6) {
            break;
        }

        switch (choice) {
            case 1: {
                int id;
                std::string title, author;
                std::cout << "Enter book ID: ";
                std::cin >> id;
                std::cin.ignore(); // Ignore newline left in the buffer
                std::cout << "Enter book title: ";
                std::getline(std::cin, title);
                std::cout << "Enter book author: ";
                std::getline(std::cin, author);
                library.addBook(id, title, author);
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter book ID to remove: ";
                std::cin >> id;
                library.removeBook(id);
                break;
            }
            case 3: {
                int id;
                std::cout << "Enter book ID to issue: ";
                std::cin >> id;
                library.issueBook(id);
                break;
            }
            case 4: {
                int id;
                std::cout << "Enter book ID to return: ";
                std::cin >> id;
                library.returnBook(id);
                break;
            }
            case 5: {
                library.displayBooks();
                break;
            }
            default: {
                std::cout << "Invalid choice, please try again." << std::endl;
                break;
            }
        }
    }

    return 0;
}
