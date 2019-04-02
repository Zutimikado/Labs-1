#include "unordered_map.h"
#include <iostream>
#include <string>

int main()
{
	Unordered_map<int, const char*> my_table(10);

	my_table.test();

	system("pause");
	return 0;
}