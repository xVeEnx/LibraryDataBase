#pragma once
#include "Book.h"
#include "BookType.h"
#include "LibraryMember.h"
#include <fstream>
#include <vector>
#include "LibraryNamespaces.h"
class Library {
public:
  Library();
  ~Library();
private:
  void addMember();
  void addBook();
  void addBookType();
  void showAllLibraryMembers();
  void showAllBooks();
  void showAllTypes();
  void addBookToMember();
  void deleteBookFromMember();
  void saveMemberInFile(const LibraryMember& currentMember);
  void saveBookInFile(const Book& currentBook);
  void saveTypeInFile(const BookType& currentType);
  void showBooksOfSelectedType(const int typeID);
  template <typename T>
  void readOperation(std::fstream& file, std::vector<T> vect);
  void saveOperation(std::fstream& file, std::string text);
  std::string makeText(LibraryMember currentMember, int bookIndex);
  std::fstream memberFile;
  std::fstream booksFile;
  std::fstream typesFile;
  std::vector<LibraryMember> libraryMembers;
  std::vector<Book> books;
  std::vector<BookType> types;
};
