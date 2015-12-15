

#include <iostream>
#include <cstring>
using namespace std;

class String {

	char* str = nullptr;
	unsigned size = 0;

public:

	String() : str(nullptr), size(0) {}
	String(const char* _str) {

		if (_str && *_str) {

			size = strlen(_str) + 1;
			str = new char[size];
			strcpy_s(str, size, _str);

		}
	}

	String(const String& S) {

		if (S.str && *S.str) {
			size = S.size;
			str = new char[size];
			strcpy_s(str, size, S.str);
		}
	}

	~String() {

		if (*str) {

			delete[] str;
			str = nullptr;
		}
	}

	void operator= (const String& S) {

		if (S.str && *S.str) {
			delete[] str;
			size = S.size;
			str = new char[size];
			strcpy_s(str, size, S.str);
		}

	}

	void operator+ (const String& S) {

		if (S.str && *S.str) {
			char* temp = new char[S.size + size];
			strcpy_s(temp, size, str);
			delete[] str;
			size += S.size;
			strcat_s(temp, size, S.str);
			str = temp;
		}
	}

	void operator+= (const String& S) {

		if (S.str && *S.str) {
			char* temp = new char[S.size + size];
			strcpy_s(temp, size, str);
			delete[] str;
			size += S.size;
			strcat_s(temp, size, S.str);
			str = temp;
		}
	}

	char* operator[] (unsigned index) {
		if (index <= size)
			return &str[index];
		else
			return nullptr;
	}

	double str_to_double() {
		double temp;
		temp = atof(str);
		return temp;
	}

	int str_to_int() {
		int temp;
		temp = atoi(str);
		return temp;
	}

	unsigned serch(const char* s) {
		if (s && *s) {
			unsigned size_s = strlen(s);
			if (size_s > size) {
				return 0;
			}

			unsigned count = 0;


			for (unsigned i = 0; i < size; ++i) {
				for (unsigned j = 0; j < size_s; ++j) {

					if (str[i + j] != s[j]) {
						break;
					}
					if (j == (size_s - 1)) {
						count++;
					}
				}
			}
			return count;
		}
		else
			return 0;
	}

	bool isNotEmpty() const {
		return (str && *str) ? true : false;
	}

	bool operator== (const String& S) const {

		if (!(strcmp(str, S.str))) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator> (const String& S) const {

		if (strcmp(str, S.str) > 0) {
			return true;
		}
		else
			return false;
	}

	bool operator< (const String& S) const {

		return !(this->operator>(S));
	}

	bool operator!= (const String& S) const {

		return !(this->operator==(S));
	}

	friend ostream& operator<<(ostream&, const String&);
	friend istream& operator>>(istream&, String&);


};

ostream& operator<< (ostream& os, const String& S) {

	os << (S.isNotEmpty() ? S.str : "");

	return os;

}

istream& operator>> (istream& is, String& S) {

	char buf[100];
	is.get(buf, 100);
	S.size = strlen(buf) + 1;
	S.str = new char[S.size];
	strcpy_s(S.str, S.size, buf);
	return is;

}

int main() {

	setlocale(LC_ALL, "");
	const unsigned size = 7;
	String* A = new String[size];
	unsigned menu = 0;
	while (menu != 9) {

		system("cls");
		cout << "Строки в памяти:\n";

		for (int i = 0; i < size; ++i){
			cout << i + 1 << ". " << A[i] << '\n';


		}

		cout << endl;
		cout << "Меню:" << endl;
		cout << "1. Ввести строку\n2. Просмотреть строку\n3. Сравнить строки\n";
		cout << "4. Поиск в строке символа, подстроки\n5. Замена буквы в строке\n";
		cout << "6. Преобразовать строку в целое число\n7. Преобразовать строку в дробное число\n";
		cout << "8. Соединить две строки\n9. Завершение работы\n";

		cin >> menu;

		switch (menu) {

		case 1:
			system("cls");
			cout << "введите номер строки\n";
			cin >> menu; cin.ignore();
			if (menu > 0 && menu <= size) {
				cout << "введите строку\n";
				cin >> A[menu - 1];
			}
			break;

		case 2:
			system("cls");
			cout << "введите номер строки\n";
			cin >> menu; cin.ignore();
			if (menu > 0 && menu <= size) {
				cout << A[menu - 1];
			}
			break;

		case 3:
			system("cls");
			unsigned number1, number2;
			cout << "Введите номер первой строки для сравнения\n";
			cin >> number1; cin.ignore();
			cout << "\nВведите номер второй строки для сравнения \n";
			cin >> number2; cin.ignore();
			if ((number1 > 0 && number1 <= size) && (number2 > 0 && number2 <= size)) {
				if (A[number1 - 1] == A[number2 - 1])
					cout << "строки равны" << endl;
				else if (A[number1 - 1] > A[number2 - 1])
					cout << "строка \"" << A[number1 - 1] << "\" больше строки \"" << A[number2 - 1] << "\"";
				else
					cout << "строка \"" << A[number1 - 1] << "\" меньше строки \"" << A[number2 - 1] << "\"";
			}
			break;

		case 4:
			system("cls");
			cout << "введите номер строки\n";
			cin >> menu; cin.ignore();
			if (menu > 0 && menu <= size) {
				char str[20];
				cout << "Введите искомую комбинацию символов/n";
				cin >> str;
				unsigned count = A[menu - 1].serch(str);
				cout << "встречается " << count << "раз";
			}
			break;

		case 5:
			system("cls");
			cout << "введите номер строки\n";
			cin >> menu; cin.ignore();
			if (menu > 0 && menu <= size) {
				unsigned number;
				cout << "введите номер символа для замены/n";
				cin >> number;
				if (number < 1 && number >(menu - 1)) {
					cout << "символа с таким номером не существует/n";
					break;
				}
				else {
					char symbol;
					cout << "введите символ на который будет проиведена замена/n";
					cin >> symbol;
					*(A[menu - 1][number - 1]) = symbol;
				}
			}
			break;

		case 6:
			cout << "введите номер строки\n";
			cin >> menu; cin.ignore();
			if (menu > 0 && menu <= size) {
				int number = A[menu - 1].str_to_int();
				cout << number;
			}
			break;

		case 7:
			cout << "введите номер строки\n";
			cin >> menu; cin.ignore();
			if (menu > 0 && menu <= size) {
				double number = A[menu - 1].str_to_double();
				cout << number;
			}
			break;

		case 8:
			system("cls");
			cout << "Введите номер первой строки\n";
			cin >> number1; cin.ignore();
			cout << "\nВведите номер второй строки \n";
			cin >> number2; cin.ignore();
			if ((number1 > 0 && number1 <= size) && (number2 > 0 && number2 <= size)) {
				A[number1 - 1] + A[number2 - 1];
			}

			break;

		case 9:

			break;

		}
		system("pause");
	}

	return 0;
}