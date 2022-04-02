#pragma once
#include "Book.h"
#include <iostream>
#include <string>
#include "LibraryNamespaces.h"
class BookType {
public:
  BookType(int id, std::string name, std::string description);
  std::string getTypeName() const;
  std::string getTypeDescription()const;
  int getTypeID()const;
  static BookType readTypesFromFile(std::string &line);
  void showType()const;

private:
  const int typeID;
  std::string nameOfType;
  std::string typeDescription;
};
