#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <cstring>
#include <math.h>
using namespace std;
#define N 5
#define eps 1e-20

class CFabric;

class MyClass
{
	public:
	double a[N];
	MyClass() {memset(a, 0, sizeof(a));}
	MyClass(double x) {for (size_t i = 0; i < N; i++) a[i] = x;}
	virtual ~MyClass() {cout << "MyClass Destructor" << endl;}
	double &operator[] (size_t i) {return a[i];}
	virtual void Show() = 0;
	virtual int cmp(double u, double v) {if (u > v) return 1; if (u < v) return -1; return 0;}
	void Sort() {double z; for (int i=0; i < N; i++) for (int j=0; j < N; j++) {if (cmp(a[i], a[j]) == 1) {z = a[i]; a[i] = a[j]; a[j] = z;}}}
	static int Input(const char *name, vector <MyClass *> &v, vector<CFabric *> &fabric);
};

class ChildClass1 : public MyClass
{
	public:
	ChildClass1(): MyClass(){}
	ChildClass1(double x): MyClass(x){}
	~ChildClass1() {cout << endl << "ChildClass1 Destructor" << endl;}
	void Show() {for(int i = 0; i < N; i++) cout << endl << "! a[" << i << "] = " << a[i]; cout << endl;}
	int cmp(double u, double v) {if (u > v) return 1; if (u < v) return -1; return 0;}
	ChildClass1 &operator= (const MyClass &b) {if (this != &b) {for (int i=0; i < N; i++) {a[i] = b.a[i];}} return *this;}
};

class ChildClass2 : public MyClass
{
	public:
	ChildClass2(): MyClass(){}
	ChildClass2(double x): MyClass(x){}
	~ChildClass2() {cout << endl << "ChildClass2 Destructor" << endl;}
	void Show() {for(int i = 0; i < N; i++) cout << endl << "? a[" << i << "] = " << a[i]; cout << endl;}
	int cmp(double u, double v) {if (u > v) return 1; if (u < v) return -1; return 0;}
	ChildClass2 &operator= (const MyClass &b) {if (this != &b) {for (int i=0; i < N; i++) {a[i] = b.a[i];}} return *this;}
};

class CFabric
{
	public:
	virtual MyClass *Create() = 0;
	virtual ~CFabric() {}; 
};

class CFabric1 : public CFabric
{
	public:
	virtual MyClass *Create(){return new ChildClass1;}  
};

class CFabric2 : public CFabric
{
	public:
	virtual MyClass *Create(){return new ChildClass2;}         
};
                         


int MyClass::Input(const char *name, vector <MyClass *> &v, vector<CFabric *> &fabric)
{
	ifstream f(name); string str;
	while (getline(f, str))
	{
		stringstream ss(str); istream_iterator<string> it;
		it = ss;
		if (it != istream_iterator<string>())
		{
			if (fabs(stod(*it) - 1) < eps)
			{
				MyClass *w = fabric[0] -> Create(); size_t i; ++it; 
				//cout << "\n|" << *it << "|\n"; ++it;
				for (i = 0; i < N && it != istream_iterator<string>(); ++it) (*w)[i++] = stod(*it);
				v.push_back(w);
			}
			if (fabs(stod(*it) - 2) < eps)
			{
				MyClass *w = fabric[1] -> Create(); size_t i; ++it; 
				//cout << "\n|" << *it << "|\n"; ++it;
				for (i = 0; i < N && it != istream_iterator<string>(); ++it) (*w)[i++] = stod(*it);
				v.push_back(w);
			}
		}
	}
	return 0;	         

}


int main(void)
{
	vector<MyClass *> v; ChildClass1 cl;
	vector<CFabric *> fabric;

	fabric.push_back(new CFabric1);
	fabric.push_back(new CFabric2);
	
	MyClass::Input("data.txt", v, fabric);
	
	cout << "File input test" << endl << endl;

	for (size_t i = 0; i < v.size(); ++i) v[i]->Show();

	cout << endl << "Destructor test" << endl;

	for (size_t i = 0; i < v.size(); ++i) delete v[i];
	
	cout << endl << "Method inheritance test" << endl;
	
	for (size_t i = 0; i < N; ++i) cl[i] = N - i;
	cl.Show();

	for (size_t i = 0; i < fabric.size(); ++i) delete fabric[i];
	
	return 0;
}