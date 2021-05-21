#pragma once

#include <iostream>
#include <thread>
#include <exception>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <string.h>
#include <mutex>
#include <deque>
#include <queue>

#include <ctime>
#include <bitset>

#ifndef BUFF_SIZE
#define BUFF_SIZE 2621440
//#define BUFF_SIZE 8
#endif

#ifndef NUMBERS
#define NUMBERS 100000000
#endif

#define THREADS_LIMIT 4

using namespace std;
