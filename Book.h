#pragma once
#include <iostream>
#include "LibraryNamespaces.h"

class Book {
public:
  Book(int id, std::string name, std::string type, int number, int borrowed);
  static Book readBooksFromFile(const std::string& line);
  int getBookID()const;
  std::string getbookName()const;
  std::string getBookType()const;
  int getNumberOfBooks()const;
  int getNumberOfBorrowedBooks()const;
  void showBook()const;
  void bookWasBorrowed(const int numberOfBorrowedBooks);
  void bookIsBack();

private:
  const int bookID;
  const std::string bookName;
  const std::string bookType;
  int numberOfBooks;
  int borrowedBooks;
};
