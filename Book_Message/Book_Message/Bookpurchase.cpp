#include"pch.h"
#include"BookManagment.h"
#include"Bookpurchase.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

//顾客操作函数 先登录注册 再购买书籍
void BookPurchase::IsCustomers() {
	BookPurchase customer;   //定义一个顾客对象
	cout << "*******欢迎购买优质图书*********" << endl;
	cout << "我是已注册过的顾客（请按1）" << endl;
	cout << "我是尚未注册的顾客（请按2）" << endl;
	cout << "退出（请按3）" << endl;
	int n;
	cin >> n;
	switch (n) {
	case 1:
		customer.Log();
		break;
	case 2:
		customer.BeMembers();
		break;
	case 3:
		break;
	default:
		break;
	}
}

//注册
void BookPurchase::BeMembers(){
	cout << "******设置个人信息********" << endl;
	ofstream fileout("god.txt", ios::app);//打开文件
	string phn;
	string pw;  
	cout << "设置您的认证号码：";
	cin >> phn;
	cout << "设置密码：";
	cin >> pw;
	fileout << endl;
	fileout << phn << " " << pw << " " << endl;
	fileout.close();//关闭文件
	cout << "按任意键退出" << endl;
	getchar();
	system("exit");
}

//登录
void BookPurchase::Log() {
	cout << "******欢迎登录购书系统******" << endl;
	string phn, pw;
	cout << "请输入您的号码：";
	cin >> phn;
	cout << "请输入密码：";
	cin >> pw;
	string h, w;
	ifstream filein("god.txt");
	bool buzai = true;//默认账号不存在
	do {
		if (filein.eof()) 
			break;
		string l;//定义变量
		getline(filein,l);//读入每一行
		istringstream sin(l);//定义sin流
		sin >> h >> w;
		if ((phn == h) && (pw == w)) {//如果输入顾客正确，开始购书~
			BookPurchase customer;
			buzai = false;  
			customer.PurchaseBook();
		}
	}while (filein.peek() != EOF); //判断是否都读到文件尾
	if (buzai) {  //如果找不到顾客输入的账号信息
		cout << "输入密码不正确/该号码尚未注册哦！" << endl;
		filein.close();
		cout << "按任意键退出" << endl;
		getchar();
		system("exit");
	}
}

//购买书籍
void BookPurchase::PurchaseBook() {
	Book book3;
	int nowInventory; //库存量
	bool bought = false;
	int outNumber;
	ifstream outFile("book.txt");  //打开我的文件
	if (!outFile) {
		cout << "读取文件失败！" << endl;
		exit(1);
	}
	else {
		int n;
		cout << "请输入需要查找的书籍的ISBN：" << endl;
		n = 0;//标签，是否有这本书
		string t;
		cin >> t;//输入ISBN号
		cout << "----------------------------------------------------------------" << endl;
		do{	
			//定义变量
			string x, y, z, u; int w;int v;
			string s;
			getline(outFile, s);//读入每一行
			istringstream sin(s);  
				sin >> x >> y >> z >> u;
				if (t == u) { //找到这本书了，进行借书服务和更新数据的步骤
					n = 1;
					sin >> w >> v;
					book3.setName(x);
					book3.setISBN(u);
					book3.setPress(y);
					book3.setAthour(z);
					book3.setInventory(v);
					book3.setPrice(w);
					book3.inputOneBook(book3);
					//判断这本书还有没有对应的库存
					nowInventory = v;
					if (book3.judgeInventory(nowInventory)) {   //此函数会返回一个布尔值，如果有库存，就返回true
					        
						cout << "        是否购买：是（Y / y）, 否（N / n）" << endl;
						string a;//定义变量
						cin >> a;
						if (a == "Y" || a == "y") {
							cout << "请输入需要购买的数量";
							cin >> outNumber;
							//do...while..判断输入的库存量有没有超过实际库存量
							do {
								if (outNumber > v) {
									cout << "库存量不足，请重新输入书籍数量：";
									cin >> outNumber;
								}
							} while (outNumber > v); 
							cout << "恭喜你购买成功！" << endl;
							bought = true;
						}
						if (a == "N" || a == "n") {
							cout << "您未购买任何书籍~~~" << endl;
							bought = false;
						}
					}
					else {//如果库存不足
						cout << "库存不足，无法购买此书籍！若有其他需要，请联系工作人员！" << endl;
					}
				}
		} while (n == 0);  //这个的逻辑是，当没有找到这本书时，就继续找，找到了（n变量标签不再被识别）就不再循环了。
		if (n == 0) {   //找不到书籍
			cout << "找不到这本书！" << endl;
			outFile.close();
		}outFile.close();
		
		
			//进行文件读写
			ifstream filein("book.txt");
			do {    //把这本书的信息写进文件里，
				string x, y, z, u; int w; int k;//定义变量
				string s;
				getline(filein, s);//读入每一行
				istringstream sin(s);
				sin >> x >> y >> z >> u;
				ofstream tempFile("book2.txt",ios::app);//写到一个暂时的新文件中去
				if (t!=u) {       //如果不是查询购买的这本书，不需要做任何修改
					tempFile << s << endl;
				}
				if (t == u ) {     //如果这本书是顾客查询的书籍，有可能要做修改
					
					sin >> w >>k;//将一行字符串读出
					
					int trueInventory ;
					if (bought) {   //如果这本书被买了 
						trueInventory = k - outNumber;  //计算真正的库存量
					}
					else {
						trueInventory = k;  //没要被买，库存量不变
					}
					book3.setName(x);//把对应的信息都设定好
					book3.setISBN(u);
					book3.setPress(y);
					book3.setAthour(z);
					book3.setInventory(trueInventory); //其中的库存量可能要更新
					book3.setPrice(w);
					tempFile << book3.getName() << "  " << book3.getPress() << "  " << book3.getAuthor() << "  "
						<< book3.getISBN() << "  " << book3.getPrice() << "  " << book3.getInventory() << endl; //写入文件
					tempFile.close();//关闭文件
				}
			} //while (!filein.eof());
			while (filein.peek() != EOF);//判断是否读到文件尾
			filein.close();//关闭文件
		  
		

		//更新book.txt文件的内容
		ifstream file1("book2.txt");//打开文档
		ofstream file2("book.txt");//把之前的文档给清空了！

		for (string a; getline(file1, a);) {
			file2 << a << endl;
		}
		file1.close();
		file2.close();
		system("del book2.txt");//删除文件副本
		cout << "按任意键退出" << endl;
		
	}
}