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
	void Log(); //��¼
	void BeMembers();  //ע��
	void PurchaseBook();  //����
	void IsCustomers();  
};