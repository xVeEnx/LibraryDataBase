#include "Book.h"
#include <iostream>
#include <string>
using namespace LibraryNamespaces;
Book::Book(int id, std::string name, std::string type, int number, int borrowed)
    : bookID{id}, bookName{name}, bookType{type}, numberOfBooks{number},
      borrowedBooks{borrowed} {}
int Book::getBookID()const { return bookID; }
std::string Book::getbookName() const { return bookName; }
std::string Book::getBookType() const { return bookType; }
int Book::getNumberOfBooks()const { return numberOfBooks; }
int Book::getNumberOfBorrowedBooks()const { return borrowedBooks; }
Book Book::readBooksFromFile(const std::string& line) {
  std::string tempLine = line;

  try {
       const auto id = stoi(getNextValue(&tempLine));
       const auto name = getNextValue(&tempLine);
       const auto type = getNextValue(&tempLine);
       const auto books = stoi(getNextValue(&tempLine));
       const auto borrowed = stoi(getNextValue(&tempLine));
      return Book(id, name, type, books, borrowed);
      return Book(0,"","",0,0);
  }
  catch (const std::exception& e)
  {
      error("ERROR WITH NUMBER!!!!. ERROR CODE: ");
      std::cout << e.what();
  }
}
void Book::showBook() const {
  std::cout << "ID: " << bookID;
  std::cout << " Name: " << bookName << std::endl;
  std::cout << "Type: " << bookType << std::endl;
  std::cout << "Number of books: " << numberOfBooks << std::endl;
  std::cout << "Number of books borrowed: " << borrowedBooks << std::endl;
  std::cout << std::endl;
}
void Book::bookWasBorrowed(const int numberOfBorrowedBooks) {
  borrowedBooks += numberOfBorrowedBooks;
  numberOfBooks -= numberOfBorrowedBooks;
}

void Book::bookIsBack() {
  numberOfBooks++;
  borrowedBooks--;
}
