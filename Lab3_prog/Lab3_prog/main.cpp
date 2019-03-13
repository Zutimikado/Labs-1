#include "agency.h"

int main()
{
	agency k(10);

	k.append("OBLADAET", 180, 2018, 4, 24, 19, 0);
	k.append("LSP", 1000, 2019, 4, 23, 20, 0);
	std::cout << k;
	k.sortname();
	std::cout << k;
	/*std::cin >> k;

	std::cout << k[0];
	std::cout << k.num() << std::endl;*/

	system("pause");
	return 0;
}