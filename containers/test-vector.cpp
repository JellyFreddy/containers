#include "vector.hpp"
#include "map.hpp"
#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>

#include "sample_class.hpp"

int main() {
	// 1 allocator constructor //

	using namespace ft;
	typedef vector<sampleClass> used_vector_sampleClass;
	typedef vector<int> used_vector_int;
	typedef map<int, sampleClass> used_map_sampleClass;
	typedef map<int, int> used_map_int;

	used_vector_sampleClass myVector((std::allocator<sampleClass>()));

	/// Vector

	std::cout << std::endl << "\033[1;33m VECTOR \033[0m" << std::endl << std::endl;

	// 1.1 push_back

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
	if (myVector[3] == sampleClass(4)) {
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


	/// map

	std::cout << std::endl << "\033[1;33m MAP \033[0m" << std::endl << std::endl;

	used_map_sampleClass myMap;

	if (myMap.size() != 0) {
		std::cout << "\033[1;31m3.1 size - when default constructor - doesn't function as expected\033[0m" << std::endl;
		return (0);
	}

	for(int i = 0; i != 100; i++) {
		myMap.insert(pair<const int, sampleClass>(i, sampleClass(i)));
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
		myMap.insert(make_pair(100 - i, sampleClass(i)));
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

	myMap.insert(make_pair(666, sampleClass(666)));
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
	for(int i = 0; i != 13; i++) { myMap.insert(make_pair(i, sampleClass(i))); }
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
		my_map_to_be_swaped.insert(make_pair(i, sampleClass(11 - i)));
		myMap.insert(make_pair(i, sampleClass(i)));
	}
	swap(myMap, my_map_to_be_swaped);
	for(int i = 0; i != 12; i++) {
		if (myMap.find(i)->second != sampleClass(11 - i) || my_map_to_be_swaped.find(i)->second != sampleClass(i)) {
			std::cout << "\033[1;31m3.13 swap - when default constructor - doesn't function as expected\033[0m" << std::endl;
			return (0);
		}
	}
	std::cout << "\033[1;32m3.13 swap - when default constructor - functions as expected\033[0m" << std::endl;
}