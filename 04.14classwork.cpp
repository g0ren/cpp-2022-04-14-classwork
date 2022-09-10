#include <iostream>
#include <cstring>
using namespace std;
#define MAX(X,Y) (((X)>(Y))?(X):(Y))
#define MIN(X,Y) (((X)<(Y))?(X):(Y))

class String {
	char *value;
public:

//	1. Конструктор по умолчанию
	String() {
		this->value = nullptr;
	}
//	2. Конструктор с значением
	String(char *value) {
		if (value) {
			this->value = new char[strlen(value) + 1];
			strcpy(this->value, value);
		}
	}
//	3. Конструктор копирования
	String(const String &s) {
		this->value = s.value ? new char[strlen(s.value) + 1] : nullptr;
		if (this->value)
			strcpy(this->value, s.value);
	}

	int length() {
		return strlen(this->value);
	}
//	4. Оператор =
	String operator=(const String &s) {
		this->value = s.value ? new char[strlen(s.value) + 1] : nullptr;
		if (this->value)
			strcpy(this->value, s.value);
		return *this;
	}
//	5. Оператор +
	String operator+(char *v) {
		char *newval = new char[this->length() + strlen(v) + 1] { };
		char *ptr = newval;
		for (int i = 0; i < this->length(); i++, ptr++) {
			*ptr = this->value[i];
		}
		for (int i = 0; i < strlen(v); i++, ptr++) {
			*ptr = v[i];
		}
		String ret { newval };
		return ret;
	}

	String operator+(String s) {
		return this->operator+(s.value);
	}

//	6. Функция вывода
	void print() {
		cout << this->value;
	}
	friend ostream& operator<<(ostream&, const String&);

//  7. Деструктор
	~String() {
		if (this->value)
			delete[] this->value;
	}
//	8. Оператор ==
	bool operator==(String s) {
		if (this->length() != s.length())
			return false;
		for (int i = 0; i < this->length(); i++)
			if (this->value[i] != s.value[i])
				return false;
		return true;
	}
//  9. Оператор !=
	bool operator!=(String s) {
		return !(operator ==(s));
	}
//	10. Оператор >
	bool operator>=(String s) {
		if (this->length() < s.length())
			return false;
		for (int i = 0; i < this->length(); i++)
			if (this->value[i] < s.value[i])
				return false;
		return true;
	}
	bool operator>(String s) {
		return !(operator ==(s)) && operator >=(s);
	}
//	11. Оператор <
	bool operator<=(String s) {
		return !(operator >(s));
	}
	bool operator<(String s) {
		return !(operator >=(s));
	}
//  12. Конструктор перемещения
	String(String &&s) {
		if (this->value)
			this->value = nullptr;
		strcpy(this->value, s.value);
		delete[] s.value;
	}

};

ostream& operator<<(ostream &out, const String &s) {
	out << s.value;
	return out;
}

int main() {
	String s1 { "Mikhail" };
	String s2 { "Lunkovsky" };
	String s3 { s1 + " " + s2 };
	String s4 = s3;
	s4.print();
	return 0;
}
