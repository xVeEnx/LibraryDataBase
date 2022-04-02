#include "LibraryMember.h"
#include "Book.h"
#include <iostream>
#include <string>
using namespace LibraryNamespaces;

LibraryMember::LibraryMember(const int memberId,const std::string& name,
	const std::string& postalAdress, const std::string& adress,
	const int _booksBorrowed,
	std::vector<std::string> _booksToBack)
	: memberID(memberId), memberName(name), memberPostalAdress(postalAdress),
	memberAdress(adress), booksBorrowedAmount{ _booksBorrowed }, booksToBackNames{
															 _booksToBack } {}
void LibraryMember::showBooksOfMember() const {
	std::cout << "Books borrowed:" << std::endl;
	for (auto &booksIterator:booksToBackNames) {
		std::cout << booksIterator << std::endl;
	}
}
std::string LibraryMember::getMemberName() const { return memberName; }
std::string LibraryMember::getMemberPostalAdress() const {
	return memberPostalAdress;
}
std::string LibraryMember::getMemberAdress()const { return memberAdress; }
int LibraryMember::getMemberID() const { return memberID; }
std::vector<std::string> LibraryMember::getBooksToBack()const { return booksToBackNames; }
void LibraryMember::showLibraryMembers()const {
	std::cout << "ID: " << getMemberID();
	std::cout << "Name: " << getMemberName() << std::endl;
	std::cout << "Postal adress: " << getMemberPostalAdress() << std::endl;
	std::cout << "Adress: " << getMemberAdress() << std::endl;
	std::cout << "Number of books borrowed: " << getBooksToBack().size()
		<< std::endl;
	showBooksOfMember();
	std::cout << std::endl;
}

LibraryMember LibraryMember::readMemberFromFile(const std::string& line) {
	std::string tempLine = line;
	 std::string name, postalAdress, adress;
	 int id, numberOfBooks;
	try {
		  id = stoi(getNextValue(&tempLine));
		  name = getNextValue(&tempLine);
		  postalAdress = getNextValue(&tempLine);
		  adress = getNextValue(&tempLine);
		  numberOfBooks = stoi(getNextValue(&tempLine));
	}
	catch (const std::exception& e)
	{
		error("ERROR WITH NUMBER!!!!. ERROR CODE: ");
		std::cout << e.what();
	}
	std::vector<std::string> vectorOfBorrowed;
	for (int i = 0; i < numberOfBooks; i++) {
		vectorOfBorrowed.push_back(getNextValue(&tempLine));
	}
	return LibraryMember(id, name, postalAdress, adress, numberOfBooks,
		vectorOfBorrowed);
}
void LibraryMember::bookWasBorrowed(const int numberOfBorrowedBooks,const Book& borrowedBook) {
	booksBorrowedAmount += numberOfBorrowedBooks;
	for (int i = 0; i < numberOfBorrowedBooks; i++)
		booksToBackNames.push_back(borrowedBook.getbookName());
}
void LibraryMember::bookIsBack(const int index) {
	booksToBackNames.erase(std::next(booksToBackNames.begin(), index));
	booksBorrowedAmount--;
}
