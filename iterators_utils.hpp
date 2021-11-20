#ifndef ITERATORS_H
# define ITERATORS_H

# include <cstdlib>
# include <memory>

namespace ft {

template<class T> struct iterators_traits
{
	typedef typename T::value_type          value_type;
	typedef typename T::difference_type     difference_type;
	typedef typename T::iterator_category   iterator_category;
	typedef typename T::pointer             pointer;
	typedef typename T::reference           reference;
};

template<class T> struct iterators_traits<T*>
{
	typedef typename T::value_type          value_type;
	typedef typename T::difference_type     difference_type;
	typedef typename T::iterator_category   iterator_category;
	typedef typename T::pointer             pointer;
	typedef typename T::reference           reference;
};

template<typename Iterator>
class reverse_iterator {
protected:
	Iterator current;
public:

	// constructor
	reverse_iterator() {} ;
	reverse_iterator(typename iterators_traits<Iterator>::pointer ptr) : current(Iterator(ptr)) {}
	reverse_iterator(Iterator itr) : current(itr) {};
	reverse_iterator(const reverse_iterator& other) { *this = other; };
	~reverse_iterator() {};

	// member types //
	typedef Iterator                                                 iterator_type;
	typedef typename iterators_traits<Iterator>::iterator_category   iterator_category;
	typedef typename iterators_traits<Iterator>::value_type          value_type;
	typedef typename iterators_traits<Iterator>::difference_type     difference_type;
	typedef typename iterators_traits<Iterator>::pointer             pointer;
	typedef typename iterators_traits<Iterator>::reference           reference;

	// member functions //
	reverse_iterator & operator=(const reverse_iterator & other) {
		if (this != &other)
			current = other.current;
		return (*this);
	};
	iterator_type   base() const { return (current); };
	reference       operator*() const {
		Iterator tmp = current;
		return (*--tmp);
	};
	pointer         operator->() const { return std::addressof( operator*() ); };
	Iterator & operator[](difference_type n) const { return (current -n - 1); };
	reverse_iterator & operator++() {
		current--;
		return (*this);
	};
	reverse_iterator & operator--() {
		current++;
		return (*this);
	};
	reverse_iterator operator++( int ) {
		reverse_iterator<Iterator> res(*this);
		current--;
		return (res);
	};
	reverse_iterator operator--( int ) {
		reverse_iterator<Iterator> res(*this);
		current++;
		return (res);
	};
	reverse_iterator operator+( difference_type n ) const { return reverse_iterator<Iterator>(current - n); };
	reverse_iterator operator-( difference_type n ) const { return reverse_iterator<Iterator>(current + n); };
	reverse_iterator & operator+=( difference_type n ) {
		current -= n;
		return (*this);
	};
	reverse_iterator & operator-=( difference_type n ) {
		current += n;
		return (*this);
	};
};

// non-member functions
template< typename Iterator1, typename Iterator2 >
bool operator==( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
	return (lhs.base() == rhs.base());
}
template< typename Iterator1, typename Iterator2 >
bool operator!=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
	return (!(lhs.base() == rhs.base()));
}
template< typename Iterator1, typename Iterator2 >
bool operator<( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
	return (lhs.base() < rhs.base());
}
template< typename Iterator1, typename Iterator2 >
bool operator<=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
	return (lhs.base() <= rhs.base());
}
template< typename Iterator1, typename Iterator2 >
bool operator>=( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {
	return (lhs.base() >= rhs.base());
}
template< class Iter >
reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
	return reverse_iterator<Iter>(it.base() - n);
}
template< class Iter >
reverse_iterator<Iter> operator-( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it ) {
	return reverse_iterator<Iter>(it.base() + n);
}

template<bool B, class T>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template<typename> struct is_integral : std::false_type {};
template<> struct is_integral<bool> : std::true_type {};
template<> struct is_integral<short> : std::true_type {};
template<> struct is_integral<char> : std::true_type {};
template<> struct is_integral<int> : std::true_type {};
template<> struct is_integral<long> : std::true_type {};
template<> struct is_integral<long long> : std::true_type {};
template<> struct is_integral<unsigned short> : std::true_type {};
template<> struct is_integral<unsigned char> : std::true_type {};
template<> struct is_integral<unsigned int> : std::true_type {};
template<> struct is_integral<unsigned long> : std::true_type {};
template<> struct is_integral<unsigned long long> : std::true_type {};
template<> struct is_integral<char16_t> : std::true_type {};
template<> struct is_integral<char32_t> : std::true_type {};
template<> struct is_integral<wchar_t> : std::true_type {};
template<> struct is_integral<const bool> : std::true_type {};
template<> struct is_integral<const short> : std::true_type {};
template<> struct is_integral<const char> : std::true_type {};
template<> struct is_integral<const int> : std::true_type {};
template<> struct is_integral<const long> : std::true_type {};
template<> struct is_integral<const long long> : std::true_type {};
template<> struct is_integral<const unsigned short> : std::true_type {};
template<> struct is_integral<const unsigned char> : std::true_type {};
template<> struct is_integral<const unsigned int> : std::true_type {};
template<> struct is_integral<const unsigned long> : std::true_type {};
template<> struct is_integral<const unsigned long long> : std::true_type {};
template<> struct is_integral<const char16_t> : std::true_type {};
template<> struct is_integral<const char32_t> : std::true_type {};
template<> struct is_integral<const wchar_t> : std::true_type {};

template<class InputIt1, class InputIt2>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
	for (; first1 != last1; ++first1, ++first2) {
		if (!(*first1 == *first2)) {
			return false;
		}
	}
	return true;
}

template<class InputIt1, class InputIt2, class BinaryPredicate>
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
	for (; first1 != last1; ++first1, ++first2) {
		if (!p(*first1, *first2)) {
			return false;
		}
	}
	return true;
}

template<class InputIt1, class InputIt2>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
		if (*first1 < *first2) return true;
		if (*first2 < *first1) return false;
	}
	return (first1 == last1) && (first2 != last2);
}

template<class InputIt1, class InputIt2, class Compare>
bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
{
	for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
		if (comp(*first1, *first2)) return true;
		if (comp(*first2, *first1)) return false;
	}
	return (first1 == last1) && (first2 != last2);
}

template<typename T1, typename T2>
class pair {
public:
	typedef T1 first_type;
	typedef T2 second_type;
	T1 first;
	T2 second;
	pair() : first(), second() {} ;
	template<class U1, class U2>
	pair( const pair<U1, U2>& p ) : first(p.first), second(p.second) {} ;
	pair(const T1 & first, const T2 & second) : first(first), second(second) {} ;
	~pair() {};
};

template< class T1, class T2 >
ft::pair<T1,T2> make_pair( T1 t, T2 u ) { return ft::pair<T1, T2>(t, u); }

}

#endif
