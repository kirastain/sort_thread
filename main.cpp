#include "Sort.hpp"

void	generateRandom()
{
	srand((unsigned)time(0));
	uint32_t	num;
	ofstream	file;
	string		path = "input";
	string		numStr;

	try
	{
		file.open(path, ios::binary);
		for (int i = 0; i < 10; i++)
		{
			num = rand() % 50; //% RAND_MAX;
			numStr = bitset<32>(num).to_string();
			cout << numStr << endl;
			file << numStr;
		}
		file.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}	
}

vector<uint32_t>	sortVector(vector<uint32_t> vec)
{
	sort(vec.begin(), vec.end());
	return (vec);
}

void	readNumbers(int position, int *count)
{
	char *buffer = new char[BUFF_SIZE];
	vector<uint32_t> vec;
	ifstream	inputFile;
	string		path = "input";
	uint32_t	num;
	char		*numChar = new char[sizeof(uint32_t) * 8];
	ofstream	temp;
	string		tempFile;

	try
	{
		inputFile.open(path, ios::binary);
		*count = 0;

		while (inputFile.read(buffer, BUFF_SIZE))
		{
			stringstream ss;
			ss << "temp" << position << *count;
			tempFile = ss.str();
			temp.open(tempFile, ios::binary);
			//cout << "str is " << buffer << endl;

			int i = 0;
			while (buffer[i])
			{
				memcpy(numChar, &buffer[i], sizeof(uint32_t) * 8);
				num = stoul(numChar, 0, 2);
				//cout << "num is " << num << endl;
				vec.push_back(num);
				i += 32;
			}
			sort(vec.begin(), vec.end());
			for (i = 0; i < vec.size(); i++)
			{
				temp << vec[i] << endl;
			}
			temp.close();
			ss.clear();
			vec.clear();
			*count = *count + 1;
		}
		inputFile.close();
		delete buffer;
		delete numChar;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
}

void	mergeTwo(string fileOne, string fileTwo, int count)
{
	ifstream	f1;
	ifstream	f2;
	ofstream	out1;
	string		outFileNmae;
	uint32_t	a;
	uint32_t	b;
	
	try
	{
		f1.open(fileOne);
		f2.open(fileTwo);
		stringstream ss;
		ss << "merge" << "0" << count;
		outFileNmae = ss.str();
		ss.clear();
		out1.open(outFileNmae);

		string line1;
		string line2;
		getline(f1, line1);
		getline(f2, line2);
		istringstream iss1(line1);
		istringstream iss2(line2);
		iss1 >> a;
		iss2 >> b;
		iss1.str("");
		iss2.str("");

		while(a && b)
		{
			cout << a << " " << b << endl;
			if (a == b)
			{
				getline(f1, line1);
				getline(f2, line2);
				istringstream iss1(line1);
				istringstream iss2(line2);
				if (!(iss1 >> a) || !(iss2 >> b))
					break ;
			}
			else if (a < b)
			{
				out1 << a << endl;
				getline (f1, line1);
				istringstream iss1(line1);
				if (!(iss1 >> a))
					break ;
			}
			else if (b < a)
			{
				out1 << b << endl;
				getline (f2, line2);
				istringstream iss2(line2);
				if (!(iss2 >> b))
					break ;
			}
		}
		if (!(iss2 >> b))
		{
			while (a)
			{
				out1 << a << endl;
				getline (f1, line1);
				istringstream iss1(line1);
				if (!(iss1 >> a))
					break ;
			}
		}
		else if (!(iss1 >> a))
		{
			while (b)
			{
				out1 << b << endl;
				getline (f2, line2);
				istringstream iss2(line2);
				if (!(iss2 >> b))
					break ;
			}
		}
		f1.close();
		f2.close();
		out1.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	
}

void	mergeFiles(int numFiles)
{
	stringstream f1;
	stringstream f2;
	int count = 0;

	if (numFiles % 2 == 0)
	{
		//easy tree
	}
	else
	{
		for (int i = 0; i < numFiles - 1; i = i + 2)
		{
			f1 << "temp" << 0 << i;
			f2 << "temp" << 0 << i + 1;
			cout << "files " << f1.str() << " " << f2.str() << endl;
			mergeTwo(f1.str(), f2.str(), count);
			f1.str("");
			f2.str("");
			count++;
		}
	}
	
}

int main(void)
{
	auto start = chrono::high_resolution_clock::now();
	//generateRandom();
	vector<uint32_t> vecOne;
	int	numFiles;


	thread threadOne(readNumbers, 0, &numFiles);
	threadOne.join();
	cout << "files num = " << numFiles << endl;
	mergeFiles(numFiles);


	vecOne = sortVector(vecOne);
	cout << "vec 1 is ";
	for (int i = 0; i < vecOne.size(); i++)
	{
		cout << vecOne[i] << " ";
	}
	cout << endl;

	
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "time taken: " << duration.count() << endl;

	return (0);
}