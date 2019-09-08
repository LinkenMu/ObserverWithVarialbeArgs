// observor_with_variable_args.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "observer.h"
#include <iostream>
#include <functional>
#include <utility>

using namespace std;
class Observer1 {   //����Ҫ��ͬ�Ļ��ֻ࣬��Ҫע��ĺ���������ͬ��ģ��
public:
	void Notify(int a, int b) { cout << __FUNCTION__ << a << b << endl; };


};

class Observer2 {
public:
	void Handle(int a, int b) { cout << __FUNCTION__ << a << b << endl; };

};

class Observer3 {
public:
	void Info(float a) { cout << __FUNCTION__ << a << endl; };

};


class Observer4 {
public:
	void Info(int a , int b, int c) { cout << __FUNCTION__ << a << endl; };

};


int main()
{
	Observer1 ob1;
	Observer2 ob2;
	Observer3 ob3;
	Observer4 ob4;


	function<void(int, int)> f1 = bind(&Observer1::Notify, &ob1, placeholders::_1, placeholders::_2);
	function<void(int, int)> f2 = bind(&Observer2::Handle, &ob2, placeholders::_1, placeholders::_2);


	//auto f1 = bind(&Observer1::Notify, &ob1, placeholders::_1, placeholders::_2);  //��Ҫʹ��auto�� Line46 �ܿ���������.  ����Event<decltype(f1)> �� Event<decltype(f2)>��2�ֲ�ͬ����
	//auto f2 = bind(&Observer2::Handle, &ob2, placeholders::_1, placeholders::_2);
	
	auto f33 = bind(&Observer3::Info, &ob3, placeholders::_1);  //��Ҫʹ��auto�� ����	int id3 = event1.AddObserver(f3);  �ܳɹ�, ��������ϵĻ���
	function<void(int)> f3 = bind(&Observer3::Info, &ob3, placeholders::_1);
	cout << typeid(f1).name()<<'\n' << typeid(f2).name()<< '\n'<<typeid(f3).name() <<'\n' << typeid(f33).name()<< endl;
	
	
	//Event<decltype(f1)> event1;
	auto f4 = bind(&Observer4::Info, &ob4, placeholders::_1, placeholders::_2, placeholders::_3);

	Event<function<void(int, int)>> event1;
	int id1 = event1.AddObserver(f1);
	int id2 = event1.AddObserver(f2);
	int id33 = event1.AddObserver(f33);
	//int id4 = event1.AddObserver(f4);   //id4 ��id3��������ǣ�f4��Ҫ�Ĳ�����f1��һ��������ܱ�������
	Event<function<void(int)>> event2;
	int id3 = event2.AddObserver(f3);

	event1.Notify(1,2);
	event2.Notify(1.0);

	system("pause");

    return 0;
}

