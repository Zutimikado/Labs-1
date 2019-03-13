#include "agency.h"

int main()
{
	agency k(10);

	k.append("OBLADAET", 180, 2019, 4, 21, 19, 0);
	std::cin >> k;

	std::cout << k[0];

	system("pause");
	return 0;
}