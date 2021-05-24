#!/bin/sh

input=$PWD/input
output=$PWD/output

echo "--------------------TEST 0: 100 BUFF_SIZE 32--------------------------------------"
g++ -o generate -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=100 -DBUFF_SIZE=32 -O3 Generate.cpp
./generate
g++ -o generate_test -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=100 -DBUFF_SIZE=32 -O3 GenerateTest.cpp
./generate_test
g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=100 -DBUFF_SIZE=32 -O3 -o sort Sort.cpp
./sort
inputSize=$(du -b "$input" | cut -f1)
outputSize=$(du -b "$output" | cut -f1)
echo "-Input: $inputSize"
echo "Output: $outputSize"
if [ "$inputSize" -eq "$outputSize" ]; then
	echo "[OK]"
else
	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
fi
echo "Sort test: "
diff output result_test
rm temp*
echo ""

echo "--------------------TEST 0: 1000--------------------------------------"
g++ -o generate -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=1000 -O3 Generate.cpp
./generate
g++ -o generate_test -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=1000 -O3 GenerateTest.cpp
./generate_test
g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=1000 -O3 -o sort Sort.cpp 
./sort
inputSize=$(du -b "$input" | cut -f1)
outputSize=$(du -b "$output" | cut -f1)
echo "-Input: $inputSize"
echo "Output: $outputSize"
if [ "$inputSize" -eq "$outputSize" ]; then
	echo "[OK]"
else
	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
fi
echo "Sort test: "
diff output result_test
rm temp*
echo ""

echo "--------------------TEST 0: 123456--------------------------------------"
g++ -o generate -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=123456 -O3 Generate.cpp
./generate
g++ -o generate_test -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=123456 -O3 GenerateTest.cpp
./generate_test
g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=123456 -O3 -o sort Sort.cpp 
./sort
inputSize=$(du -b "$input" | cut -f1)
outputSize=$(du -b "$output" | cut -f1)
echo "-Input: $inputSize"
echo "Output: $outputSize"
if [ "$inputSize" -eq "$outputSize" ]; then
	echo "[OK]"
else
	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
fi
echo "Sort test: "
diff output result_test
rm temp*
echo ""

echo "--------------------TEST 0: 1--------------------------------------"
g++ -o generate -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=1 -O3 Generate.cpp
./generate
g++ -o generate_test -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=1 -O3 GenerateTest.cpp
./generate_test
g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=1 -O3 -o sort Sort.cpp 
./sort
inputSize=$(du -b "$input" | cut -f1)
outputSize=$(du -b "$output" | cut -f1)
echo "-Input: $inputSize"
echo "Output: $outputSize"
if [ "$inputSize" -eq "$outputSize" ]; then
	echo "[OK]"
else
	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
fi
echo "Sort test: "
diff output result_test
echo ""

echo "--------------------TEST 0: 4000000--------------------------------------"
g++ -o generate -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=4000000 -O3 Generate.cpp
./generate
g++ -o generate_test -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=4000000 -O3 GenerateTest.cpp
./generate_test
g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=4000000 -O3 -o sort Sort.cpp 
./sort
inputSize=$(du -b "$input" | cut -f1)
outputSize=$(du -b "$output" | cut -f1)
echo "-Input: $inputSize"
echo "Output: $outputSize"
if [ "$inputSize" -eq "$outputSize" ]; then
	echo "[OK]"
else
	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
fi
echo "Sort test: "
diff output result_test
rm temp*
echo ""

# echo "--------------------TEST 0: 10000000--------------------------------------"
# g++ -o generate -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=10000000 -O3 Generate.cpp
# ./generate
# g++ -o generate_test -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=10000000 -O3 GenerateTest.cpp
# ./generate_test
# g++ -pthread -w -std=c++14 -D_NDEBUG -DNUMBERS=10000000 -O3 -o sort Sort.cpp 
# ./sort
# inputSize=$(du -b "$input" | cut -f1)
# outputSize=$(du -b "$output" | cut -f1)
# echo "-Input: $inputSize"
# echo "Output: $outputSize"
# if [ "$inputSize" -eq "$outputSize" ]; then
# 	echo "[OK]"
# else
# 	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
# fi
# echo "Sort test: "
# diff output result_test
# rm temp*
# echo ""

# echo "--------------------TEST 0: 373543891--------------------------------------"
# g++ -pthread -w -std=c++14 -D_NDEBUG -O3 -o sort Sort.cpp 
# ./sort
# inputSize=$(du -b "$input" | cut -f1)
# outputSize=$(du -b "$output" | cut -f1)
# echo "-Input: $inputSize"
# echo "Output: $outputSize"
# if [ "$inputSize" -eq "$outputSize" ]; then
# 	echo "[OK]"
# else
# 	echo "!!!!!!!!ERROR!!!!!!!!!: sizes do not match!"
# fi
# echo "Sort test: "
# diff output result_test
# rm temp*
# echo ""