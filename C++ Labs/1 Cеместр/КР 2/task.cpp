#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;
int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(nullptr));
    cout << "Как получить число?" << endl;
    cout << "(1 - случайно, 2 - ввести): ";
    int select;
    cin >> select;
    unsigned int value = 0;
    switch (select)
    {
    	case '1':
            value = rand();
    	    break;
    	case '2':
            cout << "Введите число: ";
            cin >> value;
            break;
    	default:
    	    return 0;
    }

    char a[100] = {0};
    while (value > 0)
    {
        if (value % 2==1)
        {
            a[d] = '1';
        }
        else
        {
            a[d] = '0';
        }
        d++;
        value /= 2;
    }
    cout << a << endl;
}
