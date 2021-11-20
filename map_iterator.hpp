#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iterator>
# include "iterators_utils.hpp"
# include "trees.hpp"

namespace ft {
	template <class Key, class T, class Compare, class Tree, class Allocator>
	class map_iterator {
	public:
		typedef Key						key_type;
		typedef Compare					compare;
		typedef T						map_typed;
		typedef ft::TreeNode<T, Key, Allocator>	node;
		typedef ft::pair<const Key, T> 	value_type;

		typedef long int	difference_type;
		typedef size_t		size_type;

		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef Tree 		*tree_ptr;
		typedef node 		*node_ptr;
		typedef value_type & reference;
		typedef value_type 	*pointer;

	private:
		node_ptr 	_node;
		tree_ptr 	_tree;
		node_ptr 	_lastElem;
		compare		_compare;
	public:
		map_iterator(node_ptr node = 0, node_ptr lastElem = 0, tree_ptr tree = 0, const compare & compareFun = compare()) :
		_node(node), _lastElem(lastElem), _tree(tree), _compare(compareFun) {
			if (_node == nullptr)
				_node = lastElem;
		}
		map_iterator(const map_iterator<Key, T, compare, Tree, Allocator> & other) {
			_node = other.getNode();
			_lastElem = other.getLastElem();
			_compare = other.getCompare();
			_tree = other.getTree();
		}
		~map_iterator() {}
		node_ptr getNode() const { return (_node); }
		node_ptr getLastElem() const { return (_lastElem); }
		compare getCompare() const { return (_compare); }
		tree_ptr getTree() const { return (_tree); }
		map_iterator & operator=(const map_iterator & other) {
			if (this != &other) {
				_node = other._node;
				_lastElem = other._lastElem;
				_compare = other._compare;
			}
			return (*this);
		}
		reference	operator*() const { return (*(_node->getData())); }
		pointer		operator->() const { return (_node->getData()); }
		map_iterator & operator++() {
			node_ptr previousNode = _node;

			if (_node == _lastElem) {
				_node = _tree->getFirstElem();
				return (*this);
			}
			if (_node == nullptr || _node == _tree->getLastElem()) {
				_node = _lastElem;
				return (*this);
			}
			while (_node != _lastElem && !(_compare(previousNode->getKey(), _node->getKey()))) {
				if (_node->getRightChild() && _compare(previousNode->getKey(), _node->getRightChild()->getKey())) {
					_node = _node->getRightChild();
					node_ptr temp = nullptr;
					if ((temp = searchMinNode(_node)))
						_node = temp;
				}
				else if (_node == _tree->getLastElem())
					_node = _lastElem;
				else
					_node = _node->getParent();
			}
			return (*this);
		}
		map_iterator operator++(int) {
			map_iterator res(*this);

			if (_node == _lastElem) {
				_node = _tree->getFirstElem();
				return (res);
			}
			if (_node == nullptr || _node == _tree->getLastElem()) {
				_node = _lastElem;
				return (res);
			}
			while (_node != _lastElem && !(_compare(res.getNode()->getKey(), _node->getKey()))) {
				if (_node->getRightChild() && _compare(res.getNode()->getKey(), _node->getRightChild()->getKey())) {
					_node = _node->getRightChild();
					node_ptr temp = nullptr;
					if ((temp = searchMinNode(_node)))
						_node = temp;
				}
				else if (_node == _tree->getLastElem())
					_node = _lastElem;
				else
					_node = _node->getParent();
			}
			return (*this);
		}
		map_iterator & operator--() {
			node_ptr previousNode = _node;
			if (_node == _lastElem) {
				_node = _tree->getLastElem();
				return (*this);
			}
			if (_node == _tree->getFirstElem()) {
				_node = _lastElem;
				return (*this);
			}

			while (!_compare(_node->getKey(), previousNode->getKey())) {
				if (_node->getLeftChild()
					&& _compare(_node->getLeftChild()->getKey(), previousNode->getKey()))
				{
					_node = _node->getLeftChild();
					node_ptr tmp = nullptr;
					if ((tmp = searchMaxNode(_node)))
						_node = tmp;
				}
				else
					_node = _node->getParent();
			}
			return (*this);
		}
		map_iterator operator--(int) {
			map_iterator res(*this);
			if (_node == _lastElem) {
				_node = _tree->getLastElem();
				return (res);
			}
			if (_node == _tree->getFirstElem()) {
				_node = _lastElem;
				return (res);
			}

			while (!_compare(_node->getKey(), res.getNode()->getKey())) {
				if (_node->getLeftChild()
				&& _compare(_node->getLeftChild()->getKey(), res.getNode()->getKey()))
				{
					_node = _node->getLeftChild();
					node_ptr tmp = nullptr;
					if ((tmp = searchMaxNode(_node)))
						_node = tmp;
				}
				else
					_node = _node->getParent();
			}
			return (res);
		}
		bool operator==(const map_iterator& it) const   {
			return (it.getNode() == _node);
		}
		bool operator!=(const map_iterator& it) const   { return !(it == *this); }

	private:
		node_ptr searchMinNode(node_ptr root)
		{
			if (root && root->getLeftChild())
				return searchMinNode(root->getLeftChild());
			return root;
		}
		node_ptr searchMaxNode(node_ptr root)
		{
			if (root && root->getRightChild())
				return searchMaxNode(root->getRightChild());
			return root;
		}
	};
}

#endif