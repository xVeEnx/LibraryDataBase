#include "Library.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
using namespace LibraryNamespaces;
namespace {
constexpr auto BOOKSFILENAME = "books.txt";
constexpr auto MEMBERSFILENAME = "librarymembers.txt";
constexpr auto TYPESFILENAME = "types.txt";
std::string toLowerCase(const std::string &str);
bool equals(const std::string& str,const std::string& str2);
bool hasIllegalSigns(const std::string& str) {
  for (auto &c : str) {
    if (c == '/' || c == SEPARATOR[0] || c == '\\') {
     error("ILLEGAL SYMBOLS IN NAME TYPE OTHER NAME!");
      return true;
    }
  }
  return false;
}
bool checkIfExit(const std::string& str){
  if (equals(str, "exit")) {
    std::cout << "You decided to leave" << std::endl;
    return true;
  }
  return false;
}
bool checkIfExit(int number) {
  if (number == -1) {
    std::cout << "You decided to leave" << std::endl;
    return true;
  }
  return false;
}
std::string parseString(const std::string &stringToShow) {
  std::string choose = "";
  bool hasIllegal;
  do {
    std::cout  <<"\nIf you want to leave type exit" << std::endl;
    std::cout << stringToShow;
    std::getline(std::cin, choose);
    hasIllegal = false;
    if (hasIllegalSigns(choose)) {
      hasIllegal = true;
     error("ILLEGAL SIGN. TRY AGAIN!");
    }
  } while (hasIllegal);
  return choose;
}
int parseInt(const std::string &stringToShow) {
  std::string choose = "-1";
  std::cout << "\nIf you want to leave type -1" << std::endl;
  int convertedToInt = -1;
  do {
    std::cout << stringToShow;
    std::getline(std::cin, choose);
    std::istringstream iss(choose);
    iss >> convertedToInt;
    if (convertedToInt < -1)
     error("NUMBER MUST BE GRATER THAN ZERO. TRY AGAIN!");
    if (convertedToInt >=300)
       error("300 IS THE BIGGEST NUMBER YOU CAN PASS!!");
  } while (convertedToInt < -1||convertedToInt>=300);
  return convertedToInt;
}

std::string toLowerCase(const std::string &str) {
  std::string tempStr = "";
  for (auto &c : str) {
      tempStr += std::tolower(c);
  }
  return tempStr;
}
void validateFile(std::fstream &file,std::string fileName) {
  while (!file.good()) {
    std::ifstream iFile;
    iFile.open(fileName);
    if (!(iFile)) {
      std::ofstream createFile(fileName);
      createFile.close();
      file.open(fileName, std::ios::in | std::ios::out | std::ios::ate);
    } else {
      std::ostringstream text;
      text << "CHECK FILE: " << fileName << " !!!";
     error(text.str());
      abort();
    }
  }
}
bool equals(const std::string& str,const std::string& str2) {
  std::string tempStr = toLowerCase(str);
  std::string tempStr2 = toLowerCase(str2);
  if (tempStr == tempStr2)
    return true;

  return false;
}
void clearFile(std::fstream &file, std::string fileName) {
  file.close();
  file.open(fileName, std::ios::out | std::ios::trunc);
  file.close();
  file.open(fileName, std::ios::in | std::ios::out | std::ios::ate);
  validateFile(file, fileName);
}

int getIndex(std::vector<Book> books) {
  while (true) {
    int choose = parseInt("Choose ID of book that member wants to buy");
    if (checkIfExit(choose))
      return -1;
    for (std::vector<Book>::iterator booksIterator = books.begin();
         booksIterator != books.end(); booksIterator++) {
      if (choose == booksIterator->getBookID()) {
        return std::distance(books.begin(), booksIterator);
      }
    }
  }
}
int getIndex(std::vector<LibraryMember> member) {
  while (true) {
    const int choose = parseInt("Choose ID of book that member wants to buy");
    if (checkIfExit(choose))
      return -1;
    for (std::vector<LibraryMember>::iterator iterator = member.begin();
         iterator != member.end(); iterator++) {
      if (choose == iterator->getMemberID()) {
        return std::distance(member.begin(), iterator);
      }
    }
  }
}
int getIndexFromString(std::vector<Book> books,const std::string bookName) {
  for (std::vector<Book>::iterator booksIterator = books.begin();
       booksIterator != books.end(); booksIterator++) {
    if (equals(bookName, booksIterator->getbookName())) {
      return std::distance(books.begin(), booksIterator);
    }
  }
  return -1;
}
int getIndexFromString(std::vector<std::string> books,std::string *name) {
  while (true) {
    const std::string bookName =
        parseString("Choose name of book that will be returned");
    for (std::vector<std::string>::iterator booksIterator = books.begin();
         booksIterator != books.end(); booksIterator++) {
      if (equals(bookName, *booksIterator)) {
        *name = bookName;
        return std::distance(books.begin(), booksIterator);
      }
    }
  }
}

} 
Library::Library() {
  memberFile = std::fstream();
  memberFile.open(MEMBERSFILENAME,
                  std::ios::in | std::ios::out | std::ios::ate);
  validateFile(memberFile, MEMBERSFILENAME);

  booksFile = std::fstream();
  booksFile.open(BOOKSFILENAME, std::ios::in | std::ios::out | std::ios::ate);
  validateFile(booksFile, BOOKSFILENAME);

  typesFile = std::fstream();
  typesFile.open(TYPESFILENAME, std::ios::in | std::ios::out | std::ios::ate);
  validateFile(typesFile, TYPESFILENAME);

  readOperation(memberFile, libraryMembers);
  readOperation(booksFile, books);
  readOperation(typesFile, types);
     enum class usersChoose {
    allLibraryMembers = 1,
    allBookTypes = 2,
    allBooksOrChosenType = 3,
    memberAdd = 4,
    bookAdd = 5,
    bookTypeAdd = 6,
    bookToMemberAdd = 7,
    bookFromMemberDel = 8,
    exit = -1
  };
  while (true) {
    std::cout << "Welcome in Library Data Base, choose what you want to do:"
              << std::endl;
    std::cout << "1 - Show all library members" << std::endl;
    std::cout << "2 - Show all book types" << std::endl;
    std::cout << "3 - Show all Books or books of chosen type" << std::endl;
    std::cout << "4 - Add library member" << std::endl;
    std::cout << "5 - Add book" << std::endl;
    std::cout << "6 - Add book type" << std::endl;
    std::cout << "7 - Add book to member" << std::endl;
    std::cout << "8 - Delete book from member" << std::endl;

    const int choosenOption = parseInt("");
    const usersChoose k = static_cast<usersChoose>(choosenOption);
    switch (k) {
    case usersChoose::allLibraryMembers: {
      showAllLibraryMembers();
      break;
    }
    case usersChoose::allBookTypes: {
      showAllTypes();
      break;
    }
    case usersChoose::allBooksOrChosenType: {
      std::ostringstream text;
      text << "You want to see all books, or only these of choosen type?"
           << std::endl
           << "1. All books: " << std::endl
           << "2. Books of choosen type:" << std::endl;
      const int choose = parseInt(text.str());
      if (choose == 2) {
        showAllTypes();
        const int typeID = parseInt("Choose ID of type that you want to see");
        showBooksOfSelectedType(typeID);
      } else if (checkIfExit(choose))
        break;
      else
        showAllBooks();
      break;
    }
    case usersChoose::memberAdd: {
      addMember();
      saveMemberInFile(libraryMembers.back());
      break;
    }
    case usersChoose::bookAdd: {
      addBook();
      saveBookInFile(books.back());
      break;
    }
    case usersChoose::bookTypeAdd: {
      addBookType();
      saveTypeInFile(types.back());
      break;
    }
    case usersChoose::bookToMemberAdd: {
      addBookToMember();
      break;
    }
    case usersChoose::bookFromMemberDel: {
      deleteBookFromMember();
      break;
    }
    case usersChoose::exit: {
      return;
      break;
    }
    default: {
      break;
    }
    }
  }
}
void Library::addMember() {
  const std::string newMemberName=parseString("Name and surname of new member: ");
  if (checkIfExit(newMemberName))return;
  const std::string newMemberPostal = parseString("Postal adress of new member: ");
  if (checkIfExit(newMemberPostal))return;
  const std::string newMemberAdress = parseString("Adress of new meber: ");
  if (checkIfExit(newMemberAdress)) return;
  std::vector<std::string> booksVect;
  libraryMembers.push_back(LibraryMember(libraryMembers.size(), newMemberName,
                                         newMemberPostal, newMemberAdress, 0,
                                         booksVect));
}
void Library::saveMemberInFile(const LibraryMember& currentMember) {
  const std::string text = makeText(currentMember, 0);
  saveOperation(memberFile, text);
}
Library::~Library() {
  memberFile.close();
  typesFile.close();
  booksFile.close();
}
void Library::showAllLibraryMembers() {
  for (auto &membersIterator : libraryMembers) {
      membersIterator.showLibraryMembers();
  }
}
void Library::showAllTypes() {
  for (auto & typesIterator : types) {
      typesIterator.showType();
  }
}
void Library::addBook() {
  const std::string newBookName = parseString("Name of book: ");
  if (checkIfExit(newBookName))
    return;
  showAllTypes();
  int newBookTypeID;
  std::string newBookType;
  bool endOfLoop = true;
  while (endOfLoop) {
    newBookTypeID = parseInt("Choose ID of book type : ");
    if (checkIfExit(newBookTypeID))
      return;
    for (auto &typeIterator : types) {
      if (newBookTypeID == typeIterator.getTypeID()) {
        newBookType = typeIterator.getTypeName();
        endOfLoop = false;
        break;
      }
    }
  }
  const int numberOfBooks = parseInt("Number of books");
  if (checkIfExit(numberOfBooks))
    return;
  books.push_back(
      Book(books.size(), newBookName, newBookType, numberOfBooks, 0));
}
void Library::saveBookInFile(const Book& currentBook) {
  std::string text;
  text = std::to_string(currentBook.getBookID());
  text += SEPARATOR + currentBook.getbookName() + SEPARATOR +
          currentBook.getBookType() + SEPARATOR +
          std::to_string(currentBook.getNumberOfBooks()) + SEPARATOR +
          std::to_string(currentBook.getNumberOfBorrowedBooks()) + SEPARATOR;
  saveOperation(booksFile, text);
}
void Library::showAllBooks() {
  for (auto &booksIterator : books) {
      booksIterator.showBook();
  }
}
void Library::addBookType() {
  std::string newTypeName, newTypeDescription;
  newTypeName = parseString("Type name: ");
  if (checkIfExit(newTypeName))
    return;
  newTypeDescription = parseString("Type description: ");
  if (checkIfExit(newTypeDescription))
    return;
  types.push_back(BookType(types.size(), newTypeName, newTypeDescription));
}
void Library::saveTypeInFile(const BookType& currentType) {
  std::ostringstream text;
  text << std::to_string(currentType.getTypeID()) << SEPARATOR
       << currentType.getTypeName() << SEPARATOR
       << currentType.getTypeName() << SEPARATOR
       << currentType.getTypeDescription() << SEPARATOR;
  saveOperation(typesFile, text.str());
}
void Library::saveOperation(std::fstream &file, std::string text) {
  file.clear();
  if (file.is_open()) {
    file << text;
    if (file.fail()) {
      error("CHECK FILE!");
      file.clear();
    }
    file << "\n";
  } else
    error("CHECK FILE!");
  file.flush();
}
template <typename T>
void Library::readOperation(std::fstream &file, std::vector<T> vect) {
  file.seekg(0, std::ios::beg);
  if (file.is_open()) {
    if (file.fail()) {
      error("CHECK FILE!");
      file.clear();
      return;
    } else {
      std::string line;
      if (std::is_same<T, Book>::value) {
        while (std::getline(file, line)) {
          if (line == " " || line == "")
            continue;
          books.push_back(Book::readBooksFromFile(line));
        }
      }
      if (std::is_same<T, LibraryMember>::value) {
        while (std::getline(file, line)) {
          if (line == " " || line == "")
            continue;
          libraryMembers.push_back(LibraryMember::readMemberFromFile(line));
        }
      }
      if (std::is_same<T, BookType>::value) {
        while (std::getline(file, line)) {
          if (line == " " || line == "")
            continue;
          types.push_back(BookType::readTypesFromFile(line));
        }
      }
    }
  }
}
void Library::showBooksOfSelectedType(const int typeID) {
   std::string type /*= SEPARATOR*/;
  for (auto &typesIterator : types)
    if (typesIterator.getTypeID() == typeID)
      type = typesIterator.getTypeName();

   if (type != SEPARATOR) {
    std::cout << "Books of selected category: " << std::endl;
    for (auto &booksIterator : books)
      if (equals(booksIterator.getBookType(), type))
        booksIterator.showBook();
   }
}
void Library::addBookToMember() {
  showAllLibraryMembers();
  int memberIndex, booksAmount;
  memberIndex = getIndex(libraryMembers);
  if (checkIfExit(memberIndex))
    return;
  showAllBooks();
  int bookIndex = getIndex(books);
  if (checkIfExit(memberIndex))
    return;
  LibraryMember *currentMember = &libraryMembers[memberIndex];
  Book *currentBook = &books[bookIndex];

  if (currentBook->getNumberOfBooks() < 1) {
    error("THERE ARE NO MORE BOOKS LEFT");
    return;
  }
  int booksAvailable = currentBook->getNumberOfBooks();
  std::ostringstream text;
  text << "Choose amount of book that member wants to buy - there is "
       << booksAvailable << "books available";
  booksAmount = parseInt(text.str());
  if (checkIfExit(booksAmount))
    return;
  while (booksAmount > booksAvailable) {
    booksAmount = parseInt("error TYPE CORRECT AMOUNT! ");
    if (checkIfExit(booksAmount))
      return;
  }
  if (booksAmount > 0) {
    currentMember->bookWasBorrowed(booksAmount, *currentBook);
    currentBook->bookWasBorrowed(booksAmount);
    clearFile(memberFile, MEMBERSFILENAME);
    for (auto &membersVect : libraryMembers) {
      saveMemberInFile(membersVect);
    }
    clearFile(booksFile, BOOKSFILENAME);
    for (auto &booksVect : books) {
      saveBookInFile(booksVect);
    }
  } else
    std::cout << "Number of books must be greater than 0" << std::endl;
}
std::string Library::makeText(LibraryMember currentMember, int bookIndex) {
  std::ostringstream tempst;
  tempst << std::to_string(currentMember.getMemberID()) << SEPARATOR
         << currentMember.getMemberName() << SEPARATOR
         << currentMember.getMemberPostalAdress() << SEPARATOR
         << currentMember.getMemberAdress() << SEPARATOR
         << std::to_string(currentMember.getBooksToBack().size()) << SEPARATOR;
  for (int i = 0; i < currentMember.getBooksToBack().size(); i++) {
    tempst << currentMember.getBooksToBack()[i] + SEPARATOR;
  }
  return tempst.str();
}
void Library::deleteBookFromMember() {
  int indexOfMember;
  showAllLibraryMembers();
  do {
    indexOfMember = getIndex(libraryMembers);
    if (checkIfExit(indexOfMember))
      return;
    continue;
  } while (libraryMembers[indexOfMember].getBooksToBack().size() < 1);

  LibraryMember *currentMember = &(libraryMembers[indexOfMember]);
  currentMember->showBooksOfMember();

  std::string bookName;
  int index = getIndexFromString(currentMember->getBooksToBack(), &bookName);
  if (checkIfExit(indexOfMember))
    return;
  int indexInBooks = getIndexFromString(books, bookName);
  if (checkIfExit(indexOfMember))
    return;

  currentMember->bookIsBack(index);
  books[indexInBooks].bookIsBack();

  clearFile(memberFile, MEMBERSFILENAME);
  for (auto& membersIterator : libraryMembers)
    saveMemberInFile(membersIterator);

  clearFile(booksFile, BOOKSFILENAME);
  for (auto &booksIterator:books)
    saveBookInFile(booksIterator);
}
