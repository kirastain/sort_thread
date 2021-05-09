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
		for (int i = 0; i < 20; i++)
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

void	mergeTwo(string fileOne, string fileTwo, int count, int countSteps, int flag)
{
	ifstream	f1;
	ifstream	f2;
	ofstream	out1;
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
		out1.open(outFileName);
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

		while(a || b)
		{
			if (a == b)
			{
				out1 << a << endl << b << endl;
				getline(f1, line1);
				getline(f2, line2);
				istringstream iss1(line1);
				istringstream iss2(line2);
				if (!(iss1 >> a))
				{
					while (b)
					{
						out1 << b << endl;
						getline (f2, line2);
						istringstream iss2(line2);
						if (!(iss2 >> b))
							break ;
					}
					break ;
				}
				else if (!(iss2 >> b))
				{
					while (a)
					{
						out1 << a << endl;
						getline (f1, line1);
						istringstream iss1(line1);
						if (!(iss1 >> a))
							break ;
					}
					break ;
				}
			}
			else if (a < b)
			{
				out1 << a << endl;
				getline (f1, line1);
				istringstream iss1(line1);
				if (!(iss1 >> a))
				{
					while (b)
					{
						out1 << b << endl;
						getline (f2, line2);
						istringstream iss2(line2);
						if (!(iss2 >> b))
							break ;
					}
					break ;
				}
			}
			else if (b < a)
			{
				out1 << b << endl;
				getline (f2, line2);
				istringstream iss2(line2);
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
					break ;
				}
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
			//cout << "files " << f1.str() << " " << f2.str() << endl;
			mergeTwo(f1.str(), f2.str(), countFiles, *countSteps, 0);
			f1.str("");
			f2.str("");
			countFiles++;
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
		outFile.open(outFileName);
		while (getline(inFile, line))
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
	cout << "files num = " << numFiles << endl;
	threadRead.~thread();

	/* ----- Threads --- */
	
	thread threadOne(mergeFiles, &numFiles, &numSteps);
	threadOne.join();

	/* --- end thread ---- */

	//mergeFiles(numFiles, numSteps);
	outputResult(numSteps);
	
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << "time taken: " << duration.count() << endl;

	return (0);
}