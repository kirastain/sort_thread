#include "Sort.hpp"

int	main()
{
	srand((unsigned)time(0));
	uint32_t	num;
	ofstream	file;
	string		path = "input";

	file.open(path, ios::out | ios::binary);
	if (file.fail())
	{
		std::cout << "Error while opening input file" << endl;
	}
	else
	{
		for (int i = 0; i < NUMBERS; i++)
		{
			num = rand() % RAND_MAX;
			file.write((char*)&num, sizeof(num));
		}
		cout << endl;
		file.close();
	}

	return (0);
}