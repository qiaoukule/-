#include"pch.h"
#include"BookManagment.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

//管理操作，先登录再操作
void BookManagment::IsMamagment() {
	Book book1;  //定义对象
	BookManagment person;  
	if (person.Identify()) {   //如果输入的密码正确，函数返回true 
		int m;
		cout << "----执行相关操作请按对于数字---" << endl;
		cout << "1.添加书籍" << "\n" << "2.查询或修改" << "\n" << "3.删除功能" << "\n" << "4.退出" << endl;
		cin >> m;
		switch (m)
		{
		case 1:
			book1.Record();
			break;
		case 2:
			person.Modify();
			break;
		case 3:
			person.deletebook();
			break;
		case 4:
			break;
		default:
			break;
		}
	}
}

//管理员登录
bool BookManagment::Identify() {
	int password;  //定义变量
	cout << "-------欢迎登陆--------";
	cout << "请输入管理员权限密码：";
	cin >> password;   
	if (password == 675061026) {
		cout << "验证成功！" << endl;
		return true;
	}
	else {
		cout << "验证失败！" << endl;
		return false;
	}
}

//修改操作
void BookManagment::Modify() {
	Book book1;  //实例化book类对象
	ifstream outFile("book.txt");  //打开我的文件
	if (!outFile) {  //如果打开文件失败
		cout << "读取文件失败！" << endl;
		exit(1);
	}

	bool is = false;  //定义变量用于后面判断是否有这本书
	string one;   //定义ISBN变量
	string a, b, c, d; int i; float k;
	cout << "请输入希望查询或修改信息的书籍ISBN号：";
	cin >> one;  //输入ISBN
	do {
		string line;
		getline(outFile, line);//读入每一行 (从istream中读取至多n个字符保存在s对应的数组中,遇到换行符时读取终止)
		istringstream sin(line); //定义一个字符串输入流的对象sin,并调用sin的复制构造函数
		sin >> a >> b >> c >> d;  //将line中所包含的字符串放入sin 对象中，每个变量保存着书籍不同的信息
		ofstream TempFile("book2.txt", ios::app);   //定义一个文件对象，打开一个新的文件TempFile，用来记录更新书籍信息
		if (one != d) {    //逐行判断是不是我要ISBN号对应书籍的信息所在行
			TempFile << line << endl;   //不是的话就原封不动地写进去文件book2.txt
		}
		if (one ==d) {  //找到所在行
			is = true;   //找到书籍的标志
			int n;       //用于操作选择的变量
			cout << "书籍信息" << "↓↓※↓↓" << "---------------(修改书籍信息请按数字9)(退出请按0)" << endl;
			sin >> i >> k;  
			book1.setName(a); //传参用于输出信息
			book1.setISBN(d);
			book1.setPress(b);
			book1.setAthour(c);
			book1.setInventory(k);
			book1.setPrice(i);
			//调用函数输出书籍的信息，来方便再次确认信息;
			book1.inputOneBook(book1); 
			cin >> n;  //用户输入选择
			switch (n)
			{
			case 9:{
				cout << "*****修改图书信息*****" << endl;
				cout << "书籍名称（不需要书名号）：";
				string name;
				cin >> name;   
				book1.setName(name);
				cout << "出版社:";
				string press;
				cin >> press;
				book1.setPress(press);
				cout << "作者：";
				string author;
				cin >> author;
				book1.setAthour(author);
				cout << "库存量：";
				int inventory;
				cin >> inventory;
				book1.setInventory(inventory);
				cout << "出售价格：";
				float price;
				cin >> price;
				book1.setPrice(price);
                 //写进文件里
				TempFile << book1.getName() << "  " << book1.getPress() << "  " << book1.getAuthor() << "  "
					<<  book1.getISBN()<< "  " << book1.getPrice() << "  " << book1.getInventory() << endl; //写入文件
				cout << "修改成功！" << endl;
				TempFile.close();  //关闭文件
				break;
			}
			case 0: //尽管不做修改，也要把信息写回文件里，
				TempFile << book1.getName() << "  " << book1.getPress() << "  " << book1.getAuthor() << "  "
					<< book1.getISBN() << "  " << book1.getPrice() << "  " << book1.getInventory() << endl;
			    TempFile.close();
				break;
			default:  //以防万一会手抖
				TempFile << book1.getName() << "  " << book1.getPress() << "  " << book1.getAuthor() << "  "
					<< book1.getISBN() << "  " << book1.getPrice() << "  " << book1.getInventory() << endl;
				TempFile.close();
				break;
			}
		}
	}// while (!outFile.eof());//判断是否读到文件末尾
	while (outFile.peek() != EOF);
	if (!is) {  //如果is为false，即没有找到书籍的标记
		cout << "未找到相关书籍！" << endl;
	}
	outFile.close();
	ifstream file1("book2.txt");//打开文档
	ofstream file2("book.txt");//把之前的文档给清空了！
	for (string a; getline(file1, a);) {  //把修改的内容写到文件中去
		file2 << a << endl;
	}
			file1.close();
			file2.close();
			system("del book2.txt");//删除文件副本
			cout << "按任意键退出" << endl;
			getchar();
			system("exit");
}

//删除书籍信息
void BookManagment::deletebook() {
	Book book2;  //实例化book类对象
	ifstream outFile("book.txt");  //打开我的文件
	if (!outFile) {   //如果读取失败
		cout << "读取文件失败！" << endl;
		exit(1);
	}
	else {
		cout << "请输入需要删除的ISBN：" << endl;
		int n = 0;  //标签，检查是否有这本书
		string t;
		cin >> t;   //输入书名
		do {
			int v;  //定义变量
			string x, y, z, u; int w;  //用来分别存储图书的信息
			string s;  
			getline(outFile, s);//读入每一行
			istringstream sin(s);
			sin >> x >> y >> z >> u;
			ofstream TempFile("book2.txt", ios::app);
			if (t != u) {
				TempFile << s << endl;   
			}
			else {
				n = 1;  //判断有这本书
				sin >> w >> v;
				book2.setName(x);
				book2.setISBN(u);
				book2.setPress(y);
				book2.setAthour(z);
				book2.setInventory(v);
				book2.setPrice(w);
				book2.inputOneBook(book2);
				cout<<"是否删除：是（Y / y）, 否（N / n）"<<endl;
				string a;//定义变量
				cin >> a;
				if (a == "Y" || a == "y") {  //选择删除，那就不把这本书的信息写进文件里就好了
					cout << "删除成功！" << endl;
				}
				if (a == "N" || a == "n") {
					cout << "未删除！" << endl;
					TempFile << book2.getName() << "  " << book2.getPress() << "  " << book2.getAuthor() << "  "
						<< book2.getISBN() << "  " << book2.getPrice() << "  " <<book2.getInventory()<< endl;//写入文件
				}
			}TempFile.close();
		}while(!outFile.eof());
		if (n == 0) {
			cout << "找不到这本书！" << endl;
		}
	}
	ifstream filei("book2.txt");//打开文件
	ofstream fileout("book.txt");  //打开并情空文件

	for (string s; getline(filei, s);) {  //将修改后的内容写到文件中去
		fileout << s << endl;
	}
	filei.close();
	fileout.close();
	system("del book2.txt");  //删除book2这个暂时文件
	cout << "按任意键退出" << endl;
	getchar();
	system("exit");
}
