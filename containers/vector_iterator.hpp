#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include <memory>
# include "iterators_utils.hpp"

namespace ft {

	template<
		class T,
		class Category,
		class Distance,
		class Pointer,
		class Reference
	> struct vector_iterator {
	protected:
		Pointer node;
	public:

		// member types
		typedef Category    iterator_category;
		typedef T           value_type;
		typedef Distance    difference_type;
		typedef Pointer     pointer;
		typedef Reference   reference;

		// constructors
		vector_iterator() : node(nullptr) {};
		vector_iterator(const pointer ptr) : node(ptr) {};
		vector_iterator(const vector_iterator & other) { *this = other; };
		~vector_iterator() {};

		// member functions
		vector_iterator & operator=(const vector_iterator & other) {
			if (this != &other)
				node = other.node;
			return (*this);
		};
		reference       operator*() const { return *node; };
		pointer         operator->() const { return node; };
		reference       operator[](difference_type n) const { return (node + n); };

		vector_iterator & operator++() {
			node++;
			return (*this);
		};
		vector_iterator & operator--() {
			node--;
			return (*this);
		};
		vector_iterator operator++( int ) {
			vector_iterator<value_type, iterator_category, difference_type, pointer, reference> res(*this);
			node++;
			return (res);
		};
		vector_iterator operator--( int ) {
			vector_iterator<value_type, iterator_category, difference_type, pointer, reference> res(*this);
			node--;
			return (res);
		};
		vector_iterator operator+( difference_type n ) const { return vector_iterator(node + n); };
		vector_iterator operator-( difference_type n ) const { return vector_iterator(node - n); };
		difference_type operator-( vector_iterator n ) const { return difference_type (node - n.node); };
		vector_iterator & operator+=( difference_type n ) {
			node += n;
			return (*this);
		};
		vector_iterator & operator-=( difference_type n ) {
			node -= n;
			return (*this);
		};

		bool operator==(const vector_iterator<T, Category, Distance, Pointer, Reference>& rhs ) {
			return (this->node == rhs.node);
		};
		bool operator!=(const vector_iterator<T, Category, Distance, Pointer, Reference>& rhs ) {
			return (!(this->node == rhs.node));
		};
		bool operator>=(const vector_iterator<T, Category, Distance, Pointer, Reference>& rhs ) {
			return (this->node >= rhs.node);
		};
		bool operator<=(const vector_iterator<T, Category, Distance, Pointer, Reference>& rhs ) {
			return (this->node <= rhs.node);
		};
		bool operator>(const vector_iterator<T, Category, Distance, Pointer, Reference>& rhs ) {
			return (this->node > rhs.node);
		};
		bool operator<(const vector_iterator<T, Category, Distance, Pointer, Reference>& rhs ) {
			return (this->node < rhs.node);
		};
	};

}

#endif