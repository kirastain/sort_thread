#!/bin/sh

input=$PWD/input
output=$PWD/output

echo "--------------------TEST 0: 100 BUFF_SIZE 32--------------------------------------"
g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=100 -DBUFF_SIZE=32 -O3 -o test main.cpp
./test
inputSize=$(du -b "$input" | cut -f1)
outputSize=$(du -b "$output" | cut -f1)
echo "-Input: $inputSize"
echo "Output: $outputSize"
if [ "$inputSize" -eq "$outputSize" ]; then
	echo "[OK]"
else
	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
fi
rm temp*
echo ""

echo "--------------------TEST 0: 1000--------------------------------------"
g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=1000 -O3 -o test main.cpp 
./test
inputSize=$(du -b "$input" | cut -f1)
outputSize=$(du -b "$output" | cut -f1)
echo "-Input: $inputSize"
echo "Output: $outputSize"
if [ "$inputSize" -eq "$outputSize" ]; then
	echo "[OK]"
else
	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
fi
rm temp*
echo ""

echo "--------------------TEST 0: 123456--------------------------------------"
g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=123456 -O3 -o test main.cpp 
./test
inputSize=$(du -b "$input" | cut -f1)
outputSize=$(du -b "$output" | cut -f1)
echo "-Input: $inputSize"
echo "Output: $outputSize"
if [ "$inputSize" -eq "$outputSize" ]; then
	echo "[OK]"
else
	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
fi
rm temp*
echo ""

echo "--------------------TEST 0: 1--------------------------------------"
g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=1 -O3 -o test main.cpp 
./test
inputSize=$(du -b "$input" | cut -f1)
outputSize=$(du -b "$output" | cut -f1)
echo "-Input: $inputSize"
echo "Output: $outputSize"
if [ "$inputSize" -eq "$outputSize" ]; then
	echo "[OK]"
else
	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
fi
echo ""

echo "--------------------TEST 0: 4000000--------------------------------------"
g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=4000000 -O3 -o test main.cpp 
./test
inputSize=$(du -b "$input" | cut -f1)
outputSize=$(du -b "$output" | cut -f1)
echo "-Input: $inputSize"
echo "Output: $outputSize"
if [ "$inputSize" -eq "$outputSize" ]; then
	echo "[OK]"
else
	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
fi
rm temp*
echo ""