#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include <memory>
# include "iterators_utils.hpp"
# include <iostream>

namespace ft {

	template <bool isConst, typename isFalse, typename isTrue>
	struct conditional {};

	template <typename isFalse, typename isTrue>
	struct conditional<false, isFalse, isTrue>
	{
		typedef isFalse type;
	};

	template <typename isFalse, typename isTrue>
	struct conditional<true, isFalse, isTrue>
	{
		typedef isTrue type;
	};

	template<
		class T,
		class Category,
		class Distance,
		class Pointer,
		class Reference,
		bool IsConstant
	> struct vector_iterator {
	protected:
		T * node;
	public:

		// member types
		typedef Category    														iterator_category;
		typedef T           														value_type;
		typedef Distance    														difference_type;
		typedef typename conditional<IsConstant, Pointer, const Pointer>::type    	pointer;
		typedef typename conditional<IsConstant, Reference, const Reference>::type  reference;

		T *getNode() const {  return (node); }

		// constructors
		vector_iterator() : node(nullptr) {};
		vector_iterator(T* ptr) : node(ptr) {};
		vector_iterator(const vector_iterator<T, Category, Distance, Pointer, Reference, false> & other) { node = other.getNode(); };
		~vector_iterator() {};

		// member functions
		vector_iterator & operator=(const vector_iterator & other) {
			if (this != &other)
				node = other.getNode();
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
			vector_iterator res(*this);
			node++;
			return (res);
		};
		vector_iterator operator--( int ) {
			vector_iterator res(*this);
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

		bool operator==(const vector_iterator<T, Category, Distance, Pointer, Reference, IsConstant>& rhs ) {
			return (this->node == rhs.node);
		};
		bool operator!=(const vector_iterator<T, Category, Distance, Pointer, Reference, IsConstant>& rhs ) {
			return (!(this->node == rhs.node));
		};
		bool operator>=(const vector_iterator<T, Category, Distance, Pointer, Reference, IsConstant>& rhs ) {
			return (this->node >= rhs.node);
		};
		bool operator<=(const vector_iterator<T, Category, Distance, Pointer, Reference, IsConstant>& rhs ) {
			return (this->node <= rhs.node);
		};
		bool operator>(const vector_iterator<T, Category, Distance, Pointer, Reference, IsConstant>& rhs ) {
			return (this->node > rhs.node);
		};
		bool operator<(const vector_iterator<T, Category, Distance, Pointer, Reference, IsConstant>& rhs ) {
			return (this->node < rhs.node);
		};
	};

}

#endif