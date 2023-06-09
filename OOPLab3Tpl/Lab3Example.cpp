﻿#if !defined(_MSC_VER)
#define CODING_VS_CODE
#endif
#if !defined(CODING_VS_CODE)
#include <clocale>
#endif
#define _USE_MATH_DEFINES 
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
using namespace std;

class Cube {
	double a;
	unsigned int color;
public:
	Cube() : a(1.0), color(0) {}
	Cube(double ai) : a(ai), color(0) {}
	Cube(int ic) : a(1.0) { if (ic >= 0) color = ic; else color = 0; }
	Cube(double a, int c) {
		this->a = a;
		if (c >= 0) color = c; else color = 0;
	}
	double getA() const
	{
		return a;
	}
	void setA(double a)
	{
		if (a < 0 || a > 1.e+100)
		{
			cout << " Error set a \n";
			return;
		}
		this->a = a;
	}
	double getColor() const
	{
		return color;
	}
	void setColor(int c)
	{
		if (c < 0 || c > 10000)
		{
			cout << " Error set color \n";
			return;
		}
		this->color = c;
	}
	double S() {
		return 6 * a * a;
	}
	double V() {
		return a * a * a;
	}
	double d() {
		return a * sqrt(3.0);
	}
	double Sphere() {
		return 4 / 3 * M_PI * ((a * a * a / 8));
	}
	void printInfo()
	{
		cout << "\n a= " << a << " color = " << color;
		cout << " S(Cube) = " << S() << " V = " << V() << " D = " << d() << "S(Sphere)= " << Sphere() << endl;
	}
};

void TestCube()
	{
		Cube obj;
		obj.printInfo();
		double in_a; int in_color;
		cout << " Input side and color Cube "; cin >> in_a >> in_color;
		Cube obj1(in_a), obj2(in_color), obj3(in_a, in_color);
		obj1.printInfo();
		obj2.printInfo();
		obj3.printInfo();
		obj.setA(-5);
		obj.printInfo();
		obj.setA(5);
		obj.printInfo();
		obj.setA(2.e100);
		obj.printInfo();
		obj.setColor(-10);
		obj.printInfo();
		obj.setColor(10);
		obj.printInfo();
		obj.setColor(10001);
		obj.printInfo();
		cout << " End testing \n";
	}

// Ключове слово static 

class foo
{
private:
	static int count; // загальне поле всім об'єктів
	// (У сенсі "оголошення")
public:
	foo() { incObj(); } // інкрементування під час створення об'єкта
	static int incObj() { return ++count; }
	int getcount() { return count; }
};
int  foo::count = 0;
// Ключове слово static ставиться перед типом способу.В основному використовуються
//для роботи зі статичними полями класу.

/*  Example 3
Створити тип даних - клас вектор, який має поля x, y типу double і змінну стану. У класі визначити
o	конструктор без параметрів(інінціалізує поля в нуль);
o	конструктор з одним параметром типу double (інінціалізує поля);
o	конструктор з одним параметром вказівник на тип double (інінціалізує поля x, y значенням масиву за вказівником, якщо вказівник NULL (nulptr) то встановити код помилки);
o	деструктор із виведенням інформації про стан вектора;
o	визначити функції друку, додавання, віднімання, векторний добуток які здійснюють ці арифметичні операції з даними цього класу;
o	функцію ділення на ціле типу double(при діленні на 0 змінити стан, а ділення не виконувати);
o	визначити функцію порівняння менше які повертають true або false.
У змінну стани встановлювати код помилки, діленні на 0, при передачі NULL (nulptr) в конструкторі із вказівником. Передбачити можливість підрахунку числа об'єктів даного типу. Написати програму тестування всіх можливостей цього класу.
*/
enum STATE {
	OK, BAD_INIT, BAD_DIV
};

class Vec2
{
	double  x, y;
	int state;
	static int count;
public:
	Vec2() : x(0), y(0) {
		state = OK; count++;
	}   // 	 конструктор без параметрів
	Vec2(double iv) : x(iv), y(iv) {
		state = OK; count++;
	}
	Vec2(double ix, double iy);
	Vec2(double* v);
	~Vec2() {
		count--;
		cout << " state Vec " << state;
		cout << " Vec delete \n";
	}
	Vec2(const Vec2&);
	Vec2 Add(Vec2& d);
	Vec2 Sub(Vec2& d);
	Vec2 Mul(double d);
	Vec2 Div(double d);
	void Input();   //  !!! Без первантаження операцій    
	void Output();  //  !!! Без первантаження операцій
	bool CompLessAll(Vec2& s);
	static int getCount() {
		if (count <= 0) cout << " Немає об'єктів Vec2 ";
		return count;
	}
	int getState() { return state; }
};
int Vec2::count = 0;
Vec2::Vec2(double ix, double iy) {
	x = ix; y = iy;
	state = OK;
	count++;
}
Vec2::Vec2(const Vec2& s) {
	//if (this == &s) return; //  // the expression is used in the old standard
	x = s.x; y = s.y; state = OK;
	count++;
};
Vec2::Vec2(double* v) {
	if (v == nullptr) {
		state = BAD_INIT; x = 0; y = 0;
	}
	else {
		x = v[0]; y = v[1];
		state = OK;
	}
	count++;
}
void Vec2::Input() {
	cout << " Input  x y ";
	cin >> x >> y;
}
void Vec2::Output() {
	cout << " x =" << x << " y = " << y << " state  " << state << endl;
}

Vec2 Vec2::Add(Vec2& s) {
	Vec2 tmp;
	tmp.x = x + s.x;
	tmp.y = y + s.y;
	return tmp;
}

Vec2 Vec2::Sub(Vec2& s) {
	Vec2 tmp;
	tmp.x = x - s.x;
	tmp.y = y - s.y;
	return tmp;
}
Vec2 Vec2::Div(double d) {
	Vec2 tmp;
	if (fabs(d) < 1.e-25) {
		tmp.state = BAD_DIV;
		cout << " Error div \n";
		return *this;
	}
	tmp.x = x / d;
	tmp.y = y / d;
	return tmp;
}
Vec2 Vec2::Mul(double d) {
	Vec2 tmp;
	tmp.x = x * d;
	tmp.y = y * d;
	return tmp;
}

bool Vec2::CompLessAll(Vec2& s) {

	if (x < s.x && y < s.y) return true;
	return false;
}

enum SetState {
	NoErrors,
	NoMemori, //не вистачає пам'яті
	NotInRange, //виходить за межі множини
	InvalidNumber // ініціалізація числом
};

static string SetStateStrings[] = { "NoErrors", "NoMemori", "NotInRange", "InvalidNumber" };


class Set {
	unsigned int* mnojina;
	unsigned int beg, end, size;
	SetState state = NoErrors;

public:
	Set() {
		beg = 0;
		end = 100;
		size = end - beg;
		mnojina = (unsigned int*)calloc(size, sizeof(unsigned int));
		for (int i = 0; i < size; i++) {
			mnojina[i] = 0;
		}
	}
	Set(unsigned int end) {
		beg = 0;
		this->end = end;
		size = end - beg;
		mnojina = (unsigned int*)calloc(size, sizeof(unsigned int));
		for (int i = 0; i < size; i++) {
			mnojina[i] = 0;
		}
	}

	Set(unsigned int beg, unsigned int end) {
		this->beg = beg;
		this->end = end;
		size = end - beg;

		if (end < 0 || 0 < beg) {
			state = InvalidNumber;
		}

		mnojina = (unsigned int*)calloc(size, sizeof(unsigned int));
		for (int i = 0; i < size; i++) {
			mnojina[i] = 0;
		} 
	}
	Set(unsigned int beg, unsigned int end, unsigned int value) {
		this->beg = beg;
		this->end = end;
		size = end - beg;

		if (end < value || value < beg) {
			state = InvalidNumber;
		}

		mnojina = (unsigned int*)calloc(size, sizeof(unsigned int));
		for (int i = 0; i < size; i++) {
			mnojina[i] = value;
		}
	}

	Set(const Set& ref_Point)
	{
		this->beg = ref_Point.beg;
		this->end = ref_Point.end;
		this->size = ref_Point.size;

		this->mnojina = (unsigned int*)calloc(size, sizeof(unsigned int));
		for (int i = 0; i < size; i++) {
			this->mnojina[i] = ref_Point.mnojina[i];
		}
	}

	Set& operator=(const Set& a) {
		this->beg = a.beg;
		this->end = a.end;
		this->size = a.size;
		free(mnojina);
		mnojina = (unsigned int*)calloc(a.size, sizeof(unsigned int));
		for (int i = 0; i < a.size; i++) {
			this->mnojina[i] = a.mnojina[i];
		}
		return *this;

	}

	~Set() {
		free(mnojina);
	}

	void Setvalue(int i, unsigned int value ) {

		if (end < value || value < beg) {
			state = NotInRange;
		}

		if (i > size) {
		state = NoMemori;
		}
		else {
			mnojina[i] = value;
		}
	}

	int getCount(unsigned int value) {
		int count=0;
		for (int i = 0; i < size; i++) {
			if (mnojina[i] == value) {
				count++;
			}
		}
		return count;
	}

	unsigned int GetObjectWeight() {
		unsigned int j = 0;
		for (int i = 0; i < this->size; i++) {
			j = j + this->mnojina[i];
		}
		return j;
	}


	void printInfo()
	{
	
		cout << "Beg =" << beg << " " << "End =" << end << " " << "Size =" << size << " ";
		cout << "State=" << SetStateStrings[state] << " ";
		for (int i = 0; i < size; i++) {
			cout << "[" << mnojina[i] << "] " ;
		}

		cout << endl;
		//cout << "Intersection operation " << endl;
		//cout << "Difference operation " << endl;
	}
	Set operator+(const Set& a) {
		int new_beg = min(this->beg, a.beg);

		int new_end = max(this->end, a.end);

		Set result = Set(new_beg, new_end);

		for (int i = 0; i < this->size; i++) {
			result.Setvalue(i, this->mnojina[i]);
		}

		for (int i = 0; i < a.size; i++) {
			result.Setvalue(this->size + i, a.mnojina[i]);
		}

		return result;
	}	
	
	Set operator*(Set& a) {
		int new_beg = max(this->beg, a.beg);

		int new_end = min(this->end, a.end);

		Set result = Set(new_beg, new_end);
		int j=0; 
		for (int i = 0; i < this->size; i++) {
			if (a.getCount(mnojina[i]) > 0) {
				result.Setvalue(j, mnojina[i]); 
				j++;
			}
		}
		
		return result;
	}

	Set operator-(Set& a) {
		int new_beg = this->beg;

			int new_end = this->end;

		Set result = Set(new_beg, new_end);
		int j = 0;
		for (int i = 0; i < this->size; i++) {
			if (a.getCount(mnojina[i]) == 0) {
				result.Setvalue(j, mnojina[i]);
				j++;
			}
		}

		return result;
	}

	bool operator>(Set& a) {
		 
		if (a.GetObjectWeight() < this->GetObjectWeight()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator<(Set& a) {

		if (a.GetObjectWeight() > this->GetObjectWeight()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator==(Set& a) {

		if (a.GetObjectWeight() == this->GetObjectWeight()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator!=(Set& a) {

		if (a.GetObjectWeight() != this->GetObjectWeight()) {
			return true;
		}
		else {
			return false;
		}
	}
};

void TestPrisvoena() {
	Set obj1(3, 8, 4);
	obj1.Setvalue(1, 8);
	obj1.Setvalue(2, 5);
	obj1.Setvalue(3, 3);

	Set obj2(20, 40, 20);
	obj2.Setvalue(1, 21);
	obj2.Setvalue(2, 22);
	obj2.Setvalue(3, 23);
	cout << "Before Prisvoena" << endl;
	obj1.printInfo();
	obj2.printInfo();
	obj2 = obj1;
	cout << "After Prisvoena" << endl;
	obj1.printInfo();
	obj2.printInfo();
}

void TestErrors() {
	Set obj4(1, 8, 200);
	obj4.printInfo();
	obj4.Setvalue(200,2);
	obj4.printInfo();
	obj4.Setvalue(2, 200);
	obj4.printInfo();
}

void Inf()
{
	Set obj(1, 5, 4);
	obj.printInfo();
	obj.Setvalue(2, 6);
	obj.printInfo();
	int a = obj.getCount(6);
	cout << " a: " << a << endl;

}

void Operation1(){

	Set obj1(3, 8, 4);
	obj1.Setvalue(1, 8);
	obj1.Setvalue(2, 5);
	obj1.Setvalue(3, 3);

	Set obj2(20, 40, 20);
	obj2.Setvalue(1, 21);
	obj2.Setvalue(2, 22);
	obj2.Setvalue(3, 23);

	cout << "Union operation" << endl;
	Set obj3 = obj1 + obj2;
	obj1.printInfo();
	obj2.printInfo();
	obj3.printInfo();

	Set obj4(1, 8, 2);
	obj4.Setvalue(1, 3);
	obj4.Setvalue(2, 4);
	obj4.Setvalue(3, 6);
	obj4.Setvalue(4, 7);
	obj4.Setvalue(5, 8);


	Set obj5(1, 35, 7);
	obj5.Setvalue(1, 8);
	obj5.Setvalue(2, 10);

	cout << "Intersection operation " << endl;
	Set obj6 = obj4 * obj5;
	obj4.printInfo();
	obj5.printInfo();
	obj6.printInfo();

	Set obj8(20, 40, 22);
	obj8.Setvalue(1, 28);
	obj8.Setvalue(2, 39);
	obj8.Setvalue(3, 31);


	Set obj9(15, 45, 16);
	obj9.Setvalue(1, 42);
	obj9.Setvalue(2, 38);
	obj9.Setvalue(3, 39);

	cout << "Subtraction operation " << endl;
	Set obj7 = obj8 - obj9;
	obj8.printInfo();
	obj9.printInfo();
	obj7.printInfo();

}

void Operation2() {
	Set obj2(20, 40, 20);
	obj2.Setvalue(1, 21);
	obj2.Setvalue(2, 22);
	obj2.Setvalue(3, 23);

	Set obj4(1, 8, 2);
	obj4.Setvalue(1, 3);
	obj4.Setvalue(2, 4);
	obj4.Setvalue(3, 6);
	obj4.Setvalue(4, 7);
	obj4.Setvalue(5, 8);


	cout << "obj2: ";
	obj2.printInfo();
	cout << "obj4: ";
	obj4.printInfo();

	cout << "Operation bigger then" << endl;
	if (obj4 > obj2) {
		cout << "obj4 > obj2" << endl;
	}
	else {
		cout << "obj4 < obj2" << endl;
	}


	cout << "Operation less than" << endl;
	if (obj4 < obj2) {
		cout << "obj4 < obj2" << endl;
	}
	else {
		cout << "obj4 > obj2" << endl;
	}


	cout << "The operation is equal" << endl;
	if (obj4 == obj2) {
		cout << "obj4 = obj2" << endl;
	}
	else {
		cout << "obj4 =! obj2" << endl;
	}


	cout << "The operation is тще equal" << endl;
	if (obj4 != obj2) {
		cout << "obj4 != obj2" << endl;
	}
	else {
		cout << "obj4 = obj2" << endl;
	}
}
 
void Prisvoena(){
	cout << "The operation =" << endl;
	TestPrisvoena();

	cout << " End testing \n";
}

void TestMnozhina() {
	char ch;
	do {
		cout << "\nSelect operation: \n";
		cout << "    1.  Information \n";
		cout << "    2.  Operation *,+,- \n";
		cout << "    3.  Operation >,<,=,!= \n";
		cout << "    4.  Operation Prisvoena \n";
		cout << "    5.  Test Errors \n";
		cout << "    6.  Exit \n";

		ch = _getch();
		switch (ch) {
		case '1': Inf(); break;
		case '2': Operation1(); break;
		case '3': Operation2(); break;
		case '4': Prisvoena(); break;
		case '5': TestErrors(); break;

		}
	} while (ch != '6');
}

int Task4()
{
#if !defined(CODING_VS_CODE)
	setlocale(LC_CTYPE, "ukr");
	cout << "Тестування створенного класу \n";
	cout << "Тестування конструкторiв \n"; 
#else 
	cout << "Testing create class  \n";
	cout << "Testing crot's  \n";
#endif
	Vec2 ObjCDef;
	ObjCDef.Output();
	Vec2 ObjP1(10.0);
	ObjP1.Output();
	double  a = 1.0, b = 2.0;
	Vec2  ObjP2(a, b);
	ObjP2.Output();
	Vec2 ObjCopy(ObjP2);
	double* v = nullptr, v2[] = { 1.2, 3.3 };
	Vec2  ObjP3(v2);
	if (ObjP3.getState() != OK) cout << " ObjP3  x= 0  y= 0  \n";
	Vec2  ObjP4(v2);
	if (ObjP4.getState() != OK) cout << " ObjP4 x= 0  y= 0  \n";
#if !defined(CODING_VS_CODE)
	cout << " Кiлькiсть створених об'єктiв Vec2 " << Vec2::getCount() << endl;
	cout << "Тестування введення \n";
	ObjCDef.Input();
	cout << "Тестування функцiй \n";
	ObjCDef = ObjCDef.Add(ObjP2);
	ObjCDef.Output();
	cout << " \n Кiлькiсть створених об'єктiв Vec2 до Sub " << Vec2::getCount() << endl;
	ObjCDef = ObjCDef.Sub(ObjP2);
	cout << " \n Кiлькiсть створених об'єктiв Vec2 пiсля Sub " << Vec2::getCount() << endl;
#else 
	cout << "Testing input \n";
	ObjCDef.Input();
	cout << "Testing gunction \n";
	ObjCDef = ObjCDef.Add(ObjP2);
	ObjCDef.Output();
	cout << " \n Counts create objects Vec2 before  Sub " << Vec2::getCount() << endl;
	ObjCDef = ObjCDef.Sub(ObjP2);
	cout << " \n  Counts create objects Vec2 after Sub  " << Vec2::getCount() << endl;
#endif

	ObjCDef.Output();
	ObjCDef = ObjCDef.Mul(5);
	ObjCDef.Output();
	ObjCDef = ObjCDef.Div(1.3);
	if (ObjCDef.getState() == STATE::BAD_DIV) cout << "BAD_DIV \n";
	ObjCDef.Output();

	ObjCDef = ObjCDef.Div(0.0);
	if (ObjCDef.getState() == STATE::BAD_DIV) cout << "BAD_DIV \n";
	ObjCDef.Output();
	cout << "ObjCopy state " << ObjCopy.getState() << endl;
	if (ObjCopy.CompLessAll(ObjCDef))  cout << "ObjCopy less ObjDef  " << endl;

	
#if !defined(CODING_VS_CODE)
	cout << "Завершення  тестування  \n";
#else 
	cout << "Completion of testing  \n";
#endif
	return 1;

}


/*example  4
Створити тип даних - клас вектор, який має вказівник на ComplexDouble, число елементів і змінну стану. У класі визначити
o	 конструктор без параметрів( виділяє місце для одного елемента та інінціалізує його в нуль);
o	конструктор з одним параметром - розмір вектора( виділяє місце та інінціалізує масив значенням нуль);
o	конструктор із двома параметрами - розмір вектора та значення ініціалізації(виділяє місце (значення перший аргумент) та інінціалізує значенням другого аргументу).
o	конструктор копій та операцію присвоєння; // !!!
o	деструктор звільняє пам'ять;
o	визначити функції друку, додавання;
У змінну стани встановлювати код помилки, коли не вистачає пам'яті, виходить за межі масиву. Передбачити можливість підрахунку числа об'єктів даного типу. Написати програму тестування всіх можливостей цього класу.
*/

#include<complex>
using namespace std;
typedef complex<double> ComplexDouble;
#define _RE 0
#define _IM 1

class ComplexVector
{
	ComplexDouble* v;
	int num;   // default num=2
	int state = 0;
public:
	ComplexVector() : ComplexVector(2) {}
	ComplexVector(int n);
	ComplexVector(int n, ComplexDouble&);
	ComplexVector(int n, ComplexDouble*);
	ComplexVector(const ComplexVector& s);
	ComplexVector& operator=(const ComplexVector& s);
	~ComplexVector() {
		std::cout << " del vec";
		if (v) delete[] v;
	}
	void Output();
	void Input();
	ComplexVector Add(ComplexVector& b);

};

ComplexVector::ComplexVector(int n) {
	if (n <= 0)    n = 2;  // default num =2;
	num = n;
	v = new ComplexDouble[n];
	for (int i = 0; i < n; i++) {
			v[i] = 0.0;
			//v[i]._Val[_RE]=0.0; v[i]._Val[_IM]=0.0;  
		}

}
ComplexVector::ComplexVector(int n, ComplexDouble& b) : ComplexVector(n) {
	for (int i = 0; i < num; i++) {
		v[i] = b;
		//v[i]._Val[_RE]=0.0; v[i]._Val[_IM]=0.0;  
	}
}

ComplexVector::ComplexVector(int n, ComplexDouble* p) : ComplexVector(n) {
	if (p != nullptr) 
	for (int i = 0; i < num; i++) 
		v[i] = p[i];
	
}

ComplexVector::ComplexVector(const ComplexVector& s) {
	// if (this == &s) return;  // the expression is used in the old standard
	num = s.num;
	v = new ComplexDouble[num];
	state = 0;
	for (int i = 0; i < num; i++)   v[i] = s.v[i];
}

ComplexVector& ComplexVector::operator=(const ComplexVector& s) {

	if (num != s.num)
	{
		if (v) delete[] v;
		num = s.num;
		v = new ComplexDouble[num];
		state = 0;
	}
	for (int i = 0; i < num; i++)   v[i] = s.v[i];
	return *this;
}
void ComplexVector::Input() {
	int in_num=0;
		do {
			cout << "Input size Vec\n";
			cin >> in_num;
		} while (in_num <= 0);
		if (num != in_num ) {
			num = in_num;
			if (v) delete[] v;
		v = new ComplexDouble[num];
	}
	for (int i = 0; i < num; i++) {

#if defined(_MSC_VER)
cout << " v [ " << i << " ] real img  "; cin >> v[i] >> v[i]._Val[_IM];
#else 
double re,im;
cout << " v [ " << i << " ] real img  "; cin >> re>>im;
v[i].real(re); 
v[i].imag(im);
#endif		
		
		
	}
}

void ComplexVector::Output() {
	if (num != 0) {
		for (int i = 0; i < num; i++) {
			cout << " v [ " << i << " ]   " << v[i] << '\t';
			cout << endl;
		}
	}
}

ComplexVector ComplexVector::Add(ComplexVector& b) {
	int tnum;
	tnum = num < b.num ? num : b.num;
	if (tnum >= 0) {
		ComplexVector tmp(tnum);
		for (int i = 0; i < tnum; i++) tmp.v[i] = v[i] + b.v[i];
		return tmp;
	}
	return ComplexVector(1);
}


int Task3()
{
	ComplexDouble a(1.0, 2), b, c;
	cout << a << endl;
#if defined(_MSC_VER)
    b._Val[_RE] = 21.3;
	b._Val[_IM] = 22.3;
#else 
    b.real( 21.3);
	b.imag (22.3);
#endif	
	
	cout << b << endl;
	c = a + b;
	cout << c << endl;
	cout << " Test  " << endl;
	ComplexVector VecObj, VecObj1(10);
	cout << "VecObj \n";
	VecObj.Output();
	cout << "VecObj1 \n";
	VecObj1.Output();
	cout << " Input a " << endl;

#if defined(_MSC_VER)
 cin >> a >> a._Val[_IM];
#else 
double re,im;
cin >> re>>im;
a.real(re); 
a.imag(im);
#endif		
	cout << a << endl;
	ComplexVector VecObj2(10, a);
	VecObj2.Output();

	VecObj.Input();
	cout << endl;
	VecObj.Output();
	VecObj1 = VecObj.Add(VecObj2);
	VecObj1.Output();

	return 1;
}


