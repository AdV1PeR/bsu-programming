#include <iostream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");
	
	int x, y, z;
	cin >> x >> y >> z;

	bool positive = (x > 0) && (y > 0) && (z > 0);

	if (positive) {
		cout << "Все числа положительные" << endl;
	}
	else {
		cout << "Не все числа положительные" << endl;
	}

	return 0;
}	