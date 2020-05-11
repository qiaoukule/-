#pragma once
#include<string>
using namespace std;

class Book {
protected:
	string name;
	string press;  //出版社
	string isbn;
	string author;
	int inventory;  //库存量
	float price;
public:
	Book(){};  //构造函数
	Book(string Name, string Press, string ISBN, string Author, int Inventory, float Price) ;//带参构造函数
	void setName(string Name);
	string getName();
	void setPress(string Press);
	string getPress();
	const void setISBN(string ISBN);
	const string getISBN();
	void setAthour(string Author);
	string getAuthor() ;
	void setInventory(int Inventory) ;
	int  getInventory() ;
	void setPrice(float Price) ;   
	float getPrice() ;  
	bool Record() ;//统一输入信息，就是进新书了
	void writeData(Book book);
	void inputOneBook(Book book);  //输出一本书的信息，方便查看书籍信息
	void ModifyOne(Book book);    //修改一本书的内容
	bool judgeInventory(int i);   //判断书籍时判断库存量是否大于0
	void countToatl();   //统计所有书的库存量总数
	void sort();    //可以用于以价格和库存量从大到小的排序以及按书籍名称/作者/出版社来查找书籍
};
