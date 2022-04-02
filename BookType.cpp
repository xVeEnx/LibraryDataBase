#include "BookType.h"
using namespace LibraryNamespaces;

BookType::BookType(int id, std::string name, std::string description)
    : typeID{id}, nameOfType{name}, typeDescription{description} {}
std::string BookType::getTypeName()const { return nameOfType; }
std::string BookType::getTypeDescription()const { return typeDescription; }
int BookType::getTypeID()const { return typeID; }
BookType BookType::readTypesFromFile(std::string &line) {
    std::string tempLine = line;
    try {
        int id = std::stoi(getNextValue(&tempLine));
        std::string name = getNextValue(&tempLine);
        std::string description = getNextValue(&tempLine);
        return BookType(id, name, description);
        return BookType(0,"","");
    }
    catch (const std::exception& e)
    {
       error("ERROR WITH NUMBER!!!!. ERROR CODE: ");
        std::cout << e.what();
    }
            return BookType(0,"","");

}
void BookType::showType() const {
  std::cout << "ID: " << typeID<<" ";
  std::cout << " Name: " << nameOfType << std::endl;
  std::cout << "Description: " << typeDescription << std::endl;
}
