#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>
#include <map>

using std::cout;
using std::cin;
using std::ifstream;
using std::vector;
using std::pair;
using std::find;
using std::map;

const int n = 5;

struct figure
{
	vector<pair<int, int>> coordinatesv;
	pair<int, int> starting_point;
};

void print(vector<vector<char>> a);
bool can_be_replaced(const vector<vector<char>>& originalv, vector<vector<char>>& newv);
bool try_place(const vector<vector<char>>& originalv, vector<vector<char>>& newv, map<char, figure>& figuresm);

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	ifstream input("input.txt");
	if (!input)
	{
		cout << "Файл input.txt не был открыт!\n";
		system("pause");
	}
	else
	{
		int choice;
		bool ext = false;
		vector<vector<char>> a;
		a.resize(n);
		for (int i = 0; i < n; ++i)
		{
			a[i].resize(n);
			for (int j = 0; j < n; ++j)
			{
				input >> a[i][j];
			}
		}
		cout << '\n';
		print(a);
		cout << '\n';
		vector<vector<char>> newv;
		newv.resize(n);
		for (int i = 0; i < n; ++i)
		{
			newv[i].resize(n);
			for (int j = 0; j < n; ++j)
			{
				newv[i][j] = ' ';
			}
		}
		while (!ext)
		{
			cout << "Введите номер необходимого пункта\n";
			cout << "1. Выполнение программы.\n";
			cout << "0. Завершение программы.\n\n";
			choice = _getwch();
			switch (choice)
			{
			case '1': //
			{
				if (can_be_replaced(a, newv))
				{
					cout << "Фигурки могут быть переставлены!\n\n";
					print(newv);
					cout << '\n';
				}
				else
				{
					cout << "Фигурки не могут быть переставлены!\n\n";
				}
			}
			break; //

			case '0': //Завершение программы
				ext = 1;
				break; //Завершение программы

			default:
				cout << "Неверный формат ввода, попробуйте ещё раз\n\n";
				break;
			}
		}
	}
	input.close();
	return 0;
}
//=================================================================================
void print(vector<vector<char>> a)
{
	for (int i = 0; i < a.size(); ++i)
	{
		cout << ' ';
		for (int j = 0; j < a[i].size(); ++j)
			cout << a[i][j] << ' ';
		cout << '\n';
	}
}

bool can_be_replaced(const vector<vector<char>>& originalv, vector<vector<char>>& newv)
{
	bool result = false;
	map<char, figure> figuresm;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (figuresm.find(originalv[i][j]) == figuresm.end())
			{
				figure f;
				f.coordinatesv.push_back(pair<int, int>(0, 0));
				f.starting_point = pair<int, int>(i, j);
				figuresm[originalv[i][j]] = f;
			}
			else
			{
				figuresm[originalv[i][j]].coordinatesv.push_back(pair<int, int>(i - figuresm[originalv[i][j]].starting_point.first, j - figuresm[originalv[i][j]].starting_point.second));
			}
		}
	}
	if (try_place(originalv, newv, figuresm) == true)
		result = true;
	return result;
}

bool try_place(const vector<vector<char>>& originalv, vector<vector<char>>& newv, map<char, figure>& figuresm)
{
	bool result = true;
	if (!figuresm.empty())
	{
		result = false;
		char curc = figuresm.begin()->first;
		//
		if (curc == 'H')
		{
			cout << "";
		}
		//
		figure curf = figuresm.begin()->second;
		figuresm.erase(figuresm.begin());
		bool placed = false;
		for (int i = 0; i < n && !placed; ++i)
		{
			for (int j = 0; j < n && !placed; ++j)
			{
				vector<pair<int, int>>::iterator it = curf.coordinatesv.begin();
				bool can_place = true;
				while (it != curf.coordinatesv.end() && can_place)
				{
					int i2 = it->first, j2 = it->second;
					if (i + i2 < n && i + i2 >= 0 && j + j2 < n && j + j2 >= 0 && newv[i + i2][j + j2] == ' ')
					{
						newv[i + i2][j + j2] = curc;
						if (originalv == newv)
							can_place = false;
						++it;
					}
					else
					{
						can_place = false;
					}
				}
				if (can_place)
				{
					print(newv);
					cout << "\n++++++++++++++++++++++++++++++++++++++++\n\n";
					if (try_place(originalv, newv, figuresm) == true)
						placed = true;
					else
					{
						print(newv);
						cout << '\n';
						int i2, j2;
						while (it != curf.coordinatesv.begin())
						{
							if (it == curf.coordinatesv.end())
								--it;
							i2 = it->first;
							j2 = it->second;
							if (i + i2 < n && i + i2 >= 0 && j + j2 < n && j + j2 >= 0 && newv[i + i2][j + j2] == curc)
								newv[i + i2][j + j2] = ' ';
							--it;
						}
						i2 = it->first;
						j2 = it->second;
						if (i + i2 < n && i + i2 >= 0 && j + j2 < n && j + j2 >= 0 && newv[i + i2][j + j2] == curc)
							newv[i + i2][j + j2] = ' ';
						print(newv);
						cout << "\n----------------------------------------\n\n";
					}
				}
				else
				{
					int i2, j2;
					while (it != curf.coordinatesv.begin())
					{
						print(newv);
						cout << '\n';
						if (it == curf.coordinatesv.end())
							--it;
						i2 = it->first;
						j2 = it->second;
						if (i + i2 < n && i + i2 >= 0 && j + j2 < n && j + j2 >= 0 && newv[i + i2][j + j2] == curc)
							newv[i + i2][j + j2] = ' ';
						--it;
						print(newv);
						cout << '\n';
					}
					i2 = it->first;
					j2 = it->second;
					if (i + i2 < n && i + i2 >= 0 && j + j2 < n && j + j2 >= 0 && newv[i + i2][j + j2] == curc)
					{
						newv[i + i2][j + j2] = ' ';
						print(newv);
						cout << '\n';
					}
				}
			}
		}
		if (placed)
		{
			result = true;
		}
		else
		{
			figuresm[curc] = curf;
		}
	}
	return result;
}