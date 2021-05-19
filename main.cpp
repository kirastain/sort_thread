#include "Sort.hpp"

void	generateRandom()
{
	srand((unsigned)time(0));
	uint32_t	num;
	ofstream	file;
	ofstream	file_nums;
	string		path = "input";
	string		numStr;

	try
	{
		file.open(path, ios::out | ios::binary);
		file_nums.open("test_nums");
		if (file.fail())
		{
			std::cout << "Error while opening input file" << endl;
		}
		else
		{
			std::cout << NUMBERS << endl;
			for (int i = 0; i < NUMBERS; i++)
			{
				num = rand() % RAND_MAX;
				file.write((char*)&num, sizeof(num));
				file_nums << num << endl;
			}
			file.close();
			file_nums.close();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}	
}

void	readNumbers(int position, int *count)
{
	char				*buffer = new char[BUFF_SIZE + 1];
	vector<uint32_t>	vec;
	int 				inputFile;
	uint32_t			*num;
	ofstream			temp;
	char		*numChar = new char[sizeof(uint32_t) + 1];


	try
	{
		*count = 0;
		bzero(buffer, BUFF_SIZE + 1);
		inputFile = open("input", O_RDONLY);
		int rd = 0;
		while ((rd = read(inputFile, buffer, BUFF_SIZE)) > 0)
		{
			buffer[BUFF_SIZE] = '\0';
			stringstream ss;
			ss << "temp" << position << *count;
			temp.open(ss.str());

			int i = 0;
			while (i < rd)
			{
				memcpy(numChar, &buffer[i], sizeof(uint32_t));
				numChar[sizeof(uint32_t)] = '\0';
				num = reinterpret_cast<uint32_t*>(numChar);
				vec.push_back(*num);
				i += sizeof(uint32_t);
			}
			sort(vec.begin(), vec.end());
			for (i = 0; i < vec.size(); i++)
			{
				temp << vec[i] << endl;
			}
			temp.close();
			ss.str("");
			vec.clear();
			*count = *count + 1;
			bzero(buffer, BUFF_SIZE + 1);
		}
		close(inputFile);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
}

void	mergeTwo(string fileOne, string fileTwo, int count, int countSteps, int flag)
{
	ifstream	f1;
	ifstream	f2;
	ofstream	output;
	string		outFileName;
	uint32_t	a;
	uint32_t	b;
	
	try
	{
		f1.open(fileOne);
		f2.open(fileTwo);
		if (flag == 0)
		{
			stringstream ss;
			ss << "temp" << countSteps << count;
			outFileName = ss.str();
			ss.str("");
		}
		else
		{
			outFileName = "merge";
		}
		output.open(outFileName);
		f1 >> a;
		f2 >> b;
		while (f1 && f2)
		{
			if (a <= b)
			{
				output << a << endl;
				if (!(f1 >> a))
					break;
			}
			else
			{
				output << b << endl;
				if (!(f2 >> b))
					break;
			}
		}
		if (!f1)
		{
			output << b << endl;
			while (f2 >> b)
			{
				output << b << endl;
			}
		}
		else if (!f2)
		{
			output << a << endl;
			while (f1 >> a)
			{
				output << a << endl;
			}
		}
		f1.close();
		f2.close();
		output.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
}

void	mergeFilesThread(int *numFiles, int *countSteps)
{
	stringstream	f1;
	stringstream	f2;
	int				countFiles;
	
	*countSteps = *countSteps + 1;
	while (*numFiles > 1)
	{
		countFiles = 0;
		int numThreads = *numFiles / 2;
		thread sortingThreads[numThreads];

		for (int i = 0; i < numThreads; i++)
		{
			f1 << "temp" << *countSteps - 1 << countFiles;
			f2 << "temp" << *countSteps - 1 << countFiles + 1;
			if (i == numThreads - 1 && *numFiles % 2 == 1)
			{
				mergeTwo(f1.str(), f2.str(), i, *countSteps, 1);
				f2.str("");
				f2 << "temp" << *countSteps - 1 << countFiles + 2;
				sortingThreads[i] = thread(mergeTwo, "merge", f2.str(), i, *countSteps, 0);
				f2.str("");
				f1.str("");
				break ;
			}
			sortingThreads[i] = thread(mergeTwo, f1.str(), f2.str(), i, *countSteps, 0);
			f1.str("");
			f2.str("");
			countFiles = countFiles + 2;
		}
		for (int i = 0; i < numThreads; i++)
		{
			sortingThreads[i].join();
		}
		*numFiles = *numFiles / 2;
		*countSteps = *countSteps + 1;	
	}
}

void	outputResult(int numSteps)
{
	string 		outFileName = "output";
	ofstream	outFile;
	ifstream	inFile;
	string		line;
	uint32_t	num;
	string		outLine;

	try
	{
		stringstream inFileName;
		inFileName << "temp" << numSteps - 1 << 0;
		inFile.open(inFileName.str());
		outFile.open(outFileName, ios::binary);
		while (std::getline(inFile, line))
		{
			istringstream iss1(line);
			if (!(iss1 >> num))
				break ;
			outFile.write((char*)&num, sizeof(num));
		}
		outFile.close();
		inFile.close();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	
}

int main(void)
{
	generateRandom();
	vector<uint32_t> vecOne;
	int	numFiles = 0;
	int numSteps = 0;

	thread threadRead(readNumbers, 0, &numFiles);
	threadRead.join();
	threadRead.~thread();

	int filesCanMerge = 2;
	mergeFilesThread(&numFiles, &numSteps);
	outputResult(numSteps);

	return (0);
}