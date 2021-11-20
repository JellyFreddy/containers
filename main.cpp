#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <list>
#include <stdexcept>
#include <sys/time.h>


#include "sample_class.hpp"

int main() {
	// 1 allocator constructor //

	struct timeval tp;

	typedef std::vector<sampleClass> used_vector_sampleClass;
	typedef std::vector<int> used_vector_int;
	typedef std::map<int, sampleClass> used_map_sampleClass;
	typedef std::map<int, int> used_map_int;
	typedef std::stack<sampleClass> used_stack_sampleClass;
	std::vector<int>::iterator iter;
	std::vector<int>::const_iterator const_iter;

	const_iter = iter;
	used_vector_sampleClass myVector;

	/// Vector

	std::cout << std::endl << "\033[1;33m VECTOR \033[0m" << std::endl << std::endl;

	// 1.1 push_back

	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000000 + tp.tv_usec;

	for(int i = 0; i < 100; i++) {
		myVector.push_back(sampleClass(i));
	}

	for(int i = 0; i < 100; i++) {
		if (myVector[i] != sampleClass(i)) {
			std::cout << "\033[1;31m1.1 push back - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
		if (myVector[100 - 1 - i] == sampleClass(i)) {
			std::cout << "\033[1;31m1.1 push back - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.1 push back - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.2 pop_back

	if (myVector.size() != 100) {
		std::cout << "\033[1;31m1.2 pop back - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for (int i = 0; i < 50; i++)
		myVector.pop_back();
	if (myVector.size() != 50) {
		std::cout << "\033[1;31m1.2 pop back - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	if (myVector.back() != sampleClass(49)) {
		std::cout << "\033[1;31m1.2 pop back - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.2 pop back - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.3 insert

	// 1.3.1 insert one element

	// normal condition

	// one element insert
	used_vector_sampleClass::iterator it = myVector.begin();
	it += 5;
	myVector.insert(it, sampleClass(100));
	if (myVector[5] != sampleClass(100) || myVector.size() != 51) {
		std::cout << "\033[1;31m1.3 insert - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// multiple elements insert
	it++;
	myVector.insert(it, 6, sampleClass(21));
	for (int i = 6; i < 12; i++) {
		if (myVector[i] != sampleClass(21)) {
			std::cout << "\033[1;31m1.3 insert - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (myVector.size() != 57) {
		std::cout << "\033[1;31m1.3 insert - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// iterators insert
	used_vector_sampleClass vectorToCopyFrom(5, sampleClass(5));
	it += 6;
	myVector.insert(it, vectorToCopyFrom.begin(), vectorToCopyFrom.end());
	for (int i = 12; i < 17; i++) {
		if (myVector[i] != sampleClass(5)) {
			std::cout << "\033[1;31m1.3 insert - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}

	// overflows capacity
	int freeSpace = myVector.capacity() - myVector.size();
	try {
		myVector.insert(it, freeSpace + 10, sampleClass(42));
	} catch (std::exception ex) {
		std::cout << "\033[1;31m1.3 insert - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// insert to the end element
	myVector.insert(myVector.end(), sampleClass(234));

	std::cout << "\033[1;32m1.3 insert - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.4 let's check clear

	myVector.clear();
	if (myVector.size() != 0) {
		std::cout << "\033[1;31m1.4 clear - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.4 clear - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.5 let's check erase

	// 1.5.1 simple erase

	for(int i = 0 ; i < 7; i++)
		myVector.push_back(sampleClass(i));
	it = myVector.begin();
	it += 3;
	myVector.erase(it);

	if (myVector[3] == sampleClass(3)) {
		std::cout << "\033[1;31m1.5 erase - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	// 1.5.1 erase array
	myVector.erase(it, myVector.end());

	if (myVector.size() != 3) {
		std::cout << "\033[1;31m1.5 erase - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.5 erase - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.6 let's try resize

	// resize more than size
	myVector.clear();
	myVector.resize(5, sampleClass(42));
	if (myVector.size() != 5 || myVector[4] != sampleClass(42)) {
		std::cout << "\033[1;31m1.6 resize - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// resize less than size
	myVector.resize(4, sampleClass(21));
	if (myVector.size() != 4) {
		std::cout << "\033[1;31m1.6 resize - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// resize more than capacity
	int capacity = myVector.capacity();
	myVector.resize(capacity + 10, sampleClass(42));
	if (myVector.capacity() == capacity || myVector[capacity] != sampleClass(42)) {
		std::cout << "\033[1;31m1.6 resize - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.6 resize - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.7 let's try swap
	vectorToCopyFrom = used_vector_sampleClass(5, sampleClass(5));
	capacity = myVector.size();
	myVector.swap(vectorToCopyFrom);
	for(int i = 0; i < vectorToCopyFrom.size(); i++) {
		if (vectorToCopyFrom[i] != sampleClass(42)) {
			std::cout << "\033[1;31m1.7 swap - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	for(int i = 0; i < myVector.size(); i++) {
		if (myVector[i] != sampleClass(5)) {
			std::cout << "\033[1;31m1.7 swap - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (myVector.size() != 5 || vectorToCopyFrom.size() != capacity) {
		std::cout << "\033[1;31m1.7 swap - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.7 swap - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.8 let's try assign

	// 1.8.1 simple assign
	myVector.assign(8, sampleClass(-42));
	if (myVector.size() != 8) {
		std::cout << "\033[1;31m1.8 assign - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != myVector.size(); i++) {
		if (myVector[i] != sampleClass(-42)) {
			std::cout << "\033[1;31m1.8 assign - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	vectorToCopyFrom.clear();
	for(int i = 0; i != -6; i--)
		vectorToCopyFrom.push_back(sampleClass(i));

	// 1.8.2 iterators assign
	myVector.assign(vectorToCopyFrom.begin(), vectorToCopyFrom.end());
	if (myVector.size() != 6 ) {
		std::cout << "\033[1;31m1.8 assign - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != myVector.size(); i++) {
		if (myVector[i] != sampleClass((-1) * i)) {
			std::cout << "\033[1;31m1.8 assign - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.8 assign - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.9 let's try operator=
	vectorToCopyFrom.clear();
	for(int i = 0; i != 42; i++)
		vectorToCopyFrom.push_back(sampleClass(i));

	myVector = vectorToCopyFrom;
	for(int i = 0; i < myVector.size(); i++) {
		if (myVector[i] != sampleClass(i)) {
			std::cout << "\033[1;31m1.9 operator= - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.9 operator= - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.10 let's check iterators
	for(it = myVector.begin(); it != myVector.end(); it++)
		(*it).value()++;

	it = myVector.begin();
	for(int i = 0; it != myVector.end(); it++, i++) {
		if (*it != sampleClass(1 + i)) {
			std::cout << "\033[1;31m1.10 iterators - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.10 iterators - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.11 let's check reverse iterators
	used_vector_sampleClass::reverse_iterator rit;
	for(rit = myVector.rbegin(); rit != myVector.rend(); rit++)
		((*rit).value())--;

	rit = myVector.rbegin();
	for(int i = myVector.size() - 1; rit != myVector.rend(); rit++, i--) {
		if (*rit != sampleClass(i)) {
			std::cout << "\033[1;31m1.11 reverse iterators - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.11 reverse iterators - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.12 let's try at
	try {
		myVector.at(myVector.size());
		std::cout << "\033[1;31m1.12 at - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	} catch (std::exception ex) {
		std::cout << "\033[1;32m1.12 at - when allocator constructor - functions as expected\033[0m" << std::endl;
	}

	// 1.13 let's check size

	myVector.resize(5, sampleClass(5));
	if (myVector.size() != 5) {
		std::cout << "\033[1;31m1.13 size - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.13 size - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.14 let's check reserve

	myVector.reserve(100);
	if (myVector.capacity() != 100) {
		std::cout << "\033[1;31m1.14 reserve and capacity - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.14 reserve and capacity - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.15 let's check empty

	if (myVector.empty()) {
		std::cout << "\033[1;31m1.15 empty - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	myVector.clear();
	if (!myVector.empty()) {
		std::cout << "\033[1;31m1.15 empty - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.15 empty - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.16 let's check front

	for(int i = 0; i < 6; i++)
		myVector.push_back(sampleClass(i));
	if(myVector.front() != sampleClass(0)) {
		std::cout << "\033[1;31m1.16 front - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.16 front - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.17 let's check back

	if(myVector.back() != sampleClass(5)) {
		std::cout << "\033[1;31m1.17 back - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.17 back - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.18 let's check operator==
	vectorToCopyFrom.clear();
	for(int i = 0; i < 6; i++)
		vectorToCopyFrom.push_back(sampleClass(i));
	if (myVector != vectorToCopyFrom) {
		std::cout << "\033[1;31m1.18 operator== - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.18 operator== - when allocator constructor - functions as expected\033[0m" << std::endl;

	// 1.19 let's check operator<

	used_vector_int numericVectorOne;
	numericVectorOne.push_back(0);
	numericVectorOne.push_back(1);
	numericVectorOne.push_back(2);
	numericVectorOne.push_back(3);
	used_vector_int numericVectorTwo;
	numericVectorTwo.push_back(0);
	numericVectorTwo.push_back(1);
	numericVectorTwo.push_back(2);
	numericVectorTwo.push_back(2);

	if (numericVectorOne < numericVectorTwo) {
		std::cout << "\033[1;31m1.19 operator< - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	numericVectorOne.pop_back();
	if (numericVectorTwo < numericVectorOne) {
		std::cout << "\033[1;31m1.19 operator< - when allocator constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.19 operator< - when allocator constructor - functions as expected\033[0m" << std::endl;

	///

	// 1.1 push_back

	used_vector_sampleClass myVectorCount(0, sampleClass(0));

	for(int i = 0; i < 100; i++) {
		myVectorCount.push_back(sampleClass(i));
	}

	for(int i = 0; i < 100; i++) {
		if (myVectorCount[i] != sampleClass(i)) {
			std::cout << "\033[1;31m1.20 push back - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
		if (myVectorCount[100 - 1 - i] == sampleClass(i)) {
			std::cout << "\033[1;31m1.20 push back - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.20 push back - when allocator Count - functions as expected\033[0m" << std::endl;

	// 1.2 pop_back

	if (myVectorCount.size() != 100) {
		std::cout << "\033[1;31m1.21 pop back - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for (int i = 0; i < 50; i++)
		myVectorCount.pop_back();
	if (myVectorCount.size() != 50) {
		std::cout << "\033[1;31m1.21 pop back - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	if (myVectorCount.back() != sampleClass(49)) {
		std::cout << "\033[1;31m1.21 pop back - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.21 pop back - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.3 insert

	// 1.3.1 insert one element

	// normal condition

	// one element insert
	used_vector_sampleClass::iterator itCount = myVectorCount.begin();
	itCount += 5;
	myVectorCount.insert(itCount, sampleClass(100));
	if (myVectorCount[5] != sampleClass(100) || myVectorCount.size() != 51) {
		std::cout << "\033[1;31m1.22 insert - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// multiple elements insert
	itCount++;
	myVectorCount.insert(itCount, 6, sampleClass(21));
	for (int i = 6; i < 12; i++) {
		if (myVectorCount[i] != sampleClass(21)) {
			std::cout << "\033[1;31m1.22 insert - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (myVectorCount.size() != 57) {
		std::cout << "\033[1;31m1.22 insert - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// iterators insert
	used_vector_sampleClass vectorToCopyFromCount(5, sampleClass(5));
	itCount += 6;
	myVectorCount.insert(itCount, vectorToCopyFromCount.begin(), vectorToCopyFromCount.end());
	for (int i = 12; i < 17; i++) {
		if (myVectorCount[i] != sampleClass(5)) {
			std::cout << "\033[1;31m1.22 insert - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}

	// overflows capacity
	int freeSpaceCount = myVectorCount.capacity() - myVectorCount.size();
	try {
		myVectorCount.insert(itCount, freeSpaceCount + 10, sampleClass(42));
	} catch (std::exception ex) {
		std::cout << "\033[1;31m1.22 insert - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// insert to the end element
	myVectorCount.insert(myVectorCount.end(), sampleClass(234));

	std::cout << "\033[1;32m1.22 insert - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.4 let's check clear

	myVectorCount.clear();
	if (myVectorCount.size() != 0) {
		std::cout << "\033[1;31m1.23 clear - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.23 clear - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.5 let's check erase

	// 1.5.1 simple erase

	for(int i = 0 ; i < 7; i++)
		myVectorCount.push_back(sampleClass(i));
	itCount = myVectorCount.begin();
	itCount += 3;
	myVectorCount.erase(itCount);

	if (myVectorCount[3] == sampleClass(3)) {
		std::cout << "\033[1;31m1.24 erase - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	// 1.5.1 erase array
	myVectorCount.erase(itCount, myVectorCount.end());

	if (myVectorCount.size() != 3) {
		std::cout << "\033[1;31m1.24 erase - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.24 erase - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.6 let's try resize

	// resize more than size
	myVectorCount.clear();
	myVectorCount.resize(5, sampleClass(42));
	if (myVectorCount.size() != 5 || myVectorCount[4] != sampleClass(42)) {
		std::cout << "\033[1;31m1.25 resize - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// resize less than size
	myVectorCount.resize(4, sampleClass(21));
	if (myVectorCount.size() != 4) {
		std::cout << "\033[1;31m1.25 resize - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// resize more than capacity
	int capacityCount = myVectorCount.capacity();
	myVectorCount.resize(capacityCount + 10, sampleClass(42));
	if (myVectorCount.capacity() == capacityCount || myVectorCount[capacityCount] != sampleClass(42)) {
		std::cout << "\033[1;31m1.25 resize - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.25 resize - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.7 let's try swap
	vectorToCopyFromCount = used_vector_sampleClass(5, sampleClass(5));
	capacityCount = myVectorCount.size();
	myVectorCount.swap(vectorToCopyFromCount);
	for(int i = 0; i < vectorToCopyFromCount.size(); i++) {
		if (vectorToCopyFromCount[i] != sampleClass(42)) {
			std::cout << "\033[1;31m1.26 swap - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	for(int i = 0; i < myVectorCount.size(); i++) {
		if (myVectorCount[i] != sampleClass(5)) {
			std::cout << "\033[1;31m1.26 swap - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (myVectorCount.size() != 5 || vectorToCopyFromCount.size() != capacityCount) {
		std::cout << "\033[1;31m1.26 swap - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.26 swap - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.8 let's try assign

	// 1.8.1 simple assign
	myVectorCount.assign(8, sampleClass(-42));
	if (myVectorCount.size() != 8) {
		std::cout << "\033[1;31m1.27 assign - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != myVectorCount.size(); i++) {
		if (myVectorCount[i] != sampleClass(-42)) {
			std::cout << "\033[1;31m1.27 assign - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	vectorToCopyFromCount.clear();
	for(int i = 0; i != -6; i--)
		vectorToCopyFromCount.push_back(sampleClass(i));

	// 1.8.2 iterators assign
	myVectorCount.assign(vectorToCopyFromCount.begin(), vectorToCopyFromCount.end());
	if (myVectorCount.size() != 6 ) {
		std::cout << "\033[1;31m1.27 assign - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != myVectorCount.size(); i++) {
		if (myVectorCount[i] != sampleClass((-1) * i)) {
			std::cout << "\033[1;31m1.27 assign - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.27 assign - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.9 let's try operator=
	vectorToCopyFromCount.clear();
	for(int i = 0; i != 42; i++)
		vectorToCopyFromCount.push_back(sampleClass(i));

	myVectorCount = vectorToCopyFromCount;
	for(int i = 0; i < myVectorCount.size(); i++) {
		if (myVectorCount[i] != sampleClass(i)) {
			std::cout << "\033[1;31m1.28 operator= - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.28 operator= - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.10 let's check iterators
	for(itCount = myVectorCount.begin(); itCount != myVectorCount.end(); itCount++)
		(*itCount).value()++;

	itCount = myVectorCount.begin();
	for(int i = 0; itCount != myVectorCount.end(); itCount++, i++) {
		if (*itCount != sampleClass(1 + i)) {
			std::cout << "\033[1;31m1.29 iterators - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.29 iterators - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.11 let's check reverse iterators
	used_vector_sampleClass::reverse_iterator ritCount;
	for(ritCount = myVectorCount.rbegin(); ritCount != myVectorCount.rend(); ritCount++)
		((*ritCount).value())--;

	ritCount = myVectorCount.rbegin();
	for(int i = myVectorCount.size() - 1; ritCount != myVectorCount.rend(); ritCount++, i--) {
		if (*ritCount != sampleClass(i)) {
			std::cout << "\033[1;31m1.30 reverse iterators - when Count constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.30 reverse iterators - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.12 let's try at
	try {
		myVectorCount.at(myVectorCount.size());
		std::cout << "\033[1;31m1.31 at - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	} catch (std::exception ex) {
		std::cout << "\033[1;32m1.31 at - when Count constructor - functions as expected\033[0m" << std::endl;
	}

	// 1.13 let's check size

	myVectorCount.resize(5, sampleClass(5));
	if (myVectorCount.size() != 5) {
		std::cout << "\033[1;31m1.32 size - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.32 size - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.14 let's check reserve

	myVectorCount.reserve(100);
	if (myVectorCount.capacity() != 100) {
		std::cout << "\033[1;31m1.33 reserve and capacity - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.33 reserve and capacity - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.15 let's check empty

	if (myVectorCount.empty()) {
		std::cout << "\033[1;31m1.34 empty - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	myVectorCount.clear();
	if (!myVectorCount.empty()) {
		std::cout << "\033[1;31m1.34 empty - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.34 empty - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.16 let's check front

	for(int i = 0; i < 6; i++)
		myVectorCount.push_back(sampleClass(i));
	if(myVectorCount.front() != sampleClass(0)) {
		std::cout << "\033[1;31m1.35 front - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.35 front - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.17 let's check back

	if(myVectorCount.back() != sampleClass(5)) {
		std::cout << "\033[1;31m1.36 back - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.36 back - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.18 let's check operator==
	vectorToCopyFromCount.clear();
	for(int i = 0; i < 6; i++)
		vectorToCopyFromCount.push_back(sampleClass(i));
	if (myVectorCount != vectorToCopyFromCount) {
		std::cout << "\033[1;31m1.37 operator== - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.37 operator== - when Count constructor - functions as expected\033[0m" << std::endl;

	// 1.19 let's check operator<

	used_vector_int numericVectorOneCount;
	numericVectorOneCount.push_back(0);
	numericVectorOneCount.push_back(1);
	numericVectorOneCount.push_back(2);
	numericVectorOneCount.push_back(3);
	used_vector_int numericVectorTwoCount;
	numericVectorTwoCount.push_back(0);
	numericVectorTwoCount.push_back(1);
	numericVectorTwoCount.push_back(2);
	numericVectorTwoCount.push_back(2);

	if (numericVectorOneCount < numericVectorTwoCount) {
		std::cout << "\033[1;31m1.38 operator< - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	numericVectorOneCount.pop_back();
	if (numericVectorTwoCount < numericVectorOneCount) {
		std::cout << "\033[1;31m1.38 operator< - when Count constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.38 operator< - when Count constructor - functions as expected\033[0m" << std::endl;

	///

	// 1.1 push_back
	myVectorCount.clear();
	used_vector_sampleClass myVectorCopy(myVectorCount);

	for(int i = 0; i < 100; i++) {
		myVectorCopy.push_back(sampleClass(i));
	}

	for(int i = 0; i < 100; i++) {
		if (myVectorCopy[i] != sampleClass(i)) {
			std::cout << "\033[1;31m1.39 push back - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
		if (myVectorCopy[100 - 1 - i] == sampleClass(i)) {
			std::cout << "\033[1;31m1.39 push back - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.39 push back - when allocator Copy - functions as expected\033[0m" << std::endl;

	// 1.2 pop_back

	if (myVectorCopy.size() != 100) {
		std::cout << "\033[1;31m1.40 pop back - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for (int i = 0; i < 50; i++)
		myVectorCopy.pop_back();
	if (myVectorCopy.size() != 50) {
		std::cout << "\033[1;31m1.40 pop back - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	if (myVectorCopy.back() != sampleClass(49)) {
		std::cout << "\033[1;31m1.40 pop back - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.40 pop back - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.3 insert

	// 1.3.1 insert one element

	// normal condition

	// one element insert
	used_vector_sampleClass::iterator itCopy = myVectorCopy.begin();
	itCopy += 5;
	myVectorCopy.insert(itCopy, sampleClass(100));
	if (myVectorCopy[5] != sampleClass(100) || myVectorCopy.size() != 51) {
		std::cout << "\033[1;31m1.41 insert - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// multiple elements insert
	itCopy++;
	myVectorCopy.insert(itCopy, 6, sampleClass(21));
	for (int i = 6; i < 12; i++) {
		if (myVectorCopy[i] != sampleClass(21)) {
			std::cout << "\033[1;31m1.41 insert - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (myVectorCopy.size() != 57) {
		std::cout << "\033[1;31m1.41 insert - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// iterators insert
	used_vector_sampleClass vectorToCopyFromCopy(5, sampleClass(5));
	itCopy += 6;
	myVectorCopy.insert(itCopy, vectorToCopyFromCopy.begin(), vectorToCopyFromCopy.end());
	for (int i = 12; i < 17; i++) {
		if (myVectorCopy[i] != sampleClass(5)) {
			std::cout << "\033[1;31m1.41 insert - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}

	// overflows capacity
	int freeSpaceCopy = myVectorCopy.capacity() - myVectorCopy.size();
	try {
		myVectorCopy.insert(itCopy, freeSpaceCopy + 10, sampleClass(42));
	} catch (std::exception ex) {
		std::cout << "\033[1;31m1.41 insert - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// insert to the end element
	myVectorCopy.insert(myVectorCopy.end(), sampleClass(234));

	std::cout << "\033[1;32m1.41 insert - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.4 let's check clear

	myVectorCopy.clear();
	if (myVectorCopy.size() != 0) {
		std::cout << "\033[1;31m1.42 clear - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.42 clear - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.5 let's check erase

	// 1.5.1 simple erase

	for(int i = 0 ; i < 7; i++)
		myVectorCopy.push_back(sampleClass(i));
	itCopy = myVectorCopy.begin();
	itCopy += 3;
	myVectorCopy.erase(itCopy);

	if (myVectorCopy[3] == sampleClass(3)) {
		std::cout << "\033[1;31m1.43 erase - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	// 1.5.1 erase array
	myVectorCopy.erase(itCopy, myVectorCopy.end());

	if (myVectorCopy.size() != 3) {
		std::cout << "\033[1;31m1.43 erase - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.43 erase - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.6 let's try resize

	// resize more than size
	myVectorCopy.clear();
	myVectorCopy.resize(5, sampleClass(42));
	if (myVectorCopy.size() != 5 || myVectorCopy[4] != sampleClass(42)) {
		std::cout << "\033[1;31m1.44 resize - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// resize less than size
	myVectorCopy.resize(4, sampleClass(21));
	if (myVectorCopy.size() != 4) {
		std::cout << "\033[1;31m1.44 resize - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	// resize more than capacity
	int capacityCopy = myVectorCopy.capacity();
	myVectorCopy.resize(capacityCopy + 10, sampleClass(42));
	if (myVectorCopy.capacity() == capacityCopy || myVectorCopy[capacityCopy] != sampleClass(42)) {
		std::cout << "\033[1;31m1.44 resize - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.44 resize - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.7 let's try swap
	vectorToCopyFromCopy = used_vector_sampleClass(5, sampleClass(5));
	capacityCopy = myVectorCopy.size();
	myVectorCopy.swap(vectorToCopyFromCopy);
	for(int i = 0; i < vectorToCopyFromCopy.size(); i++) {
		if (vectorToCopyFromCopy[i] != sampleClass(42)) {
			std::cout << "\033[1;31m1.45 swap - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	for(int i = 0; i < myVectorCopy.size(); i++) {
		if (myVectorCopy[i] != sampleClass(5)) {
			std::cout << "\033[1;31m1.45 swap - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (myVectorCopy.size() != 5 || vectorToCopyFromCopy.size() != capacityCopy) {
		std::cout << "\033[1;31m1.45 swap - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.45 swap - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.8 let's try assign

	// 1.8.1 simple assign
	myVectorCopy.assign(8, sampleClass(-42));
	if (myVectorCopy.size() != 8) {
		std::cout << "\033[1;31m1.46 assign - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != myVectorCopy.size(); i++) {
		if (myVectorCopy[i] != sampleClass(-42)) {
			std::cout << "\033[1;31m1.46 assign - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	vectorToCopyFromCopy.clear();
	for(int i = 0; i != -6; i--)
		vectorToCopyFromCopy.push_back(sampleClass(i));

	// 1.8.2 iterators assign
	myVectorCopy.assign(vectorToCopyFromCopy.begin(), vectorToCopyFromCopy.end());
	if (myVectorCopy.size() != 6 ) {
		std::cout << "\033[1;31m1.46 assign - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != myVectorCopy.size(); i++) {
		if (myVectorCopy[i] != sampleClass((-1) * i)) {
			std::cout << "\033[1;31m1.46 assign - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.46 assign - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.9 let's try operator=
	vectorToCopyFromCopy.clear();
	for(int i = 0; i != 42; i++)
		vectorToCopyFromCopy.push_back(sampleClass(i));

	myVectorCopy = vectorToCopyFromCopy;
	for(int i = 0; i < myVectorCopy.size(); i++) {
		if (myVectorCopy[i] != sampleClass(i)) {
			std::cout << "\033[1;31m1.47 operator= - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.47 operator= - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.10 let's check iterators
	for(itCopy = myVectorCopy.begin(); itCopy != myVectorCopy.end(); itCopy++)
		(*itCopy).value()++;

	itCopy = myVectorCopy.begin();
	for(int i = 0; itCopy != myVectorCopy.end(); itCopy++, i++) {
		if (*itCopy != sampleClass(1 + i)) {
			std::cout << "\033[1;31m1.48 iterators - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.48 iterators - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.11 let's check reverse iterators
	used_vector_sampleClass::reverse_iterator ritCopy;
	for(ritCopy = myVectorCopy.rbegin(); ritCopy != myVectorCopy.rend(); ritCopy++)
		((*ritCopy).value())--;

	ritCopy = myVectorCopy.rbegin();
	for(int i = myVectorCopy.size() - 1; ritCopy != myVectorCopy.rend(); ritCopy++, i--) {
		if (*ritCopy != sampleClass(i)) {
			std::cout << "\033[1;31m1.49 reverse iterators - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m1.49 reverse iterators - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.12 let's try at
	try {
		myVectorCopy.at(myVectorCopy.size());
		std::cout << "\033[1;31m1.50 at - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	} catch (std::exception ex) {
		std::cout << "\033[1;32m1.50 at - when Copy constructor - functions as expected\033[0m" << std::endl;
	}

	// 1.13 let's check size

	myVectorCopy.resize(5, sampleClass(5));
	if (myVectorCopy.size() != 5) {
		std::cout << "\033[1;31m1.51 size - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.51 size - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.14 let's check reserve

	myVectorCopy.reserve(100);
	if (myVectorCopy.capacity() != 100) {
		std::cout << "\033[1;31m1.52 reserve and capacity - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.52 reserve and capacity - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.15 let's check empty

	if (myVectorCopy.empty()) {
		std::cout << "\033[1;31m1.53 empty - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	myVectorCopy.clear();
	if (!myVectorCopy.empty()) {
		std::cout << "\033[1;31m1.53 empty - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.53 empty - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.16 let's check front

	for(int i = 0; i < 6; i++)
		myVectorCopy.push_back(sampleClass(i));
	if(myVectorCopy.front() != sampleClass(0)) {
		std::cout << "\033[1;31m1.54 front - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.54 front - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.17 let's check back

	if(myVectorCopy.back() != sampleClass(5)) {
		std::cout << "\033[1;31m1.55 back - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.55 back - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.18 let's check operator==
	vectorToCopyFromCopy.clear();
	for(int i = 0; i < 6; i++)
		vectorToCopyFromCopy.push_back(sampleClass(i));
	if (myVectorCopy != vectorToCopyFromCopy) {
		std::cout << "\033[1;31m1.56 operator== - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.56 operator== - when Copy constructor - functions as expected\033[0m" << std::endl;

	// 1.19 let's check operator<

	used_vector_int numericVectorOneCopy;
	numericVectorOneCopy.push_back(0);
	numericVectorOneCopy.push_back(1);
	numericVectorOneCopy.push_back(2);
	numericVectorOneCopy.push_back(3);
	used_vector_int numericVectorTwoCopy;
	numericVectorTwoCopy.push_back(0);
	numericVectorTwoCopy.push_back(1);
	numericVectorTwoCopy.push_back(2);
	numericVectorTwoCopy.push_back(2);

	if (numericVectorOneCopy < numericVectorTwoCopy) {
		std::cout << "\033[1;31m1.57 operator< - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	numericVectorOneCopy.pop_back();
	if (numericVectorTwoCopy < numericVectorOneCopy) {
		std::cout << "\033[1;31m1.57 operator< - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m1.57 operator< - when Copy constructor - functions as expected\033[0m" << std::endl;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000000 + tp.tv_usec - ms;

	std::cout << std::endl << ms << " - vector execution time" << std::endl;

	/// stack

	std::cout << std::endl << "\033[1;33m STACK \033[0m" << std::endl << std::endl;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000000 + tp.tv_usec;

	used_stack_sampleClass myStack;

	if (myStack.size() != 0) {
		std::cout << "\033[1;31m2.1 size - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	for(int i = 0; i != 10; i++) {
		myStack.push(sampleClass(i));
		if (myStack.top() != sampleClass(i)) {
			std::cout << "\033[1;31m2.2 push - when default constructor - doesn't function as expected\033[0m" << std::endl;
			std::cout << "\033[1;31m2.3 top - when default constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (myStack.size() != 10) {
		std::cout << "\033[1;31m2.1 size - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m2.1 size - when default constructor - functions as expected\033[0m" << std::endl;
	std::cout << "\033[1;32m2.2 push - when default constructor - functions as expected\033[0m" << std::endl;
	std::cout << "\033[1;32m2.3 top - when default constructor - functions as expected\033[0m" << std::endl;

	for(int i = 0; i != 5; i++) {
		myStack.pop();
		if (myStack.size() != 9 - i || myStack.top() != sampleClass(8 - i)) {
			std::cout << "\033[1;31m2.4 pop - when default constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m2.4 pop - when default constructor - functions as expected\033[0m" << std::endl;

	used_stack_sampleClass mySecondStack;
	for(int i = 0; i != 10; i++) { mySecondStack.push(sampleClass(i)); }

	myStack = mySecondStack;
	if (myStack.size() != 10) {
		std::cout << "\033[1;31m2.5 operator= - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != 10; i++) {
		if (myStack.top() != sampleClass(9 - i)) {
			std::cout << "\033[1;31m2.5 operator= - when default constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
		myStack.pop();
	}
	std::cout << "\033[1;32m2.5 operator= - when default constructor - functions as expected\033[0m" << std::endl;

	if (!myStack.empty()) {
		std::cout << "\033[1;31m2.6 empty - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	myStack.push(sampleClass(0));
	if (myStack.empty()) {
		std::cout << "\033[1;31m2.6 empty - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m2.6 empty - when default constructor - functions as expected\033[0m" << std::endl;

	if (myStack == mySecondStack) {
		std::cout << "\033[1;31m2.7 operator== - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != 9; i++) { mySecondStack.pop(); }
	if (myStack != mySecondStack) {
		std::cout << "\033[1;31m2.7 operator== - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m2.7 operator== - when default constructor - functions as expected\033[0m" << std::endl;

	myStack.push(sampleClass(9));
	if (mySecondStack > myStack) {
		std::cout << "\033[1;31m2.8 operator< - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m2.8 operator< - when default constructor - functions as expected\033[0m" << std::endl;

	///

	while(!myStack.empty()) { myStack.pop(); }
	used_stack_sampleClass myStackCopy(myStack);

	if (myStackCopy.size() != 0) {
		std::cout << "\033[1;31m2.9 size - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	for(int i = 0; i != 10; i++) {
		myStackCopy.push(sampleClass(i));
		if (myStackCopy.top() != sampleClass(i)) {
			std::cout << "\033[1;31m2.10 push - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			std::cout << "\033[1;31m2.11 top - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (myStackCopy.size() != 10) {
		std::cout << "\033[1;31m2.9 size - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m2.9 size - when Copy constructor - functions as expected\033[0m" << std::endl;
	std::cout << "\033[1;32m2.10 push - when Copy constructor - functions as expected\033[0m" << std::endl;
	std::cout << "\033[1;32m2.11 top - when Copy constructor - functions as expected\033[0m" << std::endl;

	for(int i = 0; i != 5; i++) {
		myStackCopy.pop();
		if (myStackCopy.size() != 9 - i || myStackCopy.top() != sampleClass(8 - i)) {
			std::cout << "\033[1;31m2.12 pop - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m2.12 pop - when Copy constructor - functions as expected\033[0m" << std::endl;

	used_stack_sampleClass mySecondStackCopy;
	for(int i = 0; i != 10; i++) { mySecondStackCopy.push(sampleClass(i)); }

	myStackCopy = mySecondStackCopy;
	if (myStackCopy.size() != 10) {
		std::cout << "\033[1;31m2.13 operator= - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != 10; i++) {
		if (myStackCopy.top() != sampleClass(9 - i)) {
			std::cout << "\033[1;31m2.13 operator= - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
		myStackCopy.pop();
	}
	std::cout << "\033[1;32m2.13 operator= - when Copy constructor - functions as expected\033[0m" << std::endl;

	if (!myStackCopy.empty()) {
		std::cout << "\033[1;31m2.14 empty - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	myStackCopy.push(sampleClass(0));
	if (myStackCopy.empty()) {
		std::cout << "\033[1;31m2.14 empty - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m2.14 empty - when Copy constructor - functions as expected\033[0m" << std::endl;

	if (myStackCopy == mySecondStackCopy) {
		std::cout << "\033[1;31m2.15 operator== - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != 9; i++) { mySecondStackCopy.pop(); }
	if (myStackCopy != mySecondStackCopy) {
		std::cout << "\033[1;31m2.15 operator== - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m2.15 operator== - when Copy constructor - functions as expected\033[0m" << std::endl;

	myStackCopy.push(sampleClass(9));
	if (mySecondStackCopy > myStackCopy) {
		std::cout << "\033[1;31m2.16 operator< - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m2.16 operator< - when Copy constructor - functions as expected\033[0m" << std::endl;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000000 + tp.tv_usec - ms;

	std::cout << std::endl << ms << " - stack execution time" << std::endl;

	/// map

	std::cout << std::endl << "\033[1;33m MAP \033[0m" << std::endl << std::endl;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000000 + tp.tv_usec;

	used_map_sampleClass myMap;

	if (myMap.size() != 0) {
		std::cout << "\033[1;31m3.1 size - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	for(int i = 0; i != 100; i++) {
		myMap.insert(std::pair<const int, sampleClass>(i, sampleClass(i)));
	}
	for(int i = 0; i != 100; i++) {
		if (myMap[i].value() != i) {
			std::cout << "\033[1;31m3.2 insert - when default constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (myMap.size() != 100) {
		std::cout << "\033[1;31m3.1 size - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.1 size - when default constructor - functions as expected\033[0m" << std::endl;
	std::cout << "\033[1;32m3.2 insert - when default constructor - functions as expected\033[0m" << std::endl;

	if (myMap.at(50) != sampleClass(50)) {
		std::cout << "\033[1;31m3.3 at - when default constructor - doesn't function as expected (does not return an existing value)\033[0m" << std::endl;
		return (0);
	}

	myMap.at(50) = 51;
	if (myMap.at(50) != sampleClass(51)) {
		std::cout << "\033[1;31m3.3 at - when default constructor - doesn't function as expected (does not change an existing value)\033[0m" << std::endl;
		return (0);
	}

	try {
		myMap.at(100) = sampleClass(101);
		std::cout << "\033[1;31m3.3 at - when default constructor - doesn't function as expected (does not throw an exception when needed)\033[0m" << std::endl;
		return (0);
	} catch (std::out_of_range ex) {
		std::cout << "\033[1;32m3.3 at - when default constructor - functions as expected\033[0m" << std::endl;
	}

	if (myMap[50] != sampleClass(51)) {
		std::cout << "\033[1;31m3.4 operator[] - when default constructor - doesn't function as expected (does not return an existing value)\033[0m" << std::endl;
		return (0);
	}

	myMap[50] = sampleClass(50);
	if (myMap[50] != sampleClass(50)) {
		std::cout << "\033[1;31m3.4 operator[] - when default constructor - doesn't function as expected (does not change an existing value)\033[0m" << std::endl;
		return (0);
	}

	used_map_int myIntMap;
	myIntMap[100] = 100;
	if (myIntMap[100] != 100) {
		std::cout << "\033[1;31m3.4 operator[] - when default constructor - doesn't function as expected (does not insert yet non-existing value)\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.4 operator[] - when default constructor - functions as expected\033[0m" << std::endl;

	if (myMap.empty()) {
		std::cout << "\033[1;31m3.5 empty - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	myMap.clear();
	if (myMap.size() != 0) {
		std::cout << "\033[1;31m3.6 clear - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.5 empty - when default constructor - functions as expected\033[0m" << std::endl;
	std::cout << "\033[1;32m3.6 clear - when default constructor - functions as expected\033[0m" << std::endl;

	for(int i = 0; i < 100; i++) {
		myMap.insert(std::make_pair(100 - i, sampleClass(i)));
	}
	used_map_sampleClass::iterator map_it = myMap.begin();
	if (map_it->first != 1 || map_it->second != sampleClass(99)) {
		std::cout << "\033[1;31m3.7 begin - when default constructor - doesn't function as expected (doesn't return right key or value)\033[0m" << std::endl;
		return (0);
	}
	for(int i = 1; i < 101; i++) {
		if (map_it->first != i || map_it->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.7 begin - when default constructor - doesn't function as expected (operator++ doesn't function)\033[0m" << std::endl;
			return (0);
		}
		map_it++;
	}
	for(int i = 100; i > 0; i--) {
		map_it--;
		if (map_it->first != i || map_it->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.7 begin - when default constructor - doesn't function as expected (operator-- doesn't function)\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.7 begin - when default constructor - functions as expected\033[0m" << std::endl;

	used_map_sampleClass::reverse_iterator map_reverse_it = myMap.rbegin();
	if (map_reverse_it->first != 100 || map_reverse_it->second != sampleClass(0)) {
		std::cout << "\033[1;31m3.8 rbegin - when default constructor - doesn't function as expected (doesn't return right key or value)\033[0m" << std::endl;
		return (0);
	}
	for(int i = 100; i > 0; i--) {
		if (map_reverse_it->first != i || map_reverse_it->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.8 rbegin - when default constructor - doesn't function as expected (operator++ doesn't function)\033[0m" << std::endl;
			return (0);
		}
		map_reverse_it++;
	}
	for(int i = 1; i < 101; i++) {
		map_reverse_it--;
		if (map_reverse_it->first != i || map_reverse_it->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.8 rbegin - when default constructor - doesn't function as expected (operator-- doesn't function)\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.8 rbegin - when default constructor - functions as expected\033[0m" << std::endl;

	used_map_sampleClass::iterator map_it_end = myMap.end();
	for(int i = 0; i < 100; i++) { map_it++; }
	if (map_it != map_it_end) {
		std::cout << "\033[1;31m3.9 end - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i < 100; i++) { map_it--; }
	map_it_end--;
	for(int i = 0; map_it != map_it_end; map_it_end--, i++) {
		if (map_it_end->first != 100 - i || map_it_end->second != sampleClass(i)) {
			std::cout << "\033[1;31m3.9 end - when default constructor - doesn't function as expected (operator-- doesn't function)\033[0m" << std::endl;
			return (0);
		}
	}
	for(int i = 0; i < 100; i++) { map_it_end++; }
	for(int i = 1; map_it != map_it_end; map_it++, i++) {
		if (map_it->first != i || map_it->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.9 end - when default constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.9 end - when default constructor - functions as expected\033[0m" << std::endl;

	used_map_sampleClass::reverse_iterator map_reverse_it_end = myMap.rend();

	for(int i = 0; i < 100; i++) { map_reverse_it++; }
	if (map_reverse_it != map_reverse_it_end) {
		std::cout << "\033[1;31m3.10 rend - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i < 100; i++) { map_reverse_it--; }
	map_reverse_it_end--;
	for(int i = 1; map_reverse_it != map_reverse_it_end; map_reverse_it_end--, i++) {
		if (map_reverse_it_end->first != i || map_reverse_it_end->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.10 rend - when default constructor - doesn't function as expected (operator-- doesn't function)\033[0m" << std::endl;
			return (0);
		}
	}
	for(int i = 0; i < 100; i++) { map_reverse_it_end++; }
	for(int i = 0; map_reverse_it != map_reverse_it_end; map_reverse_it++, i++) {
		if (map_reverse_it->first != 100 - i || map_reverse_it->second != sampleClass(i)) {
			std::cout << "\033[1;31m3.10 rend - when default constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.10 rend - when default constructor - functions as expected\033[0m" << std::endl;

	myMap.insert(std::make_pair(666, sampleClass(666)));
	if (myMap.find(666)->second != sampleClass(666)) {
		std::cout << "\033[1;31m3.11 find - when default constructor - doesn't function as expected (doesn't find an existing element)\033[0m" << std::endl;
		return (0);
	}
	if (myMap.find(667) != myMap.end()) {
		std::cout << "\033[1;31m3.11 find - when default constructor - doesn't function as expected (non-existing element)\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.11 find - when default constructor - functions as expected\033[0m" << std::endl;

	myMap.clear();
	for(int i = 0; i != 13; i++) { myMap.insert(std::make_pair(i, sampleClass(i))); }
	myMap.erase(6);
	if (myMap.find(6) != myMap.end()) {
		std::cout << "\033[1;31m3.12 erase - when default constructor - doesn't function as expected (key)\033[0m" << std::endl;
		return (0);
	}
	map_it = myMap.find(3);
	myMap.erase(map_it);
	if (myMap.find(3) != myMap.end()) {
		std::cout << "\033[1;31m3.12 erase - when default constructor - doesn't function as expected (single iterator)\033[0m" << std::endl;
		return (0);
	}
	map_it = myMap.find(8);
	myMap.erase(map_it, myMap.end());
	if (myMap.find(8) != myMap.end() || myMap.find(9) != myMap.end()
	|| myMap.find(10) != myMap.end() || myMap.find(11) != myMap.end() || myMap.find(12) != myMap.end()) {
		std::cout << "\033[1;31m3.12 erase - when default constructor - doesn't function as expected (multiple iterators)\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.12 erase - when default constructor - functions as expected\033[0m" << std::endl;
	myMap.clear();

	used_map_sampleClass my_map_to_be_swaped;
	for(int i = 0; i != 12; i++) {
		my_map_to_be_swaped.insert(std::make_pair(i, sampleClass(11 - i)));
		myMap.insert(std::make_pair(i, sampleClass(i)));
	}
	swap(myMap, my_map_to_be_swaped);
	for(int i = 0; i != 12; i++) {
		if (myMap.find(i)->second != sampleClass(11 - i) || my_map_to_be_swaped.find(i)->second != sampleClass(i)) {
			std::cout << "\033[1;31m3.13 swap - when default constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.13 swap - when default constructor - functions as expected\033[0m" << std::endl;

	myMap.clear();
	myMap.insert(std::make_pair(1, sampleClass(1)));
	if (myMap.count(1) != 1) {
		std::cout << "\033[1;31m3.14 insert - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	myMap.clear();
	if (myMap.count(1) != 0) {
		std::cout << "\033[1;31m3.14 insert - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.14 insert - when default constructor - functions as expected\033[0m" << std::endl;

	for(int i = 10; i <= 20; i++) { myMap.insert(std::make_pair(i, sampleClass(i))); }
	if (myMap.lower_bound(15)->second != sampleClass(15) || myMap.lower_bound(15)->first != 15) {
		std::cout << "\033[1;31m3.15 lower_bound - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	if (myMap.lower_bound(25) != myMap.end()) {
		std::cout << "\033[1;31m3.15 lower_bound - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.15 lower_bound - when default constructor - functions as expected\033[0m" << std::endl;

	if (myMap.upper_bound(15)->second != sampleClass(16) || myMap.upper_bound(15)->first != 16) {
		std::cout << "\033[1;31m3.16 upper_bound - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	if (myMap.upper_bound(25) != myMap.end()) {
		std::cout << "\033[1;31m3.16 upper_bound - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.16 upper_bound - when default constructor - functions as expected\033[0m" << std::endl;

	myMap.clear();
	for(int i = 0; i != 7; i++) { myMap.insert(std::make_pair(i * 3, sampleClass(i * 3))); }
	std::pair<used_map_sampleClass::iterator, used_map_sampleClass::iterator> result;
	result = myMap.equal_range(0);
	if (result.first->second != sampleClass(0) || result.second->second != sampleClass(3)) {
		std::cout << "\033[1;31m3.17 equal_range - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	result = myMap.equal_range(3);
	if (result.first->second != sampleClass(3) || result.second->second != sampleClass(6)) {
		std::cout << "\033[1;31m3.17 equal_range - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.17 equal_range - when default constructor - functions as expected\033[0m" << std::endl;

	used_map_sampleClass mySecondMap;
	for(int i = 0; i != 7; i++) { mySecondMap.insert(std::make_pair(i * 3, sampleClass(i * 3))); }
	if (mySecondMap != myMap) {
		std::cout << "\033[1;31m3.18 operator= - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.18 operator= - when default constructor - functions as expected\033[0m" << std::endl;

	mySecondMap.insert(std::make_pair(21, sampleClass(21)));
	if (mySecondMap < myMap) {
		std::cout << "\033[1;31m3.19 operator< - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.19 operator< - when default constructor - functions as expected\033[0m" << std::endl;

	swap(myMap, mySecondMap);
	if (myMap.size() != 8) {
		std::cout << "\033[1;31m3.20 swap - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != 8; i++) {
		if (myMap[i * 3] != sampleClass(i * 3)) {
			std::cout << "\033[1;31m3.20 swap - when default constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (mySecondMap.size() != 7) {
		std::cout << "\033[1;31m3.20 swap - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != 7; i++) {
		if (mySecondMap[i * 3] != sampleClass(i * 3)) {
			std::cout << "\033[1;31m3.20 swap - when default constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.20 swap - when default constructor - functions as expected\033[0m" << std::endl;

	///

	myMap.clear();
	used_map_sampleClass myMapCopy(myMap);

	if (myMapCopy.size() != 0) {
		std::cout << "\033[1;31m3.21 size - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	for(int i = 0; i != 100; i++) {
		myMapCopy.insert(std::pair<const int, sampleClass>(i, sampleClass(i)));
	}
	for(int i = 0; i != 100; i++) {
		if (myMapCopy[i].value() != i) {
			std::cout << "\033[1;31m3.22 insert - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (myMapCopy.size() != 100) {
		std::cout << "\033[1;31m3.21 size - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.21 size - when Copy constructor - functions as expected\033[0m" << std::endl;
	std::cout << "\033[1;32m3.22 insert - when Copy constructor - functions as expected\033[0m" << std::endl;

	if (myMapCopy.at(50) != sampleClass(50)) {
		std::cout << "\033[1;31m3.23 at - when Copy constructor - doesn't function as expected (does not return an existing value)\033[0m" << std::endl;
		return (0);
	}

	myMapCopy.at(50) = 51;
	if (myMapCopy.at(50) != sampleClass(51)) {
		std::cout << "\033[1;31m3.23 at - when Copy constructor - doesn't function as expected (does not change an existing value)\033[0m" << std::endl;
		return (0);
	}

	try {
		myMapCopy.at(100) = sampleClass(101);
		std::cout << "\033[1;31m3.23 at - when Copy constructor - doesn't function as expected (does not throw an exception when needed)\033[0m" << std::endl;
		return (0);
	} catch (std::out_of_range ex) {
		std::cout << "\033[1;32m3.23 at - when Copy constructor - functions as expected\033[0m" << std::endl;
	}

	if (myMapCopy[50] != sampleClass(51)) {
		std::cout << "\033[1;31m3.24 operator[] - when Copy constructor - doesn't function as expected (does not return an existing value)\033[0m" << std::endl;
		return (0);
	}

	myMapCopy[50] = sampleClass(50);
	if (myMapCopy[50] != sampleClass(50)) {
		std::cout << "\033[1;31m3.24 operator[] - when Copy constructor - doesn't function as expected (does not change an existing value)\033[0m" << std::endl;
		return (0);
	}

	myIntMap.clear();
	used_map_int myIntMapCopy(myIntMap);
	myIntMapCopy[100] = 100;
	if (myIntMapCopy[100] != 100) {
		std::cout << "\033[1;31m3.24 operator[] - when Copy constructor - doesn't function as expected (does not insert yet non-existing value)\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.24 operator[] - when Copy constructor - functions as expected\033[0m" << std::endl;

	if (myMapCopy.empty()) {
		std::cout << "\033[1;31m3.25 empty - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	myMapCopy.clear();
	if (myMapCopy.size() != 0) {
		std::cout << "\033[1;31m3.26 clear - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.25 empty - when Copy constructor - functions as expected\033[0m" << std::endl;
	std::cout << "\033[1;32m3.26 clear - when Copy constructor - functions as expected\033[0m" << std::endl;

	for(int i = 0; i < 100; i++) {
		myMapCopy.insert(std::make_pair(100 - i, sampleClass(i)));
	}
	used_map_sampleClass::iterator map_itCopy = myMapCopy.begin();
	if (map_itCopy->first != 1 || map_itCopy->second != sampleClass(99)) {
		std::cout << "\033[1;31m3.27 begin - when Copy constructor - doesn't function as expected (doesn't return right key or value)\033[0m" << std::endl;
		return (0);
	}
	for(int i = 1; i < 101; i++) {
		if (map_itCopy->first != i || map_itCopy->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.27 begin - when Copy constructor - doesn't function as expected (operator++ doesn't function)\033[0m" << std::endl;
			return (0);
		}
		map_itCopy++;
	}
	for(int i = 100; i > 0; i--) {
		map_itCopy--;
		if (map_itCopy->first != i || map_itCopy->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.27 begin - when Copy constructor - doesn't function as expected (operator-- doesn't function)\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.27 begin - when Copy constructor - functions as expected\033[0m" << std::endl;

	used_map_sampleClass::reverse_iterator map_reverse_itCopy = myMapCopy.rbegin();
	if (map_reverse_itCopy->first != 100 || map_reverse_itCopy->second != sampleClass(0)) {
		std::cout << "\033[1;31m3.28 rbegin - when Copy constructor - doesn't function as expected (doesn't return right key or value)\033[0m" << std::endl;
		return (0);
	}
	for(int i = 100; i > 0; i--) {
		if (map_reverse_itCopy->first != i || map_reverse_itCopy->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.28 rbegin - when Copy constructor - doesn't function as expected (operator++ doesn't function)\033[0m" << std::endl;
			return (0);
		}
		map_reverse_itCopy++;
	}
	for(int i = 1; i < 101; i++) {
		map_reverse_itCopy--;
		if (map_reverse_itCopy->first != i || map_reverse_itCopy->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.28 rbegin - when Copy constructor - doesn't function as expected (operator-- doesn't function)\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.28 rbegin - when Copy constructor - functions as expected\033[0m" << std::endl;

	used_map_sampleClass::iterator map_it_endCopy = myMapCopy.end();
	for(int i = 0; i < 100; i++) { map_itCopy++; }
	if (map_itCopy != map_it_endCopy) {
		std::cout << "\033[1;31m3.29 end - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i < 100; i++) { map_itCopy--; }
	map_it_endCopy--;
	for(int i = 0; map_itCopy != map_it_endCopy; map_it_endCopy--, i++) {
		if (map_it_endCopy->first != 100 - i || map_it_endCopy->second != sampleClass(i)) {
			std::cout << "\033[1;31m3.29 end - when Copy constructor - doesn't function as expected (operator-- doesn't function)\033[0m" << std::endl;
			return (0);
		}
	}
	for(int i = 0; i < 100; i++) { map_it_endCopy++; }
	for(int i = 1; map_itCopy != map_it_endCopy; map_itCopy++, i++) {
		if (map_itCopy->first != i || map_itCopy->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.29 end - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.29 end - when Copy constructor - functions as expected\033[0m" << std::endl;

	used_map_sampleClass::reverse_iterator map_reverse_it_endCopy = myMapCopy.rend();

	for(int i = 0; i < 100; i++) { map_reverse_itCopy++; }
	if (map_reverse_itCopy != map_reverse_it_endCopy) {
		std::cout << "\033[1;31m3.30 rend - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i < 100; i++) { map_reverse_itCopy--; }
	map_reverse_it_endCopy--;
	for(int i = 1; map_reverse_itCopy != map_reverse_it_endCopy; map_reverse_it_endCopy--, i++) {
		if (map_reverse_it_endCopy->first != i || map_reverse_it_endCopy->second != sampleClass(100 - i)) {
			std::cout << "\033[1;31m3.30 rend - when Copy constructor - doesn't function as expected (operator-- doesn't function)\033[0m" << std::endl;
			return (0);
		}
	}
	for(int i = 0; i < 100; i++) { map_reverse_it_endCopy++; }
	for(int i = 0; map_reverse_itCopy != map_reverse_it_endCopy; map_reverse_itCopy++, i++) {
		if (map_reverse_itCopy->first != 100 - i || map_reverse_itCopy->second != sampleClass(i)) {
			std::cout << "\033[1;31m3.30 rend - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.30 rend - when Copy constructor - functions as expected\033[0m" << std::endl;

	myMapCopy.insert(std::make_pair(666, sampleClass(666)));
	if (myMapCopy.find(666)->second != sampleClass(666)) {
		std::cout << "\033[1;31m3.31 find - when Copy constructor - doesn't function as expected (doesn't find an existing element)\033[0m" << std::endl;
		return (0);
	}
	if (myMapCopy.find(667) != myMapCopy.end()) {
		std::cout << "\033[1;31m3.31 find - when Copy constructor - doesn't function as expected (non-existing element)\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.31 find - when Copy constructor - functions as expected\033[0m" << std::endl;

	myMapCopy.clear();
	for(int i = 0; i != 13; i++) { myMapCopy.insert(std::make_pair(i, sampleClass(i))); }
	myMapCopy.erase(6);
	if (myMapCopy.find(6) != myMapCopy.end()) {
		std::cout << "\033[1;31m3.32 erase - when Copy constructor - doesn't function as expected (key)\033[0m" << std::endl;
		return (0);
	}
	map_itCopy = myMapCopy.find(3);
	myMapCopy.erase(map_itCopy);
	if (myMapCopy.find(3) != myMapCopy.end()) {
		std::cout << "\033[1;31m3.32 erase - when Copy constructor - doesn't function as expected (single iterator)\033[0m" << std::endl;
		return (0);
	}
	map_itCopy = myMapCopy.find(8);
	myMapCopy.erase(map_itCopy, myMapCopy.end());
	if (myMapCopy.find(8) != myMapCopy.end() || myMapCopy.find(9) != myMapCopy.end()
	|| myMapCopy.find(10) != myMapCopy.end() || myMapCopy.find(11) != myMapCopy.end() || myMapCopy.find(12) != myMapCopy.end()) {
		std::cout << "\033[1;31m3.32 erase - when Copy constructor - doesn't function as expected (multiple iterators)\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.32 erase - when Copy constructor - functions as expected\033[0m" << std::endl;
	myMapCopy.clear();

	used_map_sampleClass my_map_to_be_swapedCopy;
	for(int i = 0; i != 12; i++) {
		my_map_to_be_swapedCopy.insert(std::make_pair(i, sampleClass(11 - i)));
		myMapCopy.insert(std::make_pair(i, sampleClass(i)));
	}
	swap(myMapCopy, my_map_to_be_swapedCopy);
	for(int i = 0; i != 12; i++) {
		if (myMapCopy.find(i)->second != sampleClass(11 - i) || my_map_to_be_swapedCopy.find(i)->second != sampleClass(i)) {
			std::cout << "\033[1;31m3.33 swap - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.33 swap - when Copy constructor - functions as expected\033[0m" << std::endl;

	myMapCopy.clear();
	myMapCopy.insert(std::make_pair(1, sampleClass(1)));
	if (myMapCopy.count(1) != 1) {
		std::cout << "\033[1;31m3.34 insert - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	myMapCopy.clear();
	if (myMapCopy.count(1) != 0) {
		std::cout << "\033[1;31m3.34 insert - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.34 insert - when Copy constructor - functions as expected\033[0m" << std::endl;

	for(int i = 10; i <= 20; i++) { myMapCopy.insert(std::make_pair(i, sampleClass(i))); }
	if (myMapCopy.lower_bound(15)->second != sampleClass(15) || myMapCopy.lower_bound(15)->first != 15) {
		std::cout << "\033[1;31m3.35 lower_bound - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	if (myMapCopy.lower_bound(25) != myMapCopy.end()) {
		std::cout << "\033[1;31m3.35 lower_bound - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.35 lower_bound - when Copy constructor - functions as expected\033[0m" << std::endl;

	if (myMapCopy.upper_bound(15)->second != sampleClass(16) || myMapCopy.upper_bound(15)->first != 16) {
		std::cout << "\033[1;31m3.36 upper_bound - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	if (myMapCopy.upper_bound(25) != myMapCopy.end()) {
		std::cout << "\033[1;31m3.36 upper_bound - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.36 upper_bound - when Copy constructor - functions as expected\033[0m" << std::endl;

	myMapCopy.clear();
	for(int i = 0; i != 7; i++) { myMapCopy.insert(std::make_pair(i * 3, sampleClass(i * 3))); }
	std::pair<used_map_sampleClass::iterator, used_map_sampleClass::iterator> resultCopy;
	resultCopy = myMapCopy.equal_range(0);
	if (resultCopy.first->second != sampleClass(0) || resultCopy.second->second != sampleClass(3)) {
		std::cout << "\033[1;31m3.37 equal_range - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	resultCopy = myMapCopy.equal_range(3);
	if (resultCopy.first->second != sampleClass(3) || resultCopy.second->second != sampleClass(6)) {
		std::cout << "\033[1;31m3.37 equal_range - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.37 equal_range - when Copy constructor - functions as expected\033[0m" << std::endl;

	used_map_sampleClass mySecondMapCopy;
	for(int i = 0; i != 7; i++) { mySecondMapCopy.insert(std::make_pair(i * 3, sampleClass(i * 3))); }
	if (mySecondMapCopy != myMapCopy) {
		std::cout << "\033[1;31m3.38 operator= - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.38 operator= - when Copy constructor - functions as expected\033[0m" << std::endl;

	mySecondMapCopy.insert(std::make_pair(21, sampleClass(21)));
	if (mySecondMapCopy < myMapCopy) {
		std::cout << "\033[1;31m3.39 operator< - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	std::cout << "\033[1;32m3.39 operator< - when Copy constructor - functions as expected\033[0m" << std::endl;

	swap(myMapCopy, mySecondMapCopy);
	if (myMapCopy.size() != 8) {
		std::cout << "\033[1;31m3.40 swap - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != 8; i++) {
		if (myMapCopy[i * 3] != sampleClass(i * 3)) {
			std::cout << "\033[1;31m3.40 swap - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	if (mySecondMapCopy.size() != 7) {
		std::cout << "\033[1;31m3.40 swap - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}
	for(int i = 0; i != 7; i++) {
		if (mySecondMapCopy[i * 3] != sampleClass(i * 3)) {
			std::cout << "\033[1;31m3.40 swap - when Copy constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.40 swap - when Copy constructor - functions as expected\033[0m" << std::endl;

	gettimeofday(&tp, NULL);
	ms = tp.tv_sec * 1000000 + tp.tv_usec - ms;

	std::cout << std::endl << ms << " - map execution time" << std::endl;

	///
}
