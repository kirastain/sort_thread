#include "Sort.hpp"

int main(void)
{
	ifstream	inputFile;
	string		path = "input";
	char		*buffer;
	vector<uint32_t> vec;

	try
	{
		inputFile.open(path, ios::binary);
		buffer = new char[BUFF_SIZE];
		while (inputFile.read(buffer, BUFF_SIZE))
		{
			cout << "str is " << buffer << endl;
			uint32_t num = stoul(buffer, 0, 2);
			cout << "num is " << num << endl;
			vec.push_back(num);
		}

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}

	sort(vec.begin(), vec.end());
	
	cout << endl;
	for (int i = 0; i < vec.size(); i++)
	{
		cout << "vec is " << vec[i] << endl;
	}

	return (0);
}