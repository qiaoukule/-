#pragma once
#include<string>
using namespace std;

class Book {
protected:
	string name;
	string press;  //������
	string isbn;
	string author;
	int inventory;  //�����
	float price;
public:
	Book(){};  //���캯��
	Book(string Name, string Press, string ISBN, string Author, int Inventory, float Price) ;//���ι��캯��
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
	bool Record() ;//ͳһ������Ϣ�����ǽ�������
	void writeData(Book book);
	void inputOneBook(Book book);  //���һ�������Ϣ������鿴�鼮��Ϣ
	void ModifyOne(Book book);    //�޸�һ���������
	bool judgeInventory(int i);   //�ж��鼮ʱ�жϿ�����Ƿ����0
	void countToatl();   //ͳ��������Ŀ��������
	void sort();    //���������Լ۸�Ϳ�����Ӵ�С�������Լ����鼮����/����/�������������鼮
};
