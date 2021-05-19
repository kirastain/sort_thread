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
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mutex>

#include <ctime>
#include <bitset>

#ifndef BUFF_SIZE
#define BUFF_SIZE 240000000
#endif

#ifndef NUMBERS
#define NUMBERS 10000000
#endif

#define THREADS_LIMIT 10

using namespace std;
