#ifndef VECTOR_CPP
# define VECTOR_CPP

# include "vector_iterator.hpp"
# include <stdexcept>

namespace ft {
	template<
	class T,
	class Allocator = std::allocator<T>
	> class vector {
	public:
		// member types
		typedef T                                        value_type;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;

		typedef vector_iterator<T, std::random_access_iterator_tag, std::ptrdiff_t, pointer, reference>                     iterator;
		typedef vector_iterator<T, std::random_access_iterator_tag, std::ptrdiff_t, const_pointer , const_reference>        const_iterator;
		typedef ft::reverse_iterator<iterator>                                                                              reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>                                                                        const_reverse_iterator;

		typedef typename ft::iterators_traits<iterator>::difference_type                                                    difference_type;
		typedef std::size_t                                                                                                 size_type;
	protected:
		size_type       _capacity;
		size_type       _size;
		allocator_type  _allocator;

	public:
		pointer         _vector;
		explicit vector(const allocator_type & alloc = allocator_type()) : _allocator(alloc), _size(0), _capacity(0) {
			_vector = _allocator.allocate(_capacity);
		};
		vector(size_type count, const T & value = T(), const allocator_type & alloc = allocator_type())
		: _allocator(alloc), _size(count), _capacity(count) {
			_vector = _allocator.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_allocator.construct(&(_vector[i]), value);
		};
		template<class InputIt>
		vector(InputIt first, InputIt last, const allocator_type & alloc = allocator_type())
		: _allocator(alloc), _size(0){
			InputIt tmp(first);
			while(tmp++ != last)
				_size++;

			_capacity = _size;
			_vector = _allocator.allocate(_capacity);
			for(size_type i = 0;first != last; first++, i++)
				_allocator.construct(&(_vector[i]), *first);
		}
		vector(const vector & other) : _allocator(other._allocator), _capacity(other._capacity),
		_size(other._size) {
			_vector = _allocator.allocate(_capacity);

			for(ft::pair<int, const_iterator> pair(0, other.begin()); pair.second != other.end(); pair.first++, pair.second++)
				_allocator.construct(&(_vector[pair.first]), *(pair.second));
		}
		~vector() {
			for(iterator it = begin(); it != end(); it++)
				_allocator.destroy(&(*it));
			_allocator.deallocate(_vector, _capacity);
		}
		vector & operator=(const vector & other) {
			vector tmp(other);
			swap(tmp);
			return *this;
		}

		iterator        begin() { return (_vector); };
		const_iterator  begin() const { return (_vector); };
		iterator        end() { return (_vector + _size); };
		const_iterator  end() const { return (_vector + _size); };

		reverse_iterator        rbegin() { return (_vector + _size); };
		const_reverse_iterator  rbegin() const { return (_vector + _size); };
		reverse_iterator        rend() { return (_vector); };
		const_reverse_iterator  rend() const { return (_vector); };

		size_type size() const { return (_size); };
		size_type max_size() const { return _allocator.max_size(); };
		void resize(size_type n, value_type val = value_type()) {
			if (n > _capacity)
				reallocateVec(n);
			while(n > _size)
				push_back(val);
			while(n < _size)
				pop_back();
		}
		size_type capacity() const { return _capacity; };
		bool empty() const { return (_size == 0); };
		void reserve(size_type n) {
			if (n > max_size())
				throw std::length_error("vector");
			if (n < _capacity)
				reallocateVec(n);
		}

		reference operator[] ( size_type pos ) { return _vector[pos]; }
		const_reference operator[] ( size_type pos ) const { return _vector[pos]; }
		reference at ( size_type pos ) {
			if (pos >= size())
				throw std::out_of_range("vector");
			return (_vector[pos]);
		}
		const_reference at ( size_type pos ) const {
			if (pos >= size())
				throw std::out_of_range("vector");
			return (_vector[pos]);
		}
		reference front() { return _vector[0]; }
		const_reference front() const { return _vector[0]; }
		reference back() { return _vector[_size - 1]; }
		const_reference back() const { return _vector[_size - 1]; }
		T *data() { return _vector; }
		const T *data() const { return _vector; }

		void pop_back()
		{
			if (_size > 0) {
				_allocator.destroy(&_vector[_size - 1]);
				_size--;
			}
		}

		void push_back (const value_type& val)
		{
			if (_size + 1 > _capacity)
				reallocateVec(_capacity == 0 ? 1 : _capacity * 2);
			_allocator.construct(&_vector[_size++], val);
		}

		void clear() {
			while(_size > 0)
				pop_back();
		}
		void insert( iterator pos, size_type count, const T& value ) {
			if (pos == end())
				return ;

			if (size() + count > capacity())
				reallocateVec(size() + count);

			difference_type index = pos - begin();
			moveElementsToTheRight(index, count);

			for(int i = 0; i < count; i++)
				_allocator.construct(&(_vector[index + i]), value);
			_size += count;
		}
		iterator insert( iterator pos, const T& value ) {
			difference_type index = pos - begin();
			insert(pos, 1, value);
			return (iterator(&(_vector[index])));
		}
		template< class InputIt >
		void insert( iterator pos, InputIt first, InputIt last ) {
			if (pos == end())
				return ;
			difference_type index = pos - begin();
			difference_type count = last - first;

			if (_size + count > _capacity)
				reallocateVec(_capacity + count);

			if (count > 0)
				moveElementsToTheRight(index, count);

			for( ; first != last; first++, index++)
				_allocator.construct(&(_vector[index]), *first);
			_size += count;
		}
		iterator erase (iterator first, iterator last)
		{
			if (first == end() || first == last)
				return first;

			difference_type index = first - begin();

			if (last < end())
			{
				moveElementsToTheLeft(first, last);
				_size -= (last - first);
			}
			else
			{
				while(back() != *(first - 1)) {
					pop_back();
				}
			}

			return iterator(&_vector[index]);
		}
		iterator erase( iterator pos ) { return erase(pos, pos + 1); }
		void swap( vector& other ) {
			swap(_allocator, other._allocator);
			swap(_vector, other._vector);
			swap(_size, other._size);
			swap(_capacity, other._capacity);
		}
		void assign( size_type count, const T& value ) {
			clear();

			if (count > _capacity) {
				_allocator.deallocate(_vector, _capacity);
				_vector = _allocator.allocate(count);
				_capacity = count;
			}

			for (int i = 0; i < count; i++)
				_allocator.construct(&(_vector[i]), value);
			_size = count;
		}
		template< class InputIt >
		void assign( InputIt first, InputIt last ) {
			clear();

			size_type count = last - first;

			if (count > _capacity) {
				_allocator.deallocate(_vector, _capacity);
				_vector = _allocator.allocate(count);
				_capacity = count;
			}

			for (int i = 0; first != last; i++, first++)
				_allocator.construct(&(_vector[i]), *first);
			_size = count;
		}

		friend bool operator==(const vector& lhs, const vector& rhs)
		{
			if (lhs.size() != rhs.size())
				return false;

			for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
			it.first != lhs.end(); it.first++, it.second++)
				if (*(it.first) != *(it.second))
					return false;
			return true;
		}
		friend bool operator!=(const vector& lhs, const vector& rhs) { return (!operator==(lhs, rhs)); }
		friend bool operator<(const vector& lhs, const vector& rhs)
		{
			for (ft::pair<const_iterator, const_iterator> it(lhs.begin(), rhs.begin());
			it.first != lhs.end() && it.second != rhs.end(); it.first++, it.second++)
				if (*(it.first) < *(it.second))
					return true;
			return (lhs.size() < rhs.size());
		}
		friend bool operator>(const vector& lhs, const vector& rhs) { return (rhs < lhs); }
		friend bool operator<=(const vector& lhs, const vector& rhs) { return !(lhs < rhs); }
		friend bool operator>=(const vector& lhs, const vector& rhs) { return !(rhs < lhs); }
		friend void swap (vector& lhs, vector& rhs) { lhs.swap(rhs); }

	private:
		void reallocateVec(size_type newCapacity)
		{
			pointer tmp = _allocator.allocate(newCapacity);
			for (size_type i = 0; i < _size; ++i)
				_allocator.construct(&tmp[i], _vector[i]);

			this->~vector();
			_capacity = newCapacity;
			_vector = tmp;
		}
		void moveElementsToTheRight(difference_type position, difference_type shift) {
			size_type end = size();
			while (--end >= position) {
				_allocator.construct(&(_vector[end + shift]), _vector[end]);
				_allocator.destroy(&(_vector[end]));
			}
		}
		void moveElementsToTheLeft(iterator first, iterator last)
		{
			for (; first != end(); ++first, ++last)
			{
				_allocator.destroy(&(*first));
				if (last < end())
					_allocator.construct(&(*(first)), *last);
			}
		}
		template <typename U>
		void swap(U& a, U&b)
		{
			U tmp = a;
			a = b;
			b = tmp;
		}
	};

}

#endif