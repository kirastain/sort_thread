#include "Sort.hpp"

int	main()
{
	srand((unsigned)time(0));
	uint32_t	num;
	ifstream	file;
	ofstream	testFile;
	string		path = "input";
	vector<uint32_t>	vec;

	file.open(path, ios::binary);
	if (file.fail())
	{
		std::cout << "Error while opening input file" << endl;
	}
	else
	{
		while (file.read(reinterpret_cast<char*>(&num), sizeof(uint32_t)))
		{
			vec.push_back(num);
		}
		std::sort(vec.begin(), vec.end());
		file.close();
		testFile.open("result_test", ios::binary);

		if (testFile.fail())
		{
			std::cout << "Error opening result file" << endl;
			return (1);
		}
		else
		{
			for (int i = 0; i < vec.size(); i++)
			{
				testFile.write((char*)&(vec[i]), sizeof(uint32_t));
			}
			testFile.close();
		}
	}

	return (0);
}