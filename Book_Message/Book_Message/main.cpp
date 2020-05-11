// Book_Message.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include"Book.h"
#include"BookManagment.h"
#include"Bookpurchase.h"
#include <vector>
#include <windows.h>
using namespace std;


int main()
{
	for (int i = 0; i < 7; i++)   //界面样式
		{
			cout << endl;
		}
	cout << setw(60);
	cout << "**************" << endl;
	cout << setw(60);
	cout << "*图书管理系统*" << endl;
	cout << setw(60);
	cout << "**************" << endl;
	cout << setw(100);
	cout << "--读书不觉已春深，一寸光阴一寸金。" << endl;
	for (int i = 0; i < 2; i++)
		{
			cout << endl;
		}
	
	cout << setw(65);
	cout << "----购买图书（请按1）" << endl;
	cout << setw(65);
	cout << "----查询图书（请按2）" << endl;
	cout << setw(65);
	cout << "----管理图书（请按3）" << endl;
	char o;
	cin >> o;
	switch (o)  
	{
	case '1': 
	{     //大括号明确其变量作用域，不然编译器无法通过
		BookPurchase customer;
		customer.IsCustomers();
		break;
	}
	case '2':
	{	
		Book allbooks;
		allbooks.countToatl();
		allbooks.sort();
		break;
	}
	case '3':
	{
		BookManagment people2;
		people2.IsMamagment();
		break; 
	}
	default:
		break;
	}
}







