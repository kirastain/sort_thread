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
		for (int i = 0; i < 10000; i++)
		{
			num = rand() % 5000; //% RAND_MAX;
			numStr = bitset<32>(num).to_string();
			//std::cout << numStr << endl;
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
	char *buffer = new char[BUFF_SIZE + 1];
	vector<uint32_t> vec;
	//ifstream	inputFile;
	//string		path = "input";
	int inputFile;
	uint32_t	num;
	char		*numChar = new char[sizeof(uint32_t) * 8];
	ofstream	temp;

	try
	{
		//inputFile.open(path, ios::binary);

		*count = 0;
		bzero(buffer, BUFF_SIZE + 1);
		inputFile = open("input", O_RDONLY);
		//while (inputFile.read(buffer, BUFF_SIZE))
		while ((read(inputFile, buffer, BUFF_SIZE)) > 0)
		{
			//std::cout << "gor line with count = " << *count << endl;
			stringstream ss;
			ss << "temp" << position << *count;
			temp.open(ss.str(), ios::binary);
			//std::cout << "str is " << buffer << endl;

			int i = 0;
			while (buffer[i])
			{
				memcpy(numChar, &buffer[i], sizeof(uint32_t) * 8);
				num = stoul(numChar, 0, 2);
				//std::cout << "num is " << num << endl;
				vec.push_back(num);
				i += 32;
			}
			sort(vec.begin(), vec.end());
			//std::cout << "vec " << *count << " is ";
			for (i = 0; i < vec.size(); i++)
			{
				//std::cout << vec[i] << " ";
				temp << vec[i] << endl;
			}
			//std::cout << endl;
			temp.close();
			ss.str("");
			vec.clear();
			*count = *count + 1;
			bzero(buffer, BUFF_SIZE + 1);
		}
		//inputFile.close();
		close(inputFile);
		delete numChar;
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
		// string line1;
		// string line2;
		// std::getline(f1, line1);
		// std::getline(f2, line2);
		// istringstream iss1(line1);
		// istringstream iss2(line2);
		f1 >> a;
		f2 >> b;

		//std::cout << "iss are " << iss1.str() << " " << iss2.str() << endl;
		//std::cout << "nums are " << a << " " << b << endl;
		while (f1 && f2)
		{
			//std::cout << "curr is " << a << " " << b << endl;
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
			//std::cout << "empty file 1" << endl;
			output << b << endl;
			while (f2 >> b)
			{
				output << b << endl;
			}
		}
		else if (!f2)
		{
			//std::cout << "empty file 2" << endl;
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

int		mergeFiles(int *numFiles, int *countSteps)
{
	stringstream f1;
	stringstream f2;
	int countFiles;
	*countSteps = *countSteps + 1;

	while (*numFiles > 1)
	{
		countFiles = 0;
		for (int i = 0; i < *numFiles - 1; i = i + 2)
		{
			f1 << "temp" << *countSteps - 1 << i;
			f2 << "temp" << *countSteps - 1 << i + 1;
			if (*numFiles % 2 == 1 && i == *numFiles - 3)
			{
				mergeTwo(f1.str(), f2.str(), countFiles, *countSteps, 1);
				f2.str("");
				f2 << "temp" << *countSteps - 1 << i + 2;
				mergeTwo("merge", f2.str(), countFiles, *countSteps, 0);
				f2.str("");
				f1.str("");
				break ;
			}
			//std::cout << "files " << f1.str() << " " << f2.str() << endl;
			mergeTwo(f1.str(), f2.str(), countFiles, *countSteps, 0);
			f1.str("");
			f2.str("");
			countFiles++;
		}
		*numFiles = *numFiles / 2;
		*countSteps = *countSteps + 1;	
	}
}

void	mergeFilesThread(int *numFiles, int *countSteps, int filesCanMerge, int position)
{
	stringstream f1;
	stringstream f2;
	int countFiles;
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
			//std::cout << "files " << f1.str() << " " << f2.str() << endl;
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
		std::cout << "result in file " << inFileName.str() << endl;
		inFile.open(inFileName.str());
		outFile.open(outFileName);
		while (std::getline(inFile, line))
		{
			istringstream iss1(line);
			if (!(iss1 >> num))
				break ;
			outLine = bitset<32>(num).to_string();
			outFile << outLine;
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
	auto start = chrono::high_resolution_clock::now();
	//generateRandom();
	vector<uint32_t> vecOne;
	int	numFiles = 0;
	int numSteps = 0;

	thread threadRead(readNumbers, 0, &numFiles);
	threadRead.join();
	std::cout << "files num = " << numFiles << endl;
	threadRead.~thread();

	/* ----- Threads --- */
	int filesCanMerge = 2;
	
	mergeFiles(&numFiles, &numSteps);
	//mergeFilesThread(&numFiles, &numSteps, filesCanMerge, 0);

	/* --- end thread ---- */

	//mergeFiles(numFiles, numSteps);
	outputResult(numSteps);
	
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	std::cout << "time taken: " << duration.count() << endl;

	return (0);
}