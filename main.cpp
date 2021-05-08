#include "Sort.hpp"

void				sortVector(vector<uint32_t> vec)
{
	sort(vec.begin(), vec.end());
}

void	readNumbers(vector<uint32_t> *vec, int position)
{
	char *buffer = new char[BUFF_SIZE];
	ifstream	inputFile;
	string		path = "input";

	try
	{
		inputFile.open(path, ios::binary);
		while (inputFile.read(buffer, BUFF_SIZE))
		{
			cout << "str is " << buffer << endl;
			uint32_t num = stoul(buffer, 0, 2);
			cout << "num is " << num << endl;
			vec->push_back(num);
		}

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
}

int main(void)
{
	auto start = chrono::high_resolution_clock::now();
	vector<uint32_t> vecOne;
	vector<uint32_t> vecTwo;

	void *status;

	thread threadOne(readNumbers, &vecOne, 0);
	thread threadTwo(readNumbers, &vecTwo, 1);
	threadOne.join();
	threadTwo.join();
	
	cout << endl;
	for (int i = 0; i < vecOne.size(); i++)
	{
		cout << "vec 1 is " << vecOne[i] << endl;
	}

	for (int i = 0; i < vecTwo.size(); i++)
	{
		cout << "vec 2 is " << vecTwo[i] << endl;
	}

	
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "time taken: " << duration.count() << endl;

	return (0);
}