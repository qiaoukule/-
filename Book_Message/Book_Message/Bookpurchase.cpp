#include"pch.h"
#include"BookManagment.h"
#include"Bookpurchase.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

//�˿Ͳ������� �ȵ�¼ע�� �ٹ����鼮
void BookPurchase::IsCustomers() {
	BookPurchase customer;   //����һ���˿Ͷ���
	cout << "*******��ӭ��������ͼ��*********" << endl;
	cout << "������ע����Ĺ˿ͣ��밴1��" << endl;
	cout << "������δע��Ĺ˿ͣ��밴2��" << endl;
	cout << "�˳����밴3��" << endl;
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

//ע��
void BookPurchase::BeMembers(){
	cout << "******���ø�����Ϣ********" << endl;
	ofstream fileout("god.txt", ios::app);//���ļ�
	string phn;
	string pw;  
	cout << "����������֤���룺";
	cin >> phn;
	cout << "�������룺";
	cin >> pw;
	fileout << endl;
	fileout << phn << " " << pw << " " << endl;
	fileout.close();//�ر��ļ�
	cout << "��������˳�" << endl;
	getchar();
	system("exit");
}

//��¼
void BookPurchase::Log() {
	cout << "******��ӭ��¼����ϵͳ******" << endl;
	string phn, pw;
	cout << "���������ĺ��룺";
	cin >> phn;
	cout << "���������룺";
	cin >> pw;
	string h, w;
	ifstream filein("god.txt");
	bool buzai = true;//Ĭ���˺Ų�����
	do {
		if (filein.eof()) 
			break;
		string l;//�������
		getline(filein,l);//����ÿһ��
		istringstream sin(l);//����sin��
		sin >> h >> w;
		if ((phn == h) && (pw == w)) {//�������˿���ȷ����ʼ����~
			BookPurchase customer;
			buzai = false;  
			customer.PurchaseBook();
		}
	}while (filein.peek() != EOF); //�ж��Ƿ񶼶����ļ�β
	if (buzai) {  //����Ҳ����˿�������˺���Ϣ
		cout << "�������벻��ȷ/�ú�����δע��Ŷ��" << endl;
		filein.close();
		cout << "��������˳�" << endl;
		getchar();
		system("exit");
	}
}

//�����鼮
void BookPurchase::PurchaseBook() {
	Book book3;
	int nowInventory; //�����
	bool bought = false;
	int outNumber;
	ifstream outFile("book.txt");  //���ҵ��ļ�
	if (!outFile) {
		cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
		exit(1);
	}
	else {
		int n;
		cout << "��������Ҫ���ҵ��鼮��ISBN��" << endl;
		n = 0;//��ǩ���Ƿ����Ȿ��
		string t;
		cin >> t;//����ISBN��
		cout << "----------------------------------------------------------------" << endl;
		do{	
			//�������
			string x, y, z, u; int w;int v;
			string s;
			getline(outFile, s);//����ÿһ��
			istringstream sin(s);  
				sin >> x >> y >> z >> u;
				if (t == u) { //�ҵ��Ȿ���ˣ����н������͸������ݵĲ���
					n = 1;
					sin >> w >> v;
					book3.setName(x);
					book3.setISBN(u);
					book3.setPress(y);
					book3.setAthour(z);
					book3.setInventory(v);
					book3.setPrice(w);
					book3.inputOneBook(book3);
					//�ж��Ȿ�黹��û�ж�Ӧ�Ŀ��
					nowInventory = v;
					if (book3.judgeInventory(nowInventory)) {   //�˺����᷵��һ������ֵ������п�棬�ͷ���true
					        
						cout << "        �Ƿ����ǣ�Y / y��, ��N / n��" << endl;
						string a;//�������
						cin >> a;
						if (a == "Y" || a == "y") {
							cout << "��������Ҫ���������";
							cin >> outNumber;
							//do...while..�ж�����Ŀ������û�г���ʵ�ʿ����
							do {
								if (outNumber > v) {
									cout << "��������㣬�����������鼮������";
									cin >> outNumber;
								}
							} while (outNumber > v); 
							cout << "��ϲ�㹺��ɹ���" << endl;
							bought = true;
						}
						if (a == "N" || a == "n") {
							cout << "��δ�����κ��鼮~~~" << endl;
							bought = false;
						}
					}
					else {//�����治��
						cout << "��治�㣬�޷�������鼮������������Ҫ������ϵ������Ա��" << endl;
					}
				}
		} while (n == 0);  //������߼��ǣ���û���ҵ��Ȿ��ʱ���ͼ����ң��ҵ��ˣ�n������ǩ���ٱ�ʶ�𣩾Ͳ���ѭ���ˡ�
		if (n == 0) {   //�Ҳ����鼮
			cout << "�Ҳ����Ȿ�飡" << endl;
			outFile.close();
		}outFile.close();
		
		
			//�����ļ���д
			ifstream filein("book.txt");
			do {    //���Ȿ�����Ϣд���ļ��
				string x, y, z, u; int w; int k;//�������
				string s;
				getline(filein, s);//����ÿһ��
				istringstream sin(s);
				sin >> x >> y >> z >> u;
				ofstream tempFile("book2.txt",ios::app);//д��һ����ʱ�����ļ���ȥ
				if (t!=u) {       //������ǲ�ѯ������Ȿ�飬����Ҫ���κ��޸�
					tempFile << s << endl;
				}
				if (t == u ) {     //����Ȿ���ǹ˿Ͳ�ѯ���鼮���п���Ҫ���޸�
					
					sin >> w >>k;//��һ���ַ�������
					
					int trueInventory ;
					if (bought) {   //����Ȿ�鱻���� 
						trueInventory = k - outNumber;  //���������Ŀ����
					}
					else {
						trueInventory = k;  //ûҪ���򣬿��������
					}
					book3.setName(x);//�Ѷ�Ӧ����Ϣ���趨��
					book3.setISBN(u);
					book3.setPress(y);
					book3.setAthour(z);
					book3.setInventory(trueInventory); //���еĿ��������Ҫ����
					book3.setPrice(w);
					tempFile << book3.getName() << "  " << book3.getPress() << "  " << book3.getAuthor() << "  "
						<< book3.getISBN() << "  " << book3.getPrice() << "  " << book3.getInventory() << endl; //д���ļ�
					tempFile.close();//�ر��ļ�
				}
			} //while (!filein.eof());
			while (filein.peek() != EOF);//�ж��Ƿ�����ļ�β
			filein.close();//�ر��ļ�
		  
		

		//����book.txt�ļ�������
		ifstream file1("book2.txt");//���ĵ�
		ofstream file2("book.txt");//��֮ǰ���ĵ�������ˣ�

		for (string a; getline(file1, a);) {
			file2 << a << endl;
		}
		file1.close();
		file2.close();
		system("del book2.txt");//ɾ���ļ�����
		cout << "��������˳�" << endl;
		
	}
}