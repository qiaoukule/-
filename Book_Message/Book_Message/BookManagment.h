#pragma once
#include"Book.h"
class Book;
class BookManagment :public Book {
public:   
	BookManagment() {};
	~BookManagment() {};
	bool Identify(); //认证身份
	void Modify();  //修改书籍操作
	void deletebook();  //删除书籍操作
	void IsMamagment(); //管理流程操作
};

