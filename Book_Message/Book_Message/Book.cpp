#include "pch.h"
#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<ostream>
#include"Book.h"
using namespace std;

//用于图书馆添加新书的时候，录入整本书的信息
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

//录入新书时把书籍信息写进文件里
void Book::writeData(Book book) {
	ofstream outFile;  //定义文件对象
	outFile.open("book.txt",ios::binary | ios::app);  //打开文件
	if (!outFile)
	{  //文件打开失败
		cout << "操作失败：文件打开失败！";
		exit(1);
	}
	outFile << book.getName() << "   " << book.getISBN() << "   " << book.getAuthor() << "   "
		<< book.getPress() << "   " << book.getPrice() << "  " << book.getInventory() << endl;  //写入文件
	outFile.close();  //关闭文件
}

//修改书籍信息
void Book::ModifyOne(Book book) {
	cout << "*****修改图书信息*****" << endl;
	cout << "书籍名称（不需要书名号）：";
	string name;
	cin >> name;   
	book.setName(name);
	/*cout << "ISBN:";  //保证isbn唯一
	string isbn;
	cin >> isbn;*/  
	cout << "出版社(完整名称)：";
	string press;
	cin >> press;
	book.setPress(press);
	cout << "作者：";
	string author;
	cin >> author;
	book.setAthour(author);
	cout << "库存量：";
	int inventory;
	cin >> inventory;
	book.setInventory(inventory);
	cout << "出售价格：";
	float price;
	cin >> price;
	book.setPrice(price);
}

//录入一本新进馆的书
bool Book::Record() {
	char x;   //定义全局变量x,用于后面是否继续录入的判断
	do {
		cout << "*****录入图书信息*****" << endl;
		cout << "书籍名称（不需要书名号）：";
		string name;
		cin >> name;   
		cout << "ISBN:";
		string isbn;
		cin >> isbn;
		//do...while...判断isbn是否重复
		ifstream outFile("book.txt");
		do{
			string s;
			getline(outFile, s);//读入每一行
			istringstream sin(s);
			string a, b, c, d; int i; float k;
			sin >> a >> b >> c >> d >> i >> k;
			if (d == isbn) {            //如果重复，则给出提示，返回并结束函数
				cout << " ISBN号重复！ " << endl;
				return false;
			}
		}while (outFile.peek() != EOF);
		outFile.close();
		//ISBN未重复继续输入信息
		cout << "出版社(完整名称)：";
		string press;
		cin >> press;
		cout << "作者：";
		string author;
		cin >> author;
		cout << "库存量：";
		int inventory;
		cin >> inventory;
		cout << "出售价格：";
		float price;
		cin >> price;
		Book newbook(name, isbn, press, author, inventory, price);  //利用构造函数传参将数据放入
		writeData(newbook);   //写入文件
		cout << "是否继续录入新书信息：是（Y/y）,否（N/n）";
		cin >> x;
	} while (x == 'Y' || x == 'y');  //当输入Y/y时将继续执行do里的语句
	return true;
}

//inputOneBook输出一本书的内容，方便确认信息
void  Book::inputOneBook(Book book) {
	cout << "书籍名称：" << book.name << endl;
	cout << "    ISBN：" << book.isbn << endl;
	cout << "  出版社：" << book.press << endl;
	cout << "    作者：" << book.author << endl;
	cout << "  库存量：" << book.inventory << endl;
	cout << "出售价格：" << book.price << endl;
	cout << "--------------------------------------------------------" << endl;
}


bool Book::judgeInventory(int i) {  
	if (i <= 0) {      //如果库存量小于或等于0 则给函数返回 false
		return false;
	}
	if (i > 0) {
		return true;
	}
}

void Book::countToatl() {
	int totalinventorys = 0;
	ifstream outFile("book.txt");  //打开我的文件
	if (!outFile) {
		cout << "读取文件失败！" << endl;
		exit(1);
	}
	else {
		//定义书本数组来保存数据
		do{
			string s;
			getline(outFile, s);//读入每一行
			istringstream sin(s);
			string a, b, c, d; float i; int k;
			sin >> a >> b >> c >> d >> i >> k;
			totalinventorys += k;  //每次取出库存量的数据做累加
		} while (!outFile.eof());
	}cout << "书店的书籍总库存量是  ";cout<< totalinventorys; cout << " 册书籍" << endl;
	outFile.close();  //关闭文件
}

void Book::sort() {
	cout << "1.搜索书名------按数字1" << endl;
	cout << "2.搜索作者------按数字2" << endl;
	cout << "3.搜索ISBN-------按数字3" << endl;
	cout << "4.搜索出版社------按数字4" << endl;
	cout << "5.以*库存量*排序查看所有书籍信息------按数字5" << endl;
	cout << "6.以*价格*排序查看所有书籍信息------按数字6" << endl;
	int options;
	cin >> options;
	switch (options)
	{
	case 1: {  //书名
		bool zai = false; //用于标志是否存在这本书
		Book book;
		ifstream outFile("book.txt");  //打开我的文件
		if (!outFile) {
			cout << "读取文件失败！" << endl;
			exit(1);
		}
		else {
			cout << "请输入书名：";
			string key;
			cin >> key;
			//定义书本数组来保存数据
			do {
				string s;
				getline(outFile, s); //读入每一行
				istringstream sin(s);   //定义一个字符串输入流道的对象sin
				string a, b, c, d; float j; int k;
				sin >> a >> b >> c >> d >> j >> k;  //读取字符串
				if ( a == key) {   //匹配到书籍 输出书籍信息
					zai = true; 
					book.setName(a); book.setPress(b); book.setISBN(d); book.setAthour(c); book.setInventory(k); book.setPrice(j);
					book.inputOneBook(book); 
				}
			}// while (!outFile.eof());   
			while (outFile.peek() != EOF);  //读取文件指针下一个位置的值，但并不移动文件指针：
			if (!zai) {
				cout << "未找到相关书籍！" << endl;
			}
		}outFile.close();
		break;
	}
	case 2:{
		bool zai = false; //用于标志是否存在这本书
		Book book;
		ifstream outFile("book.txt");  //打开我的文件
		if (!outFile) {
			cout << "读取文件失败！" << endl;
			exit(1);
		}
		else {
			cout << "请输入作者：";
			string key;
			cin >> key;
			//定义书本数组来保存数据
			do {
				string s;
				getline(outFile, s); //读入每一行
				istringstream sin(s);
				string a, b, c, d; float j; int k;
				sin >> a >> b >> c >> d >> j >> k;
				if ( c == key) {
					zai = true;
					book.setName(a); book.setPress(b); book.setISBN(d); book.setAthour(c); book.setInventory(k); book.setPrice(j);
					book.inputOneBook(book); 
				}
			}// while (!outFile.eof());  
			while (outFile.peek() != EOF);  //读取文件指针下一个位置的值，但并不移动文件指针：
			if (!zai) {
				cout << "未找到相关书籍！" << endl;
			}
		}outFile.close();
		break;
	}
		  
	case 3: {   //ISBN查找
		bool zai = false; //用于标志是否存在这本书
		Book book;
		ifstream outFile("book.txt");  //打开我的文件
		if (!outFile) {
			cout << "读取文件失败！" << endl;
			exit(1);
		}
		else {
			cout << "请输入ISBN号：";
			string key;
			cin >> key;
			//定义书本数组来保存数据
			do {
				string s;
				getline(outFile, s);//读入每一行
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
				cout << "未找到相关书籍！" << endl;
			}
		}outFile.close();
		break;
	}
	
	case 4: {   //出版社
		bool zai = false; //用于标志是否存在这本书
		Book book;
		ifstream outFile("book.txt");  //打开我的文件
		if (!outFile) {
			cout << "读取文件失败！" << endl;
			exit(1);
		}
		else {
			cout << "请输入出版社名称：";
			string key;
			cin >> key;
			//定义书本数组来保存数据
			do {
				string s;
				getline(outFile, s);//读入每一行
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
				cout << "未找到相关书籍！" << endl;
			}
		}outFile.close();
		break;
	}
	
	case 5: {
		Book books[500];  //声明数组对象
		int inventory[500]; 
		int p = 0;  //循环时作为数组的下标
		int count = 0;//用来保存图书的总数
		int t;//中间变量
		Book f;//中间变量
		ifstream outFile("book.txt");  //打开我的文件
		if (!outFile) {
			cout << "读取文件失败！" << endl;
			exit(1);
		}
		else {
			//读取数据到数组里
			do {
				string s;
				getline(outFile, s);//读入每一行
				istringstream sin(s);
				string a, b, c, d; float j; int k;
				sin >> a >> b >> c >> d >> j >> k;
				inventory[p] = k;
				books[count].setName(a); books[count].setPress(b); books[count].setISBN(d); books[count].setAthour(c); books[count].setInventory(k); books[count].setPrice(j);
				count++;
				p++;
			}while (outFile.peek() != EOF);

			//冒泡法来排序
			for(int i = 0; i < count-1 ; i++) {  //因为最后一个不用排了，所以是count-1
				for (int j = 0; j < count-1 ; j++) {  //内层循环，每遍历完一次都会把整个（或剩下后排的）数组中的最大值排在前面
					if (inventory[j] < inventory[j + 1])
					{
						t = inventory[j];  //库存量排序
						f = books[j];
						inventory[j] = inventory[j + 1];
						books[j] = books[j + 1];
						inventory[j + 1] = t;
						books[j + 1] = f;
					}
				}
			}
			
			for (int y = 0; y < count; y++) {
				books[y].inputOneBook(books[y]);//输出这本书的信息
			}
		}outFile.close();  //关闭文件
			break;
	}
case 6:
		//以图书价格分类
		{
		Book books[500];
		int price[500];
		int p = 0;
		int count = 0;//用来保存图书的总数
		int t;//中间变量
		Book f;//中间变量
		ifstream outFile("book.txt");  //打开我的文件
		if (!outFile) {
			cout << "读取文件失败！" << endl;
			exit(1);
		}
		else {
			//定义书本数组来保存数据
			do {
				string s;
				getline(outFile, s);//读入每一行
				istringstream sin(s);
				string a, b, c, d; float i; int k;
				sin >> a >> b >> c >> d >> i >> k;
				price[p] = i;
				books[count].setName(a); books[count].setPress(b); books[count].setISBN(d); books[count].setAthour(c); books[count].setInventory(k); books[count].setPrice(i);
				count++;
				p++;
			} //while (!outFile.eof());
			while (outFile.peek() != EOF);

			//冒泡法来排序
			for (int i = 0; i < count-1 ; i++) {  //因为最后一个不用排了，所以是count-1
				for (int j = 0; j < count-1 ; j++) { //内层循环，每遍历一次都会把整个（或剩下后排的）数组中的最大值排在前面
					if (price[j] < price[j + 1])//相邻两个作比较
					{
						t = price[j];
						f = books[j];
						price[j] = price[j + 1];  
						books[j] = books[j + 1];  //定义的书籍对象在数组中的位置也要做改变
						price[j + 1] = t;
						books[j + 1] = f;
					}
				}
			}
			for (int y = 0; y < count; y++) {
				books[y].inputOneBook(books[y]);//输出这本书的信息
			}
		}outFile.close();
		break;
		}
	//以图书库存量来进行排序
	default:break;
	}
}
