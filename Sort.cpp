#include "Sort.hpp"

void	readNumbers(int *numFiles, ifstream *inputFile, mutex *readMutex, mutex *fileMutex)
{
	vector<uint32_t>	vec;
	uint32_t			num;
	ofstream			temp;
	int					numsRead;

	try
	{
		while(!(inputFile->eof()))
		{
			numsRead = 0;
			num = 0;
			while(!(inputFile->eof()) && numsRead < BUFF_SIZE / 4)
			{
				readMutex->lock();
				if (!(inputFile->read(reinterpret_cast<char*>(&num), sizeof(uint32_t))))
					{
						readMutex->unlock();
						break;
					}
				readMutex->unlock();
				vec.push_back(num);
				numsRead++;
			}
			sort(vec.begin(), vec.end());
			stringstream ss;
			fileMutex->lock();
			ss << "temp" << 0 << *numFiles;
			*numFiles = *numFiles + 1;
			fileMutex->unlock();
			temp.open(ss.str());
			if (temp.fail())
			{
				std::cout << "Error creating temp files" << endl;
				exit(1);
			}
			// for (int i = 0; i < vec.size(); i++)
			// {
			// 	temp << vec[i] << endl;
			// }
			std::ostream_iterator<uint32_t> outputIterator(temp, "\n");
			std::copy(vec.begin(), vec.end(), outputIterator);
			temp.close();
			ss.str("");
			vec.clear();
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
}

void	readNumbersThread(int *numFiles)
{
	string		inputFileName = "input";
	ifstream	inputFile;
	thread		readingThreads[THREADS_LIMIT];
	mutex		readMutex;
	mutex		fileMutex;

	inputFile.open(inputFileName, ios::binary);
	if(inputFile.fail())
	{
		std::cout << "Error while opening input file" << endl;
		exit(1);
	}
	else
	{
		*numFiles = 0;
		for (int i = 0; i < THREADS_LIMIT; i++)
		{
			readingThreads[i] = thread(readNumbers, numFiles, &inputFile, &readMutex, &fileMutex);
		}
		for (int i = 0; i < THREADS_LIMIT; i++)
		{
			readingThreads[i].join();
			readingThreads[i].~thread();
		}
		inputFile.close();
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

	stringstream inFileName;
	//inFileName << "temp" << numSteps - 1 << 0;
	inFileName << "result";
	inFile.open(inFileName.str());
	outFile.open(outFileName, ios::binary);
	if (inFile.fail() || outFile.fail())
	{
		std::cout << "Error while opening file" << endl;
	}
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

void	mergeNFiles(int numFiles, int startFile, int step)
{
	vector<uint32_t>	currentNums;
	ifstream			files[numFiles];
	ofstream			resultFile;
	stringstream		ss;
	int					i;
	uint32_t			num;

	for (i = startFile; i < numFiles; i++)
	{
		ss << "temp" << step << i;
		files[i].open(ss.str());
		ss.str("");
	}
	priority_queue<pair<uint32_t, int>, vector<pair<uint32_t, int> >, std::greater<pair <uint32_t, int> > > numsMerged;
	ss << "output"; //"temp" << step + 1 << i;
	resultFile.open(ss.str());
	ss.str("");
	if (resultFile.fail())
	{
		std::cout << "Error creating result file" << endl;
		exit(1);
	}
	for (i = startFile; i < numFiles; i++)
	{
		if (files[i] >> num)
		{
			numsMerged.push(make_pair(num, i));
		}
	}
	while (!(numsMerged.empty()))
	{
		pair<uint32_t, int> numPair = numsMerged.top();
		//cout << numPair.first << endl
		resultFile.write((char*)&(numPair.first), sizeof(numPair.first)); //<< numPair.first << endl;
		numsMerged.pop();
		if (files[numPair.second] >> num)
		{
			numsMerged.push(make_pair(num, numPair.second));
		}
	}
	for (i = startFile; i < numFiles; i++)
	{
		files[i].close();
	}
	resultFile.close();
}

int main(void)
{
	//generateRandom();
	auto start = chrono::high_resolution_clock::now();
	int	numFiles = 0;
	int numSteps = 0;

	readNumbersThread(&numFiles);
	
	auto mid = chrono::high_resolution_clock::now();
	auto durationMid = chrono::duration_cast<chrono::microseconds>(mid - start);
	std::cout << "time read: " << durationMid.count() << endl;

	mergeNFiles(numFiles, 0, 0);
	// int numMerges = 0;
	// thread firstLevelOne(mergeNFiles, numFiles / 2, 0, numSteps, &numMerges);
	// thread firstLevelTwo(mergeNFiles, numFiles, numFiles / 2, numSteps, &numMerges);

	// firstLevelOne.join();
	// firstLevelTwo.join();
	// numSteps++;

	// int filesCanMerge = 2;
	// mergeFilesThread(&numFiles, &numSteps);
	//outputResult(numSteps);

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	std::cout << "time taken: " << duration.count() << endl;

	return (0);
}