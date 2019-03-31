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
	my_table.insert(18, "Masha");
	my_table.insert(3, "Nastya");
	my_table.show();
	std::cout << my_table.count() << std::endl;
	std::cout << my_table.size() << std::endl;
	std::cout << my_table.empty() << std::endl;
	my_table.clear();
	my_table.show();
	std::cout << my_table.count() << std::endl;
	std::cout << my_table.size() << std::endl;
	std::cout << my_table.empty() << std::endl;
	

	system("pause");
	return 0;
}