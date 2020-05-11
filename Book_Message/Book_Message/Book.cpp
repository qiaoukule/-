#include "pch.h"
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<ostream>
#include"Book.h"
using namespace std;

//����ͼ�����������ʱ��¼�����������Ϣ
Book::Book(string Name, string Press, string ISBN, string Author, int Inventory, float Price) {
	name=Name;
	press= Press;
	isbn=ISBN;
	author=Author;
	inventory = Inventory;
	price = Price;
}


void Book::setName(string Name) {
	name=Name;  
}
string Book::getName() {
	return name; 
}
const void Book::setISBN(string ISBN) {
	isbn= ISBN;
}
const string Book::getISBN() {
	return isbn;
}
void Book::setPress(string Press) {
	press= Press;
}
string Book::getPress() {
	return press;
}
void Book::setAthour(string Author) {
	author=Author;
}
string Book::getAuthor() {
	return author;
}
float Book::getPrice() {
	return price;
}
void Book::setPrice(float Price) {
	price = Price;
}
void Book::setInventory(int Inventory){
	inventory = Inventory;
}
int Book::getInventory() {
	return inventory;
}

//¼������ʱ���鼮��Ϣд���ļ���
void Book::writeData(Book book) {
	ofstream outFile;  //�����ļ�����
	outFile.open("book.txt",ios::binary | ios::app);  //���ļ�
	if (!outFile)
	{  //�ļ���ʧ��
		cout << "����ʧ�ܣ��ļ���ʧ�ܣ�";
		exit(1);
	}
	outFile << book.getName() << "   " << book.getISBN() << "   " << book.getAuthor() << "   "
		<< book.getPress() << "   " << book.getPrice() << "  " << book.getInventory() << endl;  //д���ļ�
	outFile.close();  //�ر��ļ�
}

//�޸��鼮��Ϣ
void Book::ModifyOne(Book book) {
	cout << "*****�޸�ͼ����Ϣ*****" << endl;
	cout << "�鼮���ƣ�����Ҫ�����ţ���";
	string name;
	cin >> name;   
	book.setName(name);
	/*cout << "ISBN:";  //��֤isbnΨһ
	string isbn;
	cin >> isbn;*/  
	cout << "������(��������)��";
	string press;
	cin >> press;
	book.setPress(press);
	cout << "���ߣ�";
	string author;
	cin >> author;
	book.setAthour(author);
	cout << "�������";
	int inventory;
	cin >> inventory;
	book.setInventory(inventory);
	cout << "���ۼ۸�";
	float price;
	cin >> price;
	book.setPrice(price);
}

//¼��һ���½��ݵ���
bool Book::Record() {
	char x;   //����ȫ�ֱ���x,���ں����Ƿ����¼����ж�
	do {
		cout << "*****¼��ͼ����Ϣ*****" << endl;
		cout << "�鼮���ƣ�����Ҫ�����ţ���";
		string name;
		cin >> name;   
		cout << "ISBN:";
		string isbn;
		cin >> isbn;
		//do...while...�ж�isbn�Ƿ��ظ�
		ifstream outFile("book.txt");
		do{
			string s;
			getline(outFile, s);//����ÿһ��
			istringstream sin(s);
			string a, b, c, d; int i; float k;
			sin >> a >> b >> c >> d >> i >> k;
			if (d == isbn) {            //����ظ����������ʾ�����ز���������
				cout << " ISBN���ظ��� " << endl;
				return false;
			}
		}while (outFile.peek() != EOF);
		outFile.close();
		//ISBNδ�ظ�����������Ϣ
		cout << "������(��������)��";
		string press;
		cin >> press;
		cout << "���ߣ�";
		string author;
		cin >> author;
		cout << "�������";
		int inventory;
		cin >> inventory;
		cout << "���ۼ۸�";
		float price;
		cin >> price;
		Book newbook(name, isbn, press, author, inventory, price);  //���ù��캯�����ν����ݷ���
		writeData(newbook);   //д���ļ�
		cout << "�Ƿ����¼��������Ϣ���ǣ�Y/y��,��N/n��";
		cin >> x;
	} while (x == 'Y' || x == 'y');  //������Y/yʱ������ִ��do������
	return true;
}

//inputOneBook���һ��������ݣ�����ȷ����Ϣ
void  Book::inputOneBook(Book book) {
	cout << "�鼮���ƣ�" << book.name << endl;
	cout << "    ISBN��" << book.isbn << endl;
	cout << "  �����磺" << book.press << endl;
	cout << "    ���ߣ�" << book.author << endl;
	cout << "  �������" << book.inventory << endl;
	cout << "���ۼ۸�" << book.price << endl;
	cout << "--------------------------------------------------------" << endl;
}


bool Book::judgeInventory(int i) {  
	if (i <= 0) {      //��������С�ڻ����0 ����������� false
		return false;
	}
	if (i > 0) {
		return true;
	}
}

void Book::countToatl() {
	int totalinventorys = 0;
	ifstream outFile("book.txt");  //���ҵ��ļ�
	if (!outFile) {
		cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
		exit(1);
	}
	else {
		//�����鱾��������������
		do{
			string s;
			getline(outFile, s);//����ÿһ��
			istringstream sin(s);
			string a, b, c, d; float i; int k;
			sin >> a >> b >> c >> d >> i >> k;
			totalinventorys += k;  //ÿ��ȡ����������������ۼ�
		} while (!outFile.eof());
	}cout << "�����鼮�ܿ������  ";cout<< totalinventorys; cout << " ���鼮" << endl;
	outFile.close();  //�ر��ļ�
}

void Book::sort() {
	cout << "1.��������------������1" << endl;
	cout << "2.��������------������2" << endl;
	cout << "3.����ISBN-------������3" << endl;
	cout << "4.����������------������4" << endl;
	cout << "5.��*�����*����鿴�����鼮��Ϣ------������5" << endl;
	cout << "6.��*�۸�*����鿴�����鼮��Ϣ------������6" << endl;
	int options;
	cin >> options;
	switch (options)
	{
	case 1: {  //����
		bool zai = false; //���ڱ�־�Ƿ�����Ȿ��
		Book book;
		ifstream outFile("book.txt");  //���ҵ��ļ�
		if (!outFile) {
			cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
			exit(1);
		}
		else {
			cout << "������������";
			string key;
			cin >> key;
			//�����鱾��������������
			do {
				string s;
				getline(outFile, s); //����ÿһ��
				istringstream sin(s);   //����һ���ַ������������Ķ���sin
				string a, b, c, d; float j; int k;
				sin >> a >> b >> c >> d >> j >> k;  //��ȡ�ַ���
				if ( a == key) {   //ƥ�䵽�鼮 ����鼮��Ϣ
					zai = true; 
					book.setName(a); book.setPress(b); book.setISBN(d); book.setAthour(c); book.setInventory(k); book.setPrice(j);
					book.inputOneBook(book); 
				}
			}// while (!outFile.eof());   
			while (outFile.peek() != EOF);  //��ȡ�ļ�ָ����һ��λ�õ�ֵ���������ƶ��ļ�ָ�룺
			if (!zai) {
				cout << "δ�ҵ�����鼮��" << endl;
			}
		}outFile.close();
		break;
	}
	case 2:{
		bool zai = false; //���ڱ�־�Ƿ�����Ȿ��
		Book book;
		ifstream outFile("book.txt");  //���ҵ��ļ�
		if (!outFile) {
			cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
			exit(1);
		}
		else {
			cout << "���������ߣ�";
			string key;
			cin >> key;
			//�����鱾��������������
			do {
				string s;
				getline(outFile, s); //����ÿһ��
				istringstream sin(s);
				string a, b, c, d; float j; int k;
				sin >> a >> b >> c >> d >> j >> k;
				if ( c == key) {
					zai = true;
					book.setName(a); book.setPress(b); book.setISBN(d); book.setAthour(c); book.setInventory(k); book.setPrice(j);
					book.inputOneBook(book); 
				}
			}// while (!outFile.eof());  
			while (outFile.peek() != EOF);  //��ȡ�ļ�ָ����һ��λ�õ�ֵ���������ƶ��ļ�ָ�룺
			if (!zai) {
				cout << "δ�ҵ�����鼮��" << endl;
			}
		}outFile.close();
		break;
	}
		  
	case 3: {   //ISBN����
		bool zai = false; //���ڱ�־�Ƿ�����Ȿ��
		Book book;
		ifstream outFile("book.txt");  //���ҵ��ļ�
		if (!outFile) {
			cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
			exit(1);
		}
		else {
			cout << "������ISBN�ţ�";
			string key;
			cin >> key;
			//�����鱾��������������
			do {
				string s;
				getline(outFile, s);//����ÿһ��
				istringstream sin(s);
				string a, b, c, d; float j; int k;
				sin >> a >> b >> c >> d >> j >> k;
				if (d == key) {
					zai = true;
					book.setName(a); book.setPress(b); book.setISBN(d); book.setAthour(c); book.setInventory(k); book.setPrice(j);
					book.inputOneBook(book);
				}
			} //while (!outFile.eof());  
			while (outFile.peek() != EOF);
			if (!zai) {
				cout << "δ�ҵ�����鼮��" << endl;
			}
		}outFile.close();
		break;
	}
	
	case 4: {   //������
		bool zai = false; //���ڱ�־�Ƿ�����Ȿ��
		Book book;
		ifstream outFile("book.txt");  //���ҵ��ļ�
		if (!outFile) {
			cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
			exit(1);
		}
		else {
			cout << "��������������ƣ�";
			string key;
			cin >> key;
			//�����鱾��������������
			do {
				string s;
				getline(outFile, s);//����ÿһ��
				istringstream sin(s);
				string a, b, c, d; float j; int k;
				sin >> a >> b >> c >> d >> j >> k;
				if (b == key) {
					zai = true;
					book.setName(a); book.setPress(b); book.setISBN(d); book.setAthour(c); book.setInventory(k); book.setPrice(j);
					book.inputOneBook(book); 
				}
			}// while (!outFile.eof());  
			while (outFile.peek() != EOF);
			if (!zai) {
				cout << "δ�ҵ�����鼮��" << endl;
			}
		}outFile.close();
		break;
	}
	
	case 5: {
		Book books[500];  //�����������
		int inventory[500]; 
		int p = 0;  //ѭ��ʱ��Ϊ������±�
		int count = 0;//��������ͼ�������
		int t;//�м����
		Book f;//�м����
		ifstream outFile("book.txt");  //���ҵ��ļ�
		if (!outFile) {
			cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
			exit(1);
		}
		else {
			//��ȡ���ݵ�������
			do {
				string s;
				getline(outFile, s);//����ÿһ��
				istringstream sin(s);
				string a, b, c, d; float j; int k;
				sin >> a >> b >> c >> d >> j >> k;
				inventory[p] = k;
				books[count].setName(a); books[count].setPress(b); books[count].setISBN(d); books[count].setAthour(c); books[count].setInventory(k); books[count].setPrice(j);
				count++;
				p++;
			}while (outFile.peek() != EOF);

			//ð�ݷ�������
			for(int i = 0; i < count-1 ; i++) {  //��Ϊ���һ���������ˣ�������count-1
				for (int j = 0; j < count-1 ; j++) {  //�ڲ�ѭ����ÿ������һ�ζ������������ʣ�º��ŵģ������е����ֵ����ǰ��
					if (inventory[j] < inventory[j + 1])
					{
						t = inventory[j];  //���������
						f = books[j];
						inventory[j] = inventory[j + 1];
						books[j] = books[j + 1];
						inventory[j + 1] = t;
						books[j + 1] = f;
					}
				}
			}
			
			for (int y = 0; y < count; y++) {
				books[y].inputOneBook(books[y]);//����Ȿ�����Ϣ
			}
		}outFile.close();  //�ر��ļ�
			break;
	}
case 6:
		//��ͼ��۸����
		{
		Book books[500];
		int price[500];
		int p = 0;
		int count = 0;//��������ͼ�������
		int t;//�м����
		Book f;//�м����
		ifstream outFile("book.txt");  //���ҵ��ļ�
		if (!outFile) {
			cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
			exit(1);
		}
		else {
			//�����鱾��������������
			do {
				string s;
				getline(outFile, s);//����ÿһ��
				istringstream sin(s);
				string a, b, c, d; float i; int k;
				sin >> a >> b >> c >> d >> i >> k;
				price[p] = i;
				books[count].setName(a); books[count].setPress(b); books[count].setISBN(d); books[count].setAthour(c); books[count].setInventory(k); books[count].setPrice(i);
				count++;
				p++;
			} //while (!outFile.eof());
			while (outFile.peek() != EOF);

			//ð�ݷ�������
			for (int i = 0; i < count-1 ; i++) {  //��Ϊ���һ���������ˣ�������count-1
				for (int j = 0; j < count-1 ; j++) { //�ڲ�ѭ����ÿ����һ�ζ������������ʣ�º��ŵģ������е����ֵ����ǰ��
					if (price[j] < price[j + 1])//�����������Ƚ�
					{
						t = price[j];
						f = books[j];
						price[j] = price[j + 1];  
						books[j] = books[j + 1];  //������鼮�����������е�λ��ҲҪ���ı�
						price[j + 1] = t;
						books[j + 1] = f;
					}
				}
			}
			for (int y = 0; y < count; y++) {
				books[y].inputOneBook(books[y]);//����Ȿ�����Ϣ
			}
		}outFile.close();
		break;
		}
	//��ͼ����������������
	default:break;
	}
}
