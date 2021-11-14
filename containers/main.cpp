#include <iostream>
#include "trees.hpp"
#include <iomanip>
#include "map.hpp"
#include <functional>

int main() {

	// Allocate an array to keep track of the data we
	// add to the tree, initialize the random numbers,
	// allocate an empty tree.
	int data[10][2];
	srand(time(0));
	ft::AVLTree<int, int, std::less<int>, std::allocator<ft::pair<const int, int> > > *tree = new ft::AVLTree<int, int, std::less<int>, std::allocator<ft::pair<const int, int> > >();

	// Insert 10 unique random numbers into the tree.
	// For each number we are adding, attempt to insert
	// a random number, until it works because it is
	// unique. Afterwards, display the new number and
	// the current state of the tree.
	for (int i = 0; i < 10; i++) {
		while (!tree->insert(data[i][0] = rand()%100, data[i][1] = rand()%100));
		std::cout << "Adding " << data[i][0] << "(" << data[i][1] << ")" << std::endl;
		tree->print();
	} // for

	std::cout << std::endl;

	// Remove each of the numbers by displaying the
	// number being removed, performing the removal,
	// and displaying the current state of the tree.
	for (int i = 0; i < 10; i++) {
		std::cout << "Removing " << data[i][0] << "(" << data[i][1] << ")" << std::endl;
		tree->remove(data[i][0]);
		tree->print();
	} // for
	return 0;
}
