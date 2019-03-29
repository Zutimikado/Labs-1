#include "unordered_map.h"
#include <iostream>

int main()
{
	Unordered_map<int, const char*> Myclass;

	Myclass.AddNode(1, "Anna");
	Myclass.AddNode(3, "Nikita");
	Myclass.AddNode(2, "Andrey");
	Myclass.AddNode(100, "Tanya");
	Myclass.Show();
	Myclass.DeleteAll();
	Myclass.Show();

	system("pause");
	return 0;
}