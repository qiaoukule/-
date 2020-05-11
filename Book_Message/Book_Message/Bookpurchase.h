#pragma once
#include"Book.h"
class Book;
class BookPurchase:public Book {
private:
	int PhoneNumber;
	int password;
public:
	BookPurchase() {};
	~BookPurchase() {};
	void Log(); //µÇÂ¼
	void BeMembers();  //×¢²á
	void PurchaseBook();  //¹ºÂò
	void IsCustomers();  
};