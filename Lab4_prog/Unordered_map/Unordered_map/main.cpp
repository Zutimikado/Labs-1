#include "unordered_map.h"
#include <iostream>
#include <string>

int main()
{
	Unordered_map<int, const char*> my_table(10);

	my_table.insert(8, "Nikita");
	my_table.insert(19, "Anna");
	my_table.insert(17, "Andrei");
	my_table.insert(23, "Tanya");

	my_table.show();
	my_table.insert(18, "Masha");
	my_table.insert(3, "Nastya");
	std::cout << std::endl;
	my_table.show();

	

	system("pause");
	return 0;
}