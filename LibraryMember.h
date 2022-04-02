#pragma once
#include <iostream>
#include <vector>
#include "Book.h"
#include "LibraryNamespaces.h"
class LibraryMember
{
public:
	LibraryMember(const int memberId, const std::string& name,
		const std::string& postalAdress, const std::string& adress,
		const int _booksBorrowed, std::vector<std::string> _booksToBack);
	static LibraryMember readMemberFromFile(const std::string& line);
	int getMemberID()const;
	std::string getMemberName()const;
	std::string getMemberPostalAdress()const;
	std::string getMemberAdress()const;
	std::vector<std::string>getBooksToBack()const;
	void showLibraryMembers()const;
	void bookWasBorrowed(const int numberOfBorrowedBooks, const Book& borrowedBook);
	void showBooksOfMember()const;
	void bookIsBack(const int index);
private:
	const int memberID;
	const std::string memberName;
	const std::string memberPostalAdress;
	const std::string memberAdress;
	int booksBorrowedAmount;
	std::vector<std::string> booksToBackNames;
};

