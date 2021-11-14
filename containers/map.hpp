#ifndef MAP_HPP
# define MAP_HPP

# include "map_iterator.hpp"
# include "iterators_utils.hpp"
# include <functional>
# include <memory>
# include <stdexcept>
# include <iterator>
# include <limits>

namespace ft {
	template<
	    class Key,
	    class T,
	    class Compare = std::less<Key>,
	    class Allocator = std::allocator<ft::pair<const Key, T> >
	    > class map {
	    private:
	    	typedef ft::AVLTree<Key, T, Compare, Allocator>	tree_type;
		public:
			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair<const Key, T>					value_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;

			typedef value_type &						reference;
			typedef const value_type &					const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;


			typedef ft::map_iterator<Key, T, Compare, tree_type, Allocator>			iterator;
			typedef ft::map_iterator<Key, T, Compare, tree_type, Allocator>			const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
	    private:
	    	typedef ft::TreeNode<T, Key, Allocator>			node_type;
			typedef tree_type 								*tree_ptr;
			typedef node_type 								*node_ptr;

			tree_ptr _tree;
			node_ptr _lastElem;
			key_compare _comparator;
			allocator_type _allocator;
		public:
	    	map() {
	    		_allocator = Allocator();
	    		_comparator = Compare();
	    		_lastElem = new TreeNode<T, Key, Allocator>();
	    		_tree = new AVLTree<Key, T, Compare, Allocator>();
	    	}
	    	map( const Compare& comp, const Allocator& alloc = Allocator() ) : _comparator(comp), _allocator(alloc) {
	    		_lastElem = new TreeNode<T, Key, Allocator>();
	    		_tree = new AVLTree<Key, T, Compare, Allocator>();
	    	}
	    	template< class InputIt >
	    	map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) :
	    	_allocator(alloc), _comparator(comp) {
	    		_lastElem = new TreeNode<T, Key, Allocator>();
	    		_tree = new AVLTree<Key, T, Compare, Allocator>();
	    		for (; first != last; ++first)
	    			_tree->insert((*first).first, (*first).second);
	    	}
	    	map( const map& other ) : _allocator(other._allocator), _comparator(other._comparator) {
	    		_lastElem = new TreeNode<T, Key, Allocator>(*(other._lastElem));
	    		_tree = new AVLTree<Key, T, Compare, Allocator>();
	    		for (const_iterator it = other.begin(); it != other.end(); ++it)
	    			_tree->insert((*it).first, (*it).second);
	    	}
	    	~map() {
	    		clear();
	    		delete _lastElem;
	    	}

	    	map& operator=( const map& other ) {
	    		_comparator = other._comparator;
	    		_allocator = other._allocator;
	    		clear();
	    		delete _lastElem;
	    		_lastElem = new TreeNode<T, Key, Allocator>(*(other._lastElem));
	    		_tree = new AVLTree<Key, T, Compare, Allocator>();
	    		for (const_iterator it = other.begin(); it != other.end(); ++it)
	    			_tree->insert((*it).first, (*it).second);
	    		return (*this);
	    	}
	    	allocator_type get_allocator() const { return (_allocator); }

	    	T& at( const Key & key ) {
	    		TreeNode<mapped_type , key_type , allocator_type> *res = _tree->findNode(key);
	    		if (res == nullptr)
					throw std::out_of_range("no such key");
	    		return (res->getValue());
	    	}
	    	T& operator[]( const Key& key ) {
	    		TreeNode<mapped_type , key_type, allocator_type> *res = _tree->findNode(key);
	    		if (res == nullptr)
	    			_tree->insert(key, T());
	    		res = _tree->findNode(key);
	    		return (res->getValue());
	    	}

	    	iterator begin() { return map_iterator<Key, T, Compare, tree_type, Allocator>(_tree->getFirstElem(), _lastElem, _tree); }
	    	const_iterator begin() const { return map_iterator<Key, T, Compare, tree_type, Allocator>(_tree->getFirstElem(), _lastElem, _tree); }

	    	iterator end() { return map_iterator<Key, T, Compare, tree_type, Allocator>(_lastElem, _lastElem, _tree); }
	    	const_iterator end() const { return map_iterator<Key, T, Compare, tree_type, Allocator>(_lastElem, _lastElem, _tree); }

	    	reverse_iterator rbegin() { return map_iterator<Key, T, Compare, tree_type, Allocator>(_lastElem, _lastElem, _tree); }
	    	const_reverse_iterator rbegin() const { return map_iterator<Key, T, Compare, tree_type, Allocator>(_lastElem, _lastElem, _tree); }

	    	reverse_iterator rend() { return map_iterator<Key, T, Compare, tree_type, Allocator>(_tree->getFirstElem(), _lastElem, _tree); }
	    	const_reverse_iterator rend() const { return map_iterator<Key, T, Compare, tree_type, Allocator>(_tree->getFirstElem(), _lastElem, _tree); }

	    	bool empty() const { return (begin() == end()); }
	    	size_type size() const { return (std::distance(begin(), end())); }
	    	size_type max_size() const { std::numeric_limits<difference_type>::max(); }

	    	void erase( iterator pos ) { _tree->remove(pos->first); }
	    	void erase( iterator first, iterator last ) {
	    		for( ; first != last ; ) {
	    			iterator temp = first;
	    			first++;
	    			_tree->remove(temp->first);
	    		}
	    	}
	    	size_type erase( const Key& key ) {
	    		iterator it = find(key);
	    		if (it == end())
	    			return (0);
				erase(it);
				return (1);
	    	}
	    	void clear() { erase(begin(), end()); }
	    	ft::pair<iterator, bool> insert( const value_type& value ) {
	    		TreeNode<mapped_type , key_type, Allocator> *elem = _tree->findNode(value.first);
	    		if (elem != nullptr)
	    			return ( ft::pair<iterator, bool>(iterator(elem, _lastElem, _tree), false) );
	    		_tree->insert(value.first, value.second);
	    		return (ft::pair<iterator, bool>(iterator(_tree->findNode(value.first), _lastElem, _tree), true));
	    	}
	    	iterator insert( iterator hint, const value_type& value ) {
	    		if (hint->first == value.first)
	    			return hint;
	    		TreeNode<mapped_type , key_type, Allocator> *it = _tree->findNode(value.first);
	    		if (it != nullptr)
	    			return iterator(it, _lastElem, _tree);
	    		_tree->insert(value.first, value.second);
	    		it = _tree->findNode(value.first);
	    		return iterator(it, _lastElem, _tree);
	    	}
	    	template< class InputIt >
	    	void insert( InputIt first, InputIt last ) {
	    		for( ; first != last; first++)
					insert(*first);
	    	}
	    	void swap( map& other ) {
	    		map temp(other);
	    		other = *this;
	    		*this = temp;
	    	}

	    	size_type count( const Key& key ) const {
	    		if (_tree->findNode(key) == nullptr)
	    			return 0;
	    		return 1;
	    	}
	    	iterator find( const Key& key ) {
	    		TreeNode<mapped_type , key_type, Allocator> *elem = _tree->findNode(key);
	    		if (elem == nullptr)
	    			return end();
	    		return iterator(elem, _lastElem, _tree);
	    	}
	    	const_iterator find( const Key& key ) const {
	    		TreeNode<mapped_type , key_type, Allocator> *elem = _tree->findNode(key);
	    		if (elem == nullptr)
	    			return end();
	    		return const_iterator(elem, _lastElem, _tree);
	    	}
	    	iterator lower_bound( const Key& key ) {
				iterator it = begin();
				for( ; it != end(); it++) {
					if (_comparator(it->first, key) == false)
						break;
				}
				return (it);
	    	}
	    	const_iterator lower_bound( const Key& key ) const {
	    		const_iterator it = begin();
	    		for( ; it != end(); it++) {
	    			if (_comparator(it->first, key) == false)
	    				break;
	    		}
	    		return (it);
	    	}
	    	iterator upper_bound( const Key& key ) {
	    		iterator it = begin();
	    		for( ; it != end(); it++) {
	    			if (_comparator(key, it->first) == true)
	    				break;
	    		}
	    		return (it);
	    	}
	    	const_iterator upper_bound( const Key& key ) const {
	    		const_iterator it = begin();
	    		for( ; it != end(); it++) {
	    			if (_comparator(key, it->first) == true)
	    				break;
	    		}
	    		return (it);
	    	}
	    	ft::pair<iterator,iterator> equal_range( const Key& key ) {
	    		return (ft::make_pair(lower_bound(key), upper_bound(key)));
	    	}
	    	ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
	    		return (ft::make_pair(lower_bound(key), upper_bound(key)));
	    	}
	    	class value_compare {
			protected:
	    		Compare comp;
	    		value_compare(Compare c) : comp(c) {}
			public:
	    		typedef bool        result_type;
	    		typedef value_type  first_argument_type;
	    		typedef value_type  second_argument_type;

	    		bool operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); }
	    	};
	    	key_compare key_comp() const { return (_comparator); }
	    	value_compare value_comp() const { return (value_compare(_comparator)); }

	    	template< class key, class value, class compare, class alloc >
	    	friend bool operator==( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs );
	    	template< class key, class value, class compare, class alloc >
	    	friend bool operator!=( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs );
	    	template< class key, class value, class compare, class alloc >
	    	friend bool operator<( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs );
	    	template< class key, class value, class compare, class alloc >
	    	friend bool operator>=( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs );
	    	template< class key, class value, class compare, class alloc >
	    	friend bool operator>( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs );
	    	template< class key, class value, class compare, class alloc >
	    	friend bool operator<=( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs );
	    	template< class key, class value, class compare, class alloc >
	    	friend void swap( ft::map<key,value,compare,alloc>& lhs,
			ft::map<key,value,compare,alloc>& rhs );
	};

	template< class key, class value, class compare, class alloc >
	bool operator==( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return (false);
		for (ft::pair<typename ft::map<key,value,compare,alloc>::const_iterator,typename ft::map<key,value,compare,alloc>::const_iterator> it(lhs.begin(), rhs.begin());
		it.first != lhs.end(); it.first++, it.second++) {
			if (*(it.first) != *(it.second))
				return (false);
		}
		return (true);
	}
	template< class key, class value, class compare, class alloc >
	bool operator!=( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs ) { return (!(lhs == rhs)); }
	template< class key, class value, class compare, class alloc >
	bool operator<( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs ) {
		for (ft::pair<typename ft::map<key,value,compare,alloc>::const_iterator,typename ft::map<key,value,compare,alloc>::const_iterator> it(lhs.begin(), rhs.begin());
		it.first != lhs.end() && it.second != rhs.end(); it.first++, it.second++) {
			if (*(it.first) < *(it.second))
				return true;
		}
		return (lhs.size() < rhs.size());
	}
	template< class key, class value, class compare, class alloc >
	bool operator>=( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs ) { return (!(lhs < rhs)); }
	template< class key, class value, class compare, class alloc >
	bool operator>( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs ) { return (rhs < lhs); }
	template< class key, class value, class compare, class alloc >
	bool operator<=( const ft::map<key,value,compare,alloc>& lhs, const ft::map<key,value,compare,alloc>& rhs ) { return (!(lhs > rhs)); }
	template< class key, class value, class compare, class alloc >
	void swap( ft::map<key,value,compare,alloc>& lhs, ft::map<key,value,compare,alloc>& rhs ) { lhs.swap(rhs); }
}

#endif