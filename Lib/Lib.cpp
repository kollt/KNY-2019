#include "pch.h"
#include <iostream>
extern "C"
{
	void __stdcall ShowInt(unsigned int n,int endl, int system)
	{
		char buffer[33];
		unsigned int t, k;
		unsigned int i = n;
		unsigned int dec, bin = 0, c;
		switch (system)
		{
		case 2:

			dec = n;
			for (c = 0; dec > 0; c++)
			{
				bin += (dec % 2) * pow(10.0, c);
				dec /= 2;
			}

			std::cout << bin;
			if (endl)
				std::cout << std::endl;
			break;
		case 8:
			unsigned int quot;
			int j, octnum[100];
			k = 1;
			quot = n;
			while (quot != 0)
			{
				octnum[k++] = quot % 8;
				quot = quot / 8;
			}
			for (j = k - 1; j > 0; j--)
			{
				std::cout << octnum[j];
			}
			if (endl)
				std::cout << std::endl;
			break;
		case 10:
			std::cout << i;
			if (endl)
				std::cout << std::endl;
			break;
		default:
			break;
		}
	}
	void __stdcall ShowChar(char n, int endl)
	{
		setlocale(LC_CTYPE, "Russian");
		std::cout << n;
		if (endl)
			std::cout << std::endl;
	}
	void __stdcall ShowBool(int n, int endl)
	{
		if (n)
			std::cout << "true";
		else
			std::cout << "false";
		if (endl)
			std::cout << std::endl;
	}
	void __stdcall ShowString(unsigned char* str, int n, int endl)
	{
			setlocale(LC_CTYPE, "Russian");
			for (int i = 0; i < n; i++) {
				std::cout << *(str+i*4);
			}
			if (endl)
				std::cout << std::endl;
	}
	int __stdcall CharToInt(char n) {
		setlocale(LC_CTYPE, "Russian");
		int num = 0;
		try {
			switch (n) {
			case '0':
				return 0;
			case '1':
				return 1;
			case '2':
				return 2;
			case '3':
				return 3;
			case '4':
				return 4;
			case '5':
				return 5;
			case '6':
				return 6;
			case '7':
				return 7;
			case '8':
				return 8;
			case '9':
				return 9;
			default:
				unsigned char* e = (unsigned char*)"В строке присутствует не цифра";
				throw e;
			}
		}
		catch (unsigned char* e) {
			std::cout << e << std::endl;
			return -1;
		}
	}
	unsigned int __stdcall StringToInt(unsigned char* str, int n) {
		setlocale(LC_CTYPE, "Russian");
		long long num = 0;
		long long max = 4294967295;
		try {
			if (str[0] == '-' && n>1) {
				unsigned char* e = (unsigned char*)"Отрицательное число";
				throw e;
			}
			for (int i = 0; i < n; i++) {
					switch (*(str + i*4)) {
					case '0':
						num += pow(10, n - i - 1) * 0;
						break;
					case '1':
						num += pow(10, n - i - 1) * 1;
						break;
					case '2':
						num += pow(10, n - i - 1) * 2;
						break;
					case '3':
						num += pow(10, n - i - 1) * 3;
						break;
					case '4':
						num += pow(10, n - i - 1) * 4;
						break;
					case '5':
						num += pow(10, n - i - 1) * 5;
						break;
					case '6':
						num += pow(10, n - i - 1) * 6;
						break;
					case '7':
						num += pow(10, n - i - 1) * 7;
						break;
					case '8':
						num += pow(10, n - i - 1) * 8;
						break;
					case '9':
						num += pow(10, n - i - 1) * 9;
						break;
					default:
						unsigned char* e = (unsigned char*)"В строке присутствует не цифра";
						throw e;
					}
					if (num > max) {
						unsigned char* e = (unsigned char*)"Переполнение";
						throw e;
					}
			}
			unsigned int a = num;
			return a;
		}
		catch (unsigned char* e) {
			std::cout << e << std::endl;
			return -1;
		}
	}
	unsigned int __stdcall inv(unsigned int x)
	{
		unsigned int y = 1;
		unsigned int n = 0;
		unsigned int tmp = 0;
		if (x == 0)
			return 1;
		while (tmp != x) {
			tmp = x & y;
			y = y << 1;
			y += 1;
			n++;
		}
		x = ~x;
		y = y >> 1;
		return x&y;
	}
	int __stdcall translate(int d, int f, unsigned int num)
	{
		unsigned int t,k;
		unsigned int i = num;
		unsigned int dec,c,bin=0;
		switch (f)
		{
		case 2:
			dec = num;
			for (c = 0; dec > 0; c++)
			{
				bin += (dec % 2) * pow(10.0, c);
				dec /= 2;
			}

			std::cout << bin;
			std::cout << "->";
			break;
		case 8:
			long int quot;
			int j, octnum[100];
			k = 1;
			quot = num;
			while (quot != 0)
			{
				octnum[k++] = quot % 8;
				quot = quot / 8;
			}
			for (j = k - 1; j > 0; j--)
			{
				std::cout << octnum[j];
			}
			std::cout << "->";
			break;
		case 10:
			std::cout << i << "->";
			break;
		default:
			break;
		}
		i = num;
		switch (d)
		{
		case 2:
			t = 0;
			while (i)
			{
				i = i / 2;
				t = i % 2;
				std::cout << t;
			}
			std::cout << std::endl;
			break;
		case 8:
			long int quot;
			int j, octnum[100];
			k = 1;
			quot = num;
			while (quot != 0)
			{
				octnum[k++] = quot % 8;
				quot = quot / 8;
			}
			for (j = k - 1; j > 0; j--)
			{
				std::cout << octnum[j];
			}
			std::cout << std::endl;
			break;
		case 10:
			std::cout << i << std::endl;
			break;
		default:
			break;
		} 	
		return d;
	}
	int __stdcall cmpstr(unsigned char* str1, unsigned char* str2) {
		if (!strcmp((const char*)str1, (const char*)str2))
			return 1;
		else
			return 0;
	}
	int __stdcall cmpuint(unsigned int n, unsigned int m) {
		if (n == m)
			return 1;
		else
			return 0;
	}
	void __stdcall stop() {
		system("pause");
	}
}