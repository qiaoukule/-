#pragma once
#include"Book.h"
class Book;
class BookManagment :public Book {
public:   
	BookManagment() {};
	~BookManagment() {};
	bool Identify(); //��֤���
	void Modify();  //�޸��鼮����
	void deletebook();  //ɾ���鼮����
	void IsMamagment(); //�������̲���
};

