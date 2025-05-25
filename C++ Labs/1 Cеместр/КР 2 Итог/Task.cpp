#include <string.h>
#include <iostream>
using namespace std;
void main()
	{
		const int MAX = 80;

		char  str1[MAX] = { 0 };
		char  str2[MAX] = { 0 };
		char  str3[MAX] = { 0 };
		char SOGL[] = "BbCcDdFfGgKkMmNnPpQqRrSsTtWwXxZz ";
		int k = 0;

		cout << "Enter a string: ";
		cin.getline(str1, MAX);

		for (unsigned int i = 0; i<strlen(str1); i++)
		{
			if (str1[i] != '*')
				str2[k++] = str1[i];
		}
		cout << "Rezult1 = " << str2 << endl;
		int z = 0;

			for ( int j = 0; j< strlen(SOGL); j++)
			{
				for (unsigned int i = 0; i < strlen(str1); i++)
				{
					if (str1[i] == SOGL[j])
					{
						str3[z] = SOGL[j];
						z++;
						break;
					}
				}
		    }
		cout << "Rezult2 = " << str3 << endl;
	}
