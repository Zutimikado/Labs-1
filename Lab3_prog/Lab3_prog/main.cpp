#include "agency.h"

int main()
{
	setlocale(LC_ALL, "rus");
	agency k(10);

	k.append("OBLADAET", 500, 375, 2019, 4, 21, 19, 0);
	std::cin >> k;
	std::cout << std::endl << k[0];
	k.sortdate();
	std::cout << std::endl << k;
	k.readfile();
	k.sortname();
	std::cout << std::endl << k;
	k.book(1, 2);
	std::cout << std::endl << k;
	std::cout << k.num() << std::endl;

	system("pause");
	return 0;
}